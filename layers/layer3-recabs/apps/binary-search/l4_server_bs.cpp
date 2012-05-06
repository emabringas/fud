/* $Id: l4_server_bs.cpp 629 2011-09-13 13:54:45Z marjobe $ */

/**
 *  @file:      l4_server_bs.cpp
 *  @details    Implementation file for L4ServerBS class.\n
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


#include <mili/mili.h>
#include "l4_server_bs.h"
#include "binary_search.h"
#include <string>

L4ServerBS::L4ServerBS()
{
    _result = false;
}

void L4ServerBS::get_initial_packet(recabs::Packet& pkt) const
{
    BinarySearch::Elements v;

    for (uint32_t i = 0; i < 1000; i++)
        mili::insert_into(v, i);

    BinarySearch b(v, -1);

    b.serialize(pkt);
}

int count_results = 0;
int count_message = 0;

void L4ServerBS::receive_result(const recabs::Packet& pkt)
{
    count_results++;

    mili::bistream<> bis(pkt);
    bool res;
    bis >> res;
//    std::cout << "Llego el resultado nro " << count_results << std::endl;
    _result = (_result || res);
}

void L4ServerBS::receive_message(const recabs::Packet&)
{
    count_message++;
    std::cout << "Llego un mensaje" << count_message << std::endl;
}

void L4ServerBS::results_report() const
{
    std::string out;
    if (_result)
        out = "True";
    else
        out = "False";
    std::cout << out << ", " << count_results << " results and " << count_message << " messages has been sent." << std::endl;
}
