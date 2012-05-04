/* $Id: serializable_recursive_functor.h 357 2010-11-05 14:42:13Z emab73 $ */

/** 
 *  @file:      serializable_recursive_functor.h
 *  @details    Header file for SerializableRecursiveFunctor and Serializable interfaces.\n
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

#ifndef SERIALIZABLE_RECURSIVE_FUNCTOR_H
#define SERIALIZABLE_RECURSIVE_FUNCTOR_H

#include "common.h"
#include "recursive_functor.h"

namespace recabs
{

    /**
     * Interface that represents serializable classes.
     */
    struct Serializable
    {
        /**
         * Should be serialize its own representation.
         *
         * @returns its representation as a Packet.
         */
        virtual void serialize(Packet& pkt) = 0;
    };

    /**
     * Interface that represents a serializable recursive functor, wich is called to produce
     * their children.
     */
    struct SerializableRecursiveFunctor : public RecursiveFunctor,
                                          public Serializable
    {
        /**
         * Should be fill the children list in inductive case and put the result in base case
         * or inductive case.
         *
         * @param children : the list of RecursiveFuntor to fill, in inductive case.
         * @param result : the packaging result to fill, in base case.
         *
         */
	    virtual void call(ChildrenFunctors& children, Packet& result, WhenToSend& when) = 0;

        /**
         * Should be serialize its own representation.
         *
         * @returns its representation as a Packet.
         */
        virtual void serialize(Packet& pkt) = 0;

    };

}

#endif
