/* $Id: distributable_recursive_processor.cpp 640 2011-09-29 15:30:05Z marjobe $ */

/**
 *  @file:      distributable_recursive_processor.cpp
 *  @details    Implementation file for DistributableRecursiveProcessor class.
 *              System: RecAbs\n
 *              Language: C++\n
 *
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * process without data dependency for the framework FuD.
 * See <http://fud.googlecode.com/>.
 *
 * Copyright (C) 2010, 2011 - Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of RecAbs project.
 *
 * RecAbs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <syslog.h>
#include <algorithm>
#include <mili/mili.h>
#include "distributable_recursive_processor.h"

using namespace recabs;
using recabs::uint;

DistributableRecursiveProcessor::DistributableRecursiveProcessor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp):
    _deserializer(df),
    _client_app(app),
    _distribution_policy(dp),
    _job_sender(kJob)
{
    _result_sender = _client_app.createMessageSender(kRes);
    _message_sender = _client_app.createMessageSender(kMess);
}

DistributableRecursiveProcessor::~DistributableRecursiveProcessor()
{
    delete _result_sender;
    delete _message_sender;
}

void DistributableRecursiveProcessor::start_execution(const Packet& init_packet)
{
    /* First deserialize the input packet. */
    SerializableRecursiveFunctor* rf;
    _deserializer.deserialize(init_packet, &rf);

    /* List which mantains all functors at the moment.
     * Head positions contains heavy functors and tail has light functors.
     */
    ChildrenFunctors recursion_list;
    /* Puts the first funtor into the all functors list. */
    recursion_list.push_back(rf);
    /* Executes the recursion. The outputs are handled by "send" methods. */
    do_recursion(recursion_list);

    /* Sends all kind of messages. */
    _job_sender.flush();
    _message_sender->flush();
    _result_sender->flush();
}


/*
 * REPRODUCES_PER_ASK constant definition.
 */
static const size_t REPRODUCES_PER_ASK = 100;


void DistributableRecursiveProcessor::do_recursion(ChildrenFunctors& functor_list)
{
    /* Initializes the reproduce counter. */
    size_t reproduce_count(0);

    /* Reproduces all the funtors. */
    while ( !functor_list.empty() )
    {
        /* Take the last functor (the weight minor node) and then remove it from list. */
        RecursiveFunctor* rf = functor_list.back();
        functor_list.pop_back();
        /* Generate the children of the last functor. */
        reproduce(rf, functor_list);

        /* Children distribution. */
        reproduce_count++;
        if (reproduce_count > REPRODUCES_PER_ASK)
        {
            dispatch_children(functor_list);
            reproduce_count = 0;
        }
    }
}

void DistributableRecursiveProcessor::reproduce(RecursiveFunctor* rf, ChildrenFunctors& functor_list)
{
    /* Parameter objects of call method. */
    ChildrenFunctors children;
    Packet message;
    WhenToSend when = kSendWhenRecAbsWants;

    /* Call gives us maybe a list of children, maybe a message and a way to send the messages. */
    rf->call(children, message, when);
    /* Deletes the current recursive functor, it has already paid off. */
    delete rf;

    /* Does the message packet has something ? */
    if (!message.empty())
    {
        if ( children.empty() )
        {
            /* In this case, the message is a leaf of the recursion tree, then is a result. */
            send_result(message, when);
        }
        else
        {
            /* Here, the message contains a regular message, which could be sent in the
             * middle of the recursion.
             */
            send_message(message, when);
        }
    }

    /* Add (at the end) new children resulting from functor's call to the list of all functors. */
    if ( !children.empty() )
        functor_list.splice(functor_list.end(), children);
}

void DistributableRecursiveProcessor::dispatch_children(ChildrenFunctors& children)
{
    const uint orders = children.size()-1;
    if ( orders > 0 )
    {
        const uint free_collaborators = collaborators(orders);
        if (free_collaborators > 0)
        {
            ChildrenFunctors::iterator it = children.begin();
            advance(it, free_collaborators);

            ChildrenFunctors functors_to_dispatch(children.begin(), it);
            dispatch_work(functors_to_dispatch);
            
            /* Deletes the functors which has been sent to the server. */
            for (ChildrenFunctors::iterator itr = children.begin(); itr != it; itr++)
                delete *itr;
            children.erase(children.begin(), it);
        }
    }
}

void DistributableRecursiveProcessor::dispatch_work(ChildrenFunctors& functors)
{
    PacketContainer container;
    ChildrenFunctors::const_iterator it;
    for (it = functors.begin(); it != functors.end(); it++)
    {
        Packet p;
        SerializableRecursiveFunctor* srf((SerializableRecursiveFunctor*)*it);
        srf->serialize(p);
        mili::insert_into(container, p);
    }

    _job_sender.send(container);
}

void DistributableRecursiveProcessor::send_result(const Packet& packet, WhenToSend when)
{
    PacketContainer container;
    mili::insert_into(container, packet);

    switch (when)
    {
        case kSendThisImmediately:
            InmediatelySender(kRes).send(container);
            break;

        case kSendAllImmediately:
            _result_sender->send(container);
            _result_sender->flush();
            break;

        case kSendWhenRecAbsWants:
            _result_sender->send(container);
            break;

        default:
            syslog(LOG_NOTICE, "RecAbs Error: Invalid WhenToSend value \"%d\" found trying to send a result.", when);
    }
}

void DistributableRecursiveProcessor::send_message(const Packet& packet, WhenToSend when)
{
    PacketContainer container;
    mili::insert_into(container, packet);

    switch (when)
    {
        case kSendThisImmediately:
            InmediatelySender(kMess).send(container);
            break;

        case kSendAllImmediately:
            _message_sender->send(container);
            _message_sender->flush();
            break;

        case kSendWhenRecAbsWants:
            _message_sender->send(container);
            break;

        default:
            syslog(LOG_NOTICE, "RecAbs Error: invalid WhenToSend value \"%d\" found trying to send a message.", when);
    }
}

