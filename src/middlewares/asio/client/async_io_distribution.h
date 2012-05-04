/**
 * \file  async_io_distribution.h
 * \brief Definition of AsyncIODistribution class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AsyncIODistribution.
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

#ifndef ASYNC_IO_DISTRIBUTION_H
#define ASYNC_IO_DISTRIBUTION_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

#include "common.h"
#include "distribution_client.h"

namespace fud
{
    /**
     * The communication part of the client application. Uses the boost
     * libraries asynchronous input/output library, or <b>asio</b>.
     *
     * Check the library's <a href="www.boost.org/doc/libs/release/libs/asio/"> homepage </a>.
     *
     * \sa DistributionClient
     */
    class AsyncIODistribution : public DistributionClient
    {
        public:
            /**
             * Standard constructor.
             *
             * @param address : Address to try to connect to. The server should be there.
             * @param port : Port to use for the connection. The server should have opened it.
             */
            AsyncIODistribution(std::string address, Port port);

            /**
             * Start communication. It will try to connect to the server using
             * the address:port combination.
             *
             * If the connection is succesful, it will listen for incoming messages.
             */
            virtual void run();
        private:
            /* Override, as per -Weffc++ */
            AsyncIODistribution(const AsyncIODistribution& other);
            AsyncIODistribution& operator= (const AsyncIODistribution& other);

            virtual void inform_result(bool result);

            void wait_for_job_unit();

            /*attr*/
            tcp::socket* _socket;
            std::string  _address;
            Port         _port;
    };
}

#endif