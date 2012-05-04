/* $Id: bs_deserializer.h 567 2011-06-07 20:06:32Z marjobe $ */

/** 
 *  @file:      bs_deserializer.h
 *  @details    Header file for Recabs providing BSDeserializer class.
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

#ifndef BS_DESERIALIZER_H
#define BS_DESERIALIZER_H

#include "recabs.h"

/**
 *  Concrete class to deserialize BinarySearchs.
 */
class BSDeserializer : public recabs::DeserializerFunctor
{
    public:
    
        /**
         *  Constructor method.
         */
        BSDeserializer(){};

        /**
         *  Extract functor from the given packet.
         *  @param pkt : the packet containing the serialized BinarySearch.
         *  @param rf : the BinarySearch as a result of deserialization.
         */
        virtual void deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const;

};

#endif

