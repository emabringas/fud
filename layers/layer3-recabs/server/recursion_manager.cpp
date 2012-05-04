/* $Id: recursion_manager.cpp 354 2010-11-03 22:22:34Z emab73 $ */

/**
 *  @file:      recursion_manager.cpp
 *  @details    Implementation file for RecursionManager class.
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

#include "recursion_manager.h"
#include <mili/mili.h>


using namespace recabs;

RecursionManager::RecursionManager(L4ServerApp& app):
    _server_app(app),
    _missing_result_counter(0)
{
}

void RecursionManager::handle_receive_packet(const Packet& packet)
{
    RecabsPacketHeader header;
    /* extract_header(packet, header); */
    mili::bistream bis(packet);
    bis >> header;
    if (is_result(header))
    {
        _missing_result_counter--;
        /*  */
        PacketContainer result;
        bis >> result;
        PacketContainer::iterator it;
        for (it = result.begin(); it != result.end(); it++)
            _server_app.receive_result(*it);
    }
    else
        push_child(packet);
}

void RecursionManager::push_child(const Packet& packet)
{
    _stack.push(packet);
}

void RecursionManager::pop_child(Packet& packet)
{
    packet = _stack.top();
    _stack.pop();
    _missing_result_counter++;
}

bool RecursionManager::empty_stack() const
{
    return _stack.empty();
}

bool RecursionManager::finished() const
{
    return _missing_result_counter == 0;
}

bool RecursionManager::is_result(const RecabsPacketHeader& header) const
{
    return header == kRes;
}

