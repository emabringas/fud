/* $Id: prototype_communication.h 358 2010-11-09 20:47:54Z emab73 $ */

/** 
 *  @file:      prototype_communication.h
 *  @details    Header file for Recabs providing PrototypeCommunication class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       October 2010
 *  @version    0.1
 *
 * communication_interface.h
 * This file is part of RecAbs
 *
 * Copyright (C) 2010 - Emanuel Bringas and Mariano Bessone
 *
 * RecAbs is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#ifndef PROTOTYPE_COMMUNICATION_H
#define PROTOTYPE_COMMUNICATION_H

#include "communication.h"
#include "prototype_rm.h"
//#include "common.h"

namespace recabs
{
    class PrototypeCommunication : public Communication
    {
        public:

           PrototypeCommunication(RecursionManager& rm);

           /**
             * Sends a packet.
             *
             * @param packet : packet to send.
             */
            virtual void send(const Packet& packet);

            RecursionManager& _manager;

    };

}

#endif
