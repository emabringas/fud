/* $Id: binary_search.h 629 2011-09-13 13:54:45Z marjobe $ */

/** 
 *  @file:      binary_search.h
 *  @details    Header file for Recabs providing BinarySearch class.
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

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H


#include <list>
#include "recabs.h"


/** 
 * Class that represent the Binary Search recursive process.
 */
class BinarySearch : public recabs::SerializableRecursiveFunctor
{

    public:
        
        typedef std::list<uint32_t> Elements;

        /** Standar constructor
         * 
         * @param v : Container of elements.
         * @param s : Item to search.
         */
        BinarySearch(Elements& v, uint32_t s);

        /**
         * Destructor.
         */
        ~BinarySearch(){};

        /**
         * Fills the list with its two children functors if the list contains at least two elements. 
         * Otherwise, constructs the corresponding package with the result.
         *
         * @param children : the list of RecursiveFunctor to fill, in inductive case.
         * @param result : the packaging result to fill, in base case or inductive case.
         *
         */
        virtual void call(recabs::ChildrenFunctors& children, recabs::Packet& result, recabs::WhenToSend&);

        /**
         * Serializes a BinarySearch as a packet.
         *
         * @parram packet: Package that will be serialized itself.
         */        
        virtual void serialize(recabs::Packet& pkt);

    private:


        Elements _v;
        uint32_t _searched;

};
       
#endif
