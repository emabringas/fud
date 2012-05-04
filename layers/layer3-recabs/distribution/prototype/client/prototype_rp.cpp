/* $Id: prototype_rp.cpp 358 2010-11-09 20:47:54Z emab73 $ */

/**
 *  @file:      prototype_rp.cpp
 *  @details    Implementation file for PrototypeRP class.
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

#include "prototype_rp.h"

using namespace recabs;

PrototypeRP::PrototypeRP(L4ClientApp& app, const DeserializerFunctor& df, RecursionManager& rm):
    DistributableRecursiveProcessor(app, df, rm)
//    _manager(rm)
{
}

PrototypeRP::~PrototypeRP()
{
}

void PrototypeRP::start()
{

}

void PrototypeRP::dispatch_work(const Packet& packet)
{

}

void PrototypeRP::collaborators(uint n)
{

}

void PrototypeRP::receive_packet(const Packet& packet)
{
    /* First, apply deserialize to input packet. */
    SerializableRecursiveFunctor* rf;
    _deserializer.deserialize(packet, &rf);
    /* Executes the functor. Its output is a results container. */
    PacketContainer result;
    functor_execute(rf, result);
    /* Creates a output stream with the results container. */
    mili::bostream out;
    out << result;
    /* Sends it. */
    WhenToSend when; // esto es solo por ahoraa, BORRAR!!!
    send_result(out.str(), when);
}

void PrototypeRP::send_packet(const Packet& packet)
{
//    _manager.receive_packet(packet);
}

DistributableRecursiveProcessor* DistributableRecursiveProcessor::create_recursive_processor(const DeserializerFunctor& deserializer)
{
    return NULL;
}
