/* $Id: fud_rprocessor.cpp 611 2011-08-04 13:31:03Z marjobe $ */

/** 
 *  @file:      fud_rprocessor.cpp
 *  @details    Implementation file for FuDRProcessor class.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       March 2011
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

#include "fud_rprocessor.h"
#include "common.h"

using namespace recabs;

FuDRProcessor::FuDRProcessor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp) :
    DistributableRecursiveProcessor(app, df, dp),
    ClientProcessor()
{
}

FuDRProcessor::~FuDRProcessor()
{
    fud::finish_client();
    delete _distribution_client;
}

void FuDRProcessor::run(const Address& address, Port port)
{
    _distribution_client = fud::create_distribution_client(address, port);
    _distribution_client->run();
}

bool FuDRProcessor::process(fud::InputMessage& input, fud::OutputMessage&)
{
    /* Fill the initial packet. */
    Packet init_packet;
    input >> init_packet;

    /* Starts execution. The outputs will be sent by DRP class. */
    start_execution(init_packet);
    return true;
}

recabs::uint FuDRProcessor::collaborators(recabs::uint n)
{
    fud::InteractiveHelper helper;
    return (recabs::uint) helper.ask_for_free_clients((fud::fud_uint) n);
}

namespace recabs
{
    DistributableRecursiveProcessor* create_recursion_processor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp)
    {
        return new FuDRProcessor(app, df, dp);
    }
}

