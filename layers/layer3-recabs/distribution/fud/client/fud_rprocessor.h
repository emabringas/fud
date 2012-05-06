/* $Id: fud_rprocessor.h 611 2011-08-04 13:31:03Z marjobe $ */

/** 
 *  @file:      fud_rprocessor.h
 *  @details    Header file for FuDRProcessor class.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       March 2011
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

#ifndef FUD_PROCESSOR_H
#define FUD_PROCESSOR_H

#include <fud/fud_client.h>
#include "common.h"
#include "distributable_recursive_processor.h"
#include "deserializer_functor.h"

namespace recabs
{

/**
 * Concrete class that represents a FuD manager of recursion.
 */
class FuDRProcessor  :  public DistributableRecursiveProcessor,
                        public fud::ClientProcessor
{
    public:

        /**
         * Constructor.
         *
         * @param app : the concrete L4ServerApp that handles the results.
         */
        FuDRProcessor(const L4ClientApp& app, const DeserializerFunctor& df, const DistributablePolicy& dp);
        
        /**
         * Destructor.
         */
        virtual ~FuDRProcessor();

        /**
         *  Should be implemented as a way to start the exectution of a single node.
         */
        virtual void run(const Address& address = LOCALHOST, Port port = DEFAULT_PORT);

    protected:

        /* ClientProcessor method to implement */
        virtual bool process(fud::InputMessage& input, fud::OutputMessage&);

        /**
         *  Ask to the FuD server if exists n clients.
         *  @param n: the number of helpers needed.
         *
         *  @return the number of clients that the FuD server give us.
         */ 
        virtual uint collaborators(uint n);
        
        /** FuD DistributionClient attribute. */
        fud::DistributionClient* _distribution_client;

};

}

#endif

