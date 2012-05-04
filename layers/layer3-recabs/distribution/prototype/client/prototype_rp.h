/* $Id: prototype_rp.h 358 2010-11-09 20:47:54Z emab73 $ */

/** 
 *  @file:      prototype_rp.h
 *  @details    Header file for Recabs providing PrototypeRP class.
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

#ifndef PROTOTYPE_RP_H
#define PROTOTYPE_RP_H

#include "common.h"
#include "distributable_recursive_processor.h"
#include "deserializer_functor.h"


namespace recabs
{
    /* Forward declaration. */
    class PrototypeRM;

    /**
     *  Class that represents a concrete node of execution. It's implemented locally.
     */
    class PrototypeRP : public DistributableRecursiveProcessor
    {
        public:

            /**
             *  Constructor.
             */
            PrototypeRP(L4ClientApp& app, const DeserializerFunctor& df, RecursionManager& rm);

            /**
             *  Destructor.
             */
            virtual ~PrototypeRP();

            /**
             *  Should be implemented as a way to start the exectution of a single node.
             */
            virtual void start();

            /**
             * Sends a packet.
             *
             * @param packet : packet to send.
             */
            virtual void send_packet(const Packet& packet);

            /**
             * Receive a packet.
             *
             * @param packet : packet to send.
             */
            virtual void receive_packet(const Packet& packet);
    
        protected:

            /**
             *  Should be implemented the way to delegate work to server.
             *  @param p : Packet with work for the other clients.
             */
            virtual void dispatch_work(const Packet& packet);

            /**
             *  Should be implemented th way to request help to server.
             *  @param n: Number of helpers needed.
             */ 
            virtual void collaborators(uint n);

        private:

            /* Recursion manager asociated. */
//            RecursionManager& _manager;
            
    };
}

#endif
