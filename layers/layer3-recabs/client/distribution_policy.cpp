/* $Id: distribution_policy.cpp 607 2011-08-04 03:47:06Z marjobe $ */

/**
 *  @file:      distribution_policy.cpp
 *  @details    Implementation file for Distribution Policies classes.
 *              System: RecAbs\n
 *              Language: C++\n
 *
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       June 2011
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

#include "distribution_policy.h"
#include <cmath>
#include <assert.h>

using namespace recabs;
using recabs::uint;

uint DistributeAlwaysAllPolicy::how_much_distribute(uint n_children, uint) const
{
    if (n_children == 0)
        return 0;
    else
        return n_children-1;
}

uint DistributeRandomPolicy::how_much_distribute(uint n_children, uint) const
{
    if (n_children == 0)
        return 0;
    else
    {
        mili::Randomizer<uint> rnd(0, n_children-1);
        return rnd.get();        
    }
}

Sigmoid::Sigmoid(uint leafs, float request_index) :
    _leafs(leafs),
    _request_index(request_index)
{
    assert(leafs > 0);
    assert(_request_index > 0 && _request_index < 1);
}

uint Sigmoid::how_much_distribute(uint n_children, uint depth) const
{
    /* Cases analysis */
    if (n_children == 0)
        return 0;
    else
    {
        /* fooplot: [hijos]-1/(1+e^(-log([hijos], [leafs])*[request_index] + x)) ) */
        const float sunset_depth = ( log10(_leafs) / log10(n_children) ) * _request_index;
        const uint value = (uint) roundf( (n_children - 1) / (1 + exp(-sunset_depth + depth - (n_children - 1))) );
        assert(value < n_children);
        return value;
    }
}

FixedLeafsDistributablePolicy::FixedLeafsDistributablePolicy(uint leafs, float request_index) :
    Sigmoid(leafs, request_index)
{
}

MovingAverageLeafsDistributablePolicy::MovingAverageLeafsDistributablePolicy(float request_index) :
    Sigmoid(AVERAGE, request_index)
{
}

