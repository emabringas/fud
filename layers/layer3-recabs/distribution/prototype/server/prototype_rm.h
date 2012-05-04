/* $Id: prototype_rm.h 356 2010-11-04 13:38:16Z emab73 $ */

/** 
 *  @file:      prototype_rm.h
 *  @details    Header file for PrototypeRecursionManager class.\n
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

#ifndef PROTOTYPE_RM_H
#define PROTOTYPE_RM_H

#include <stack>
#include "common.h"
#include "recursion_manager.h"
#include "l4_server_app.h"
#include "deserializer_functor.h"
#include "prototype_rp.h"

namespace recabs
{
    /**
     * Class that represents a concrete manager of recursion. It's implemented locally.
     */
    class PrototypeRM : public RecursionManager
    {
        public:

            /**
             * Constructor.
             */
            PrototypeRM(L4ServerApp& srv_app, L4ClientApp& clt_app, const DeserializerFunctor& deserializer);

            /**
             * Destructor.
             */
            virtual ~PrototypeRM();

            /**
             * Starts the recursion.
             *
             * @param server_app : concrete L4ServerApp to set.
             */
            virtual void start();

            /**
             * Sends a packet.
             *
             * @param packet : packet to send.
             */
            virtual void send_packet(const Packet& packet);

           /**
             * Sends a packet.
             *
             * @param packet : packet to send.
             */    
            virtual void receive_packet(const Packet& packet);

        private:

            /* Unique client. This prototype support only one client as
             * a node of execution.
             */
            PrototypeRP _worker;
            
    };

}

#endif
