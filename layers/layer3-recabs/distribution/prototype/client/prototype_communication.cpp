/* $Id: prototype_communication.cpp 358 2010-11-09 20:47:54Z emab73 $ */

/**
 *  @file:      prototype_communication.cpp
 *  @details    Implementation file for  class.
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
 * communication.cpp
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

#include "prototype_communication.h"

#include "serializable_recursive_functor.h"
#include <iostream>

using namespace recabs;

Communication* Communication::create_communication(RecursionManager& rm)
{
    return new PrototypeCommunication(rm);
}

PrototypeCommunication::PrototypeCommunication(RecursionManager& rm):
    _manager(rm)
{
}

void PrototypeCommunication::send(const Packet& packet)
{
    _manager.receive_packet(packet);
}
