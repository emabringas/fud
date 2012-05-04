/* $Id: binary_search.cpp 357 2010-11-05 14:42:13Z emab73 $ */

/**
 *  @file:      binary_search.cpp
 *  @details    Implementation file for BinarySearch class.
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

#include <iostream>
#include <mili/mili.h>
#include "binary_search.h"

BinarySearch::BinarySearch(Elements& v, int s) :
    _v(v),
    _searched(s)
{
}

void BinarySearch::call(recabs::ChildrenFunctors& children, recabs::Packet& result, recabs::WhenToSend& when)
{
    mili::bostream bos;

    // Caso base 1
    if (_v.empty())
    {
        bos << false;
        result = bos.str();
        when = recabs::kSendWhenYouWant;
    }

    // Caso base 2
    if (int (_v.size()) == 1)
    {
        bos << (_v.front() == _searched);
        result = bos.str();
        when = recabs::kSendWhenYouWant;
    }
    // Caso Inductivo
    else
    {
        unsigned int middle = _v.size() / 2;

        Elements::iterator it = _v.begin();
        advance(it, middle);

        Elements leftChild(_v.begin(), it);
        Elements rightChild(it++, _v.end());

        mili::insert_into(children, new BinarySearch(leftChild, _searched));
        mili::insert_into(children, new BinarySearch(rightChild, _searched));
    }
}

void BinarySearch::serialize(recabs::Packet& pkt)
{
    mili::bostream bos;
    bos << this->_v << this->_searched;
    pkt = bos.str();
}

