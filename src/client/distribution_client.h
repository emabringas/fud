/**
 * \file  distribution_client.h
 * \brief Definition of class DistributionClient.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributionClient.
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

#ifndef DISTRIBUTION_CLIENT_H
#define DISTRIBUTION_CLIENT_H

#include <string>

#include "common.h"

namespace fud
{
    /**
     * Abstract class for Client Communication.
     * Concrete subclasses will depend on the actual distributing middleware.
     * Implements a Singleton pattern.
     *
     * \sa AsyncIODistribution
     */
    class DistributionClient
    {
        public:
            /**
             * Starts the communication part of the client application.
             * It should try to connect to the server for registration and
             * then wait incoming messages.
             */
            virtual void run()                      = 0;

            /**
             * Returns the results of the processing of a message.
             *
             * @param result : If there wasn't an error during computation. If this
             * is true then it will send the message with the results.
             */
            virtual void inform_result(bool result) = 0;

            virtual ~DistributionClient(){}

            /** Singleton method. */
            static DistributionClient*  get_instance() {return _instance; }
        protected:
            DistributionClient() {_instance = this; }
        private:
            static DistributionClient*  _instance;
    };

    /**
     * Factory method for the creation of a DistributionClient instance.
     * The implementation file for the subclass of DistributionClient should implement
     * this method and create itself.
     *
     * @param address : Address to look for the server.
     * @param port : Port to look for FuD in the given address.
     */
    DistributionClient* create_distribution_client(std::string address = "127.0.0.1", Port port = 31337);
}

#endif