/* $Id: recursive_processor.h 589 2011-07-14 18:25:31Z marjobe $ */

/** 
 *  @file:      recursive_processor.h
 *  @details    Header file for Recabs providing class RecursionProcessor.
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

#ifndef RECURSIVE_PROCESSOR_H
#define RECURSIVE_PROCESSOR_H

#include "common.h"

namespace recabs
{

/**
 *  Abstract class that represent a processing node of RecursiveFunctors.
 */
class RecursiveProcessor
{
    public:

        /**
         * Should be implemented as a way to start the exectution of a single node.
         * @param address : if it will not run locally, set this with the server address.
         * @param port : if it will not run locally, set this with the server port.
         */
        virtual void run(const Address& address = LOCALHOST, Port port = DEFAULT_PORT) = 0;

};

}

#endif
