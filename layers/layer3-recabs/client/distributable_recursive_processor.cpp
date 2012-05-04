/* $Id: distributable_recursive_processor.cpp 358 2010-11-09 20:47:54Z emab73 $ */

/**
 *  @file:      distributable_recursive_processor.cpp
 *  @details    Implementation file for DistributableRecursiveProcessor class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
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
 * This file is part of RecAbs
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * processes without data dependency for framework FuD.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Mariano Bessone and Emanuel Bringas
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

#include <mili/mili.h>
#include "distributable_recursive_processor.h"

using namespace recabs;

DistributableRecursiveProcessor::DistributableRecursiveProcessor(L4ClientApp& app, const DeserializerFunctor& df, RecursionManager& rm):
    _deserializer(df),
    _client_app(app)
{
    _realSender = new RealResultSender(rm);
    _resultSender = _client_app.createResultSender(_realSender);
    if (_resultSender == NULL)
        _resultSender = _realSender;
}

DistributableRecursiveProcessor::~DistributableRecursiveProcessor()
{

}

void DistributableRecursiveProcessor::functor_execute(RecursiveFunctor* rf, PacketContainer& final_result)
{
    ChildrenFunctors children;
    Packet result = "";

    WhenToSend when;

    rf->call(children, result, when);

    if (result.compare("") != 0)
    {
        if (children.empty())
            mili::insert_into(final_result, result);
        else
        {
            PacketContainer res;
            mili::insert_into(res, result);
            mili::bostream intermediate_result;
            intermediate_result << res;
            send_result(intermediate_result.str(), when);
        }
    }
    ChildrenFunctors::const_iterator it;
    for (it = children.begin(); it != children.end(); it++)
        functor_execute(*it, final_result);

}

void DistributableRecursiveProcessor::dispatch_work(const Packet& packet)
{
    mili::bostream header;
    header << kJob;
    send_packet(header.str() + packet);
}

void DistributableRecursiveProcessor::collaborators(uint n)
{
    mili::bostream header;
    header << kReq << n;
    send_packet(header.str());
}

void DistributableRecursiveProcessor::send_result(const Packet& packet, WhenToSend when)
{
    mili::bostream header;
    header << kRes;
//    send_packet(header.str() + packet);

    switch (when)
    {
        case kSendAllImmediately:
            _resultSender->flush();
            // don't break, now send the packet

        case kSendThisImmediately:
            _realSender->send(header.str() + packet);
            break;

        case kSendWhenYouWant:
            _resultSender->send(header.str() + packet);
            break;
    }


}

