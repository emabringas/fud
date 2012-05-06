/* $Id: recursion_manager.h 589 2011-07-14 18:25:31Z marjobe $ */

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

#ifndef RECURSION_MANAGER_H
#define RECURSION_MANAGER_H

#include <stack>
//#include "common.h"
#include "l4_server_app.h"


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
             * Destructor.
             */
             virtual ~RecursionManager();

            /**
             * Should be start the recursion.
             */
            virtual void start() = 0;

           /**
             * Handles input packets. 
             *
             * @param input : the input packet that us will handle.
             */
            virtual void handle_receive_packet(InputMessage& input);

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
             * It handles the end of a client process.
             */
            virtual void handle_end_of_job();

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
            uint _jobs_waiting_end;

    };
    
    /**
      * To be implemented, will be linked with the apropriate concrete Recursion Manager.
      */
    RecursionManager* create_recursion_manager(L4ServerApp& srv_app);



}

#endif

