/* $Id: deserializer_functor.h 326 2010-10-04 16:49:47Z marjobe $ */

/** 
 *  @file:      deserializer_functor.h
 *  @details    Header file for Recabs providing DeserializerFunctor class.
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

#ifndef DESERIALIZER_FUNCTOR_H
#define DESERIALIZER_FUNCTOR_H

#include "common.h"
#include "serializable_recursive_functor.h"

namespace recabs
{
    /**
     *  Interface for deserialization of functors.
     */
    class DeserializerFunctor
    {

        public:

            /**
             *  Should be extract functor from the given packet.
             *  @param p : the packet containing the serialized functor.
             *  @param rf : the functor as a result of deserialization.
             */
            virtual void deserialize(const Packet& p, SerializableRecursiveFunctor** rf) const = 0;

    };

}

#endif
