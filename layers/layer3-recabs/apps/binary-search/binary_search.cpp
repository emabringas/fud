/* $Id: binary_search.cpp 629 2011-09-13 13:54:45Z marjobe $ */

/**
 *  @file:      binary_search.cpp
 *  @details    Implementation file for BinarySearch class.
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

#include <iostream>
#include <mili/mili.h>
#include "binary_search.h"

BinarySearch::BinarySearch(Elements& v, uint32_t s) :
    _v(v),
    _searched(s)
{
}

void BinarySearch::call(recabs::ChildrenFunctors& children, recabs::Packet& result, recabs::WhenToSend&)
{
    /* By default: when = recabs::kSendWhenRecAbsWants; */

    /* Base case 1 */
    if (_v.empty())
    {
        mili::bostream<> bos;
        bos << false;
        result = bos.str();
    }

    /* Base case 2 */
    if (uint32_t (_v.size()) == 1)
    {
        mili::bostream<> bos;
        bos << (_v.front() == _searched);
        result = bos.str();
    }
    /* Inductive case */
    else
    {
        Elements::iterator it = _v.begin();
        advance(it, _v.size() / 2);

        Elements leftChild(_v.begin(), it);
        Elements rightChild(it++, _v.end());

        mili::insert_into(children, new BinarySearch(leftChild, _searched));
        mili::insert_into(children, new BinarySearch(rightChild, _searched));
    }
}

void BinarySearch::serialize(recabs::Packet& pkt)
{
    mili::bostream<> bos;
    bos << this->_v << this->_searched;
    pkt = bos.str();
}

