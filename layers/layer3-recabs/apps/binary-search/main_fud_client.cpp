/* $Id: main_fud_client.cpp 571 2011-06-13 14:43:46Z marjobe $ */

/**
 *  @file:      main_fud_client.h
 *  @details    Implementation file for Recabs providing app class MainFudClient.
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

#include "recabs.h"
#include "bs_deserializer.h"
#include "l4_client_bs.h"
#include <getopt_pp.h>

using namespace GetOpt;

int main(int argc, char** argv)
{
    size_t      port(31337);
    std::string address("127.0.0.1");

    GetOpt_pp ops(argc, argv);
    ops >> Option('a', "address", address) >> Option('p', "port", port) ;

    BSDeserializer bsd;
    L4ClientBS bsapp;
    recabs::FixedLeafsDistributablePolicy dp(1000000);

    recabs::DistributableRecursiveProcessor* rp = recabs::create_recursion_processor(bsapp, bsd, dp);

    rp->run(address, port);
    
    /* Clean up */
    delete rp;

    return 0;
}
