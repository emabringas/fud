/**
 * \file  optimized_container.h
 * \brief Template of optimized container.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2011 Martín Ramiro Gioiosa
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing class Antiviral.
 *
 * System:         ASO
 * Language:       C++
 *
 * Author:         Martín Ramiro Gioiosa
 * E-Mail:         giomartinr@gmail.com
 *
 * ASO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ASO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ASO.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OPTIMIZED_CONTAINER_H
#define OPTIMIZED_CONTAINER_H

#include <mili/mili.h>
#include <functional>

enum ComparisonPolicy
{
    MinimumValues,
    MaximumValues
};

enum ZeroPolicy
{
    NotIncludingZero,
    IncludingZero
};

template<ComparisonPolicy compare, class Scalar> // default: MinimumValues
struct CompFunctor
{
    typedef std::less_equal<Scalar> functor;
};
template<class Scalar>
struct CompFunctor<MaximumValues, Scalar>
{
    typedef std::greater_equal<Scalar> functor;
};

template<ZeroPolicy Zero, class Scalar>   // default: NotIncludingZero
struct ZeroFunctor
{
    static bool proceedIfZero(Scalar s)
    {
        return s != Scalar(0);
    }
};
template<class Scalar>
struct ZeroFunctor<IncludingZero, Scalar>
{
    static bool proceedIfZero(Scalar /*s*/)
    {
        return true;
    }
};

template<class Container, class Scalar, ComparisonPolicy Compare, ZeroPolicy Zero>
class OptimizedContainer
{
    Container& cont;
    Scalar value;
    typename CompFunctor<Compare, Scalar>::functor comp;
    typedef ZeroFunctor<Zero, Scalar> zero_comp;

public:
    OptimizedContainer(Container& cont, Scalar initialValue)
        : cont(cont), value(initialValue)
    {}

    void add(typename Container::const_reference element, Scalar elementValue)
    {
        if (zero_comp::proceedIfZero(elementValue) && comp(elementValue, value))
        {
            /* En caso que el elemento pasado sea mejor que el actual */
            if (value != elementValue)
            {
                cont.clear();
                value = elementValue;
            }

            insert_into(cont, element);
        }
    }

    Scalar getBestValue() const
    {
        return value;
    }
};

#endif
