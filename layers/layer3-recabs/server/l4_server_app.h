/* $Id: l4_server_app.h 326 2010-10-04 16:49:47Z marjobe $ */

/** 
 *  @file:      l4_server_app.h
 *  @details    Header file for L4ServerApp interface.\n
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

#ifndef L4_SERVER_APP_H
#define L4_SERVER_APP_H

#include "common.h"

namespace recabs
{
    /**
     * Interface that represents a helper for the start of the recursion and
     * aggregate the results.
     *
     */
    struct L4ServerApp
    {
        /**
         * This method should get the initial packet.
         *
         * @param pkt : the packet to fill with the initial packet.
         */
        virtual void get_initial_packet(Packet& pkt) const = 0;

        /**
         * Should be process a single result.
         *
         * @param result : result to manipulate.
         */
        virtual void receive_result(const Packet& result) = 0;
    };

}

#endif
