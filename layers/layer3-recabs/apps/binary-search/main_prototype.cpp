/* $Id: main_prototype.cpp 356 2010-11-04 13:38:16Z emab73 $ */

/**
 *  @file:      main_prototype.h
 *  @details    Implementation file for Recabs providing app class MainPrototype.
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

//#include <recabs/recabs.h>
#include "recabs_dev.h"
#include "l4_server_bs.h"
#include "l4_client_bs.h"
#include "bs_deserializer.h"

int main(int argc, char const* argv[])
{
    L4ServerBS bs_srv;
    L4ClientBS bs_clt;
    const BSDeserializer bs_deserializer;

    recabs::RecursionManager* manager = recabs::RecursionManager::create_recursion_manager(bs_srv, bs_clt, bs_deserializer);

    manager->start();
    /* Inform result. */
    bs_srv.results_report();

    return 0;
}

