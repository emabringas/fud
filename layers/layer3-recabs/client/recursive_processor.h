/* $Id: recursive_processor.h 282 2010-09-01 18:59:34Z marjobe $ */

/** 
 *  @file:      recursive-processor.h
 *  @details    Header file for Recabs providing class RecursionProcessor.
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

#ifndef RECURSIVE_PROCESSOR_H
#define RECURSIVE_PROCESSOR_H

#include "recursive_functor.h"

namespace recabs
{
    /**
     *  Abstract class that represent a processing node of RecursiveFunctors.
     */
    class RecursiveProcessor
    {
        public:

            /**
             *  Should be implemented as a way to start the exectution of a single node.
             */
            virtual void start() = 0;         
            
    };

}

#endif
