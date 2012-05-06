/* $Id: distributable_recursive_processor.h 640 2011-09-29 15:30:05Z marjobe $ */

/** 
 *  @file:      distributable_recursive_processor.h
 *  @details    Header file for Recabs providing DistributableRecursiveProcessor class.
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

#ifndef DISTRIBUTABLE_RECURSIVE_PROCESSOR_H
#define DISTRIBUTABLE_RECURSIVE_PROCESSOR_H

#include "common.h"
#include "recursive_processor.h"
#include "deserializer_functor.h"
#include "result_sender.h"
#include "l4_client_app.h"
#include "distribution_policy.h"

namespace recabs
{

/**
 *  Abstract class that represents a distributable node of execution.
 */

class DistributableRecursiveProcessor : public RecursiveProcessor
{
    public:

        /**
         *  Destructor.
         */
        virtual ~DistributableRecursiveProcessor();

    protected:

        /**
         *  Constructor.
         */
        DistributableRecursiveProcessor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp);

        /**
         *  Sends functors to the server if it needs. The maximum number of delivered functors
         *  is the size of the list minus 1. Erases the sent functors.
         *
         * @param children : list of funtors to dispatch.
         */
        virtual void dispatch_children(ChildrenFunctors& children);

        /**
         *  Should be implemented the way to delegate work to server.
         *
         *  @param p : packet with work for the other clients.
         */
        virtual void dispatch_work(ChildrenFunctors& functors);

        /**
         *  Should be implemented as a way to request help from the server.
         *
         *  @param n : number of helpers needed.
         */ 
        virtual uint collaborators(uint n) = 0;

        /**
         * Sends a result.
         *
         * @param packet : result to send.
         * @param when : the time politic to send the packet.
         */
        virtual void send_result(const Packet& packet, WhenToSend when);

        /**
         * Sends a message.
         *
         * @param packet : message to send.
         * @param when : the time politic to send the packet.
         */
        virtual void send_message(const Packet& packet, WhenToSend when);

        /**
         * Starts the computation. It receives a packet who is the initial functor,
         * it begins the recursion.
         *
         * @param init_packet : initial packet.
         */
        virtual void start_execution(const Packet& init_packet);

        /**
         * Computes the entire recursion. At each step of the recursion, it calls
         * reproduce method which fills the list of all functors.
         *
         * @param functor_list : the initial list to be reproduced.
         */
        virtual void do_recursion(ChildrenFunctors& functor_list);

        /**
         * Reproduces the functor given by parameter, if it is necessary sends information
         * to the server and fills the list with the new children generated.
         *
         * @param rf : functor to reproduce.
         * @param functor_list : list of funtors to be filled by this step of the recursion.
         */
        virtual void reproduce(RecursiveFunctor* rf, ChildrenFunctors& functor_list);

    private:

        /**
         * DeserializerFunctor asociated.
         * Deserialized the incoming functors.
         */
        const DeserializerFunctor& _deserializer;

        /**
         * L4ClientApp asociated.
         * It is the responsible of managing of results.
         */
        const L4ClientApp& _client_app;

        /**
         * DistributablePolicy asociated.
         * Policy responsible of decide when and how much jobs can be deliver to the server.
         */
        const DistributablePolicy& _distribution_policy;

        /**
         * Senders.
         */
        MessageSender*     _result_sender;
        MessageSender*     _message_sender;
        InmediatelySender  _job_sender;

};

/**
 *  DistributableRecursiveProcessor Factory Method.
 */
DistributableRecursiveProcessor* create_recursion_processor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp);

}

#endif
