/* $Id: prototype_rm.cpp 356 2010-11-04 13:38:16Z emab73 $ */

/**
 *  @file:      prototype_rm.cpp
 *  @details    Implementation file for PrototypeRM class.
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

#include "prototype_rm.h"

using namespace recabs;


PrototypeRM::PrototypeRM(L4ServerApp& srv_app, L4ClientApp& clt_app, const DeserializerFunctor& deserializer):
    RecursionManager(srv_app),
    _worker(clt_app, deserializer, *this)
{
}

PrototypeRM::~PrototypeRM()
{

}

void PrototypeRM::start()
{
    /* Puts the initial packet. */
    Packet initial_packet;
    _server_app.get_initial_packet(initial_packet);
    push_child(initial_packet);
    /* Starts the manager of inputs and outputs packets. */
//    do
    if (!empty_stack())
    {
        Packet packet;
        pop_child(packet);
        send_packet(packet);
    }
//    while (!finished());
}

void PrototypeRM::send_packet(const Packet& packet)
{
    _worker.receive_packet(packet);
}

void PrototypeRM::receive_packet(const Packet& packet)
{
    handle_receive_packet(packet);
}

RecursionManager* RecursionManager::create_recursion_manager(L4ServerApp& srv_app, L4ClientApp& clt_app, const DeserializerFunctor& deserializer)
{
    return new PrototypeRM(srv_app, clt_app, deserializer);
}

