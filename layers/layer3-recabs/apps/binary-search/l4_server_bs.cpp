/* $Id: l4_server_bs.cpp 357 2010-11-05 14:42:13Z emab73 $ */

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

    mili::insert_into(v, 6);
    mili::insert_into(v, 8);
    mili::insert_into(v, 6);
    mili::insert_into(v, 4);
    mili::insert_into(v, 9);
    mili::insert_into(v, 6);
    mili::insert_into(v, 2);
    mili::insert_into(v, 1);
    mili::insert_into(v, 5);
    mili::insert_into(v, 7);

    BinarySearch b(v, 7);

    b.serialize(pkt);
}

void L4ServerBS::receive_result(const recabs::Packet& pkt)
{
    mili::bistream bis(pkt);
    bool res;
    bis >> res;
    _result = (_result || res);
}

void L4ServerBS::results_report() const
{
    std::string out;
    if (_result)
        out = "True";
    else
        out = "False";
    std::cout << out << std::endl;
}
