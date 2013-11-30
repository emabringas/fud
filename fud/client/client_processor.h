/**
 * \file  client_processor.h
 * \brief Definition of class ClientProcessor.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class ClientProcessor.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 * FuD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FuD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FuD.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CLIENT_PROCESSOR_H
#define CLIENT_PROCESSOR_H

#include <string>
#include <boost/thread.hpp>
#include "fud/common/common.h"
#include "fud/common/job_unit.h"

namespace fud
{
    /**
     * Abstract class that represents a processing node or client.
     * All client computations will be carried out by concrete instances
     * of this class.
     */
    class ClientProcessor
    {
        public:
            /**
             * Computes the results of the message in input, and saves a message to output.
             *
             * @param input : The message coming from the server.
             * @param output : The message that goes to the server. Contains the results.
             *
             * @returns true if and only if the computation was done succesfuly.
             */
            virtual bool process(InputMessage& input, OutputMessage& output) = 0;

            virtual ~ClientProcessor();
        protected:
            ClientProcessor();
    };
}
#endif