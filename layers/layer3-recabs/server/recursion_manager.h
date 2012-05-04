/* $Id: recursion_manager.h 356 2010-11-04 13:38:16Z emab73 $ */

/** 
 *  @file:      recursion_manager.h
 *  @details    Header file for RecursionManager class.\n
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

#ifndef RECURSION_MANAGER_H
#define RECURSION_MANAGER_H

#include <stack>
#include "common.h"
#include "l4_server_app.h"
#include "l4_client_app.h" // Solo por ahora, esto no debería hacer falta!!!
#include "deserializer_functor.h"

namespace recabs
{
    /**
     * Abstract class that represents a manager of recursion, wich handles incoming
     * and outgoing packets. Results of the recursion are handle by L4ServerApp asociated.
     */
    class RecursionManager
    {
        public:

            /**
             * Should be start the recursion.
             *
             * @param server_app : concrete L4ServerApp to set.
             */
            virtual void start() = 0;

           /**
             * Handles input packets. 
             *
             * @param child_in : the input packet that we handle.
             */
            virtual void handle_receive_packet(const Packet& packet);

            /**
             * Should be send a packet.
             *
             * @param packet : packet to send.
             */
            virtual void send_packet(const Packet& packet) = 0;

           /**
             * Should be receive a packet.
             *
             * @param packet : packet to send.
             */    
            virtual void receive_packet(const Packet& packet) = 0 ;
        
            /**
              * To be implemented, will be linked with the apropriate concrete
              * Recursion Manager.
              * Solo por ahora toma un clien app, ya que es necesario para la creación del recursion manager de prototipo VER!!!
              */
            static RecursionManager* create_recursion_manager(L4ServerApp& srv_app, L4ClientApp& clt_app, const DeserializerFunctor& deserializer);

        protected:

            /**
             *  Constructor method.
             */
            RecursionManager(L4ServerApp& app);

            /**
             * Pushes a child.
             *
             * @param child_in : packet to push.
             */
            virtual void push_child(const Packet& packet);

            /**
             * Pops a child.
             *
             * @param child_out : packet to pop.
             */
            virtual void pop_child(Packet& packet);

            /**
             * Returns whether the stack is empty.
             *
             * @returns true if the stack is empty.
             */
            virtual bool empty_stack() const;

            /**
             * Returns wheter the recursion process is finished.
             *
             * @returns true if the recursion is finished.
             */
            virtual bool finished() const;

            /* Atribute */
            L4ServerApp& _server_app;

        private:

            /**
             * Returns wheter the given packet is a result.
             *
             * @param packet : packet to inspect.
             *
             * @returns true if the packet is a result.
             */
            bool is_result(const RecabsPacketHeader& header) const;

            /* Stack of Packet's */
            std::stack<Packet> _stack;

            /* It's the number of results we wait.
             * _missing_result_counter = <functors-sent> - <results-received>
             */
            uint _missing_result_counter;

    };


}

#endif

