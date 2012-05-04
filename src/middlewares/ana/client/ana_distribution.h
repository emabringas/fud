/**
 * \file
 * \brief Definition of AnaDistribution class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AnaDistribution.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * @author     Guillermo Biset
 * @email      billybiset AT gmail.com
 *  
 * @author     Mariano Bessone
 * @email      marjobe AT gmail.com
 *
 * @author     Emanuel Bringas
 * @email      emab73 AT gmail.com
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

#ifndef ANA_DISTRIBUTION_H
#define ANA_DISTRIBUTION_H

#include <boost/thread.hpp>

#include <ana/ana.hpp>

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
    class AnaDistribution : public DistributionClient,
                            public ana::connection_handler,
                            public ana::listener_handler,
                            public ana::send_handler
    {
        public:
            /**
             * Standard constructor.
             *
             * @param address : Address to try to connect to. The server should be there.
             * @param port : Port to use for the connection. The server should have opened it.
             */
            AnaDistribution(std::string address, Port port);

            /**
             * Start communication. It will try to connect to the server using
             * the address:port combination.
             *
             * If the connection is succesful, it will listen for incoming messages.
             */
            virtual void run();

            /**
             * Sends a string to the server.
             *
             * @param out : string to send.
             */
            virtual void dispatch(const std::string& out);


        private:
            /* Override, as per -Weffc++ */
            AnaDistribution(const AnaDistribution& other);
            AnaDistribution& operator= (const AnaDistribution& other);

            // ANA handlers
            virtual void handle_connect   (ana::error_code, ana::net_id);

            virtual void handle_receive   (ana::error_code, ana::net_id, ana::read_buffer);
            virtual void handle_disconnect(ana::error_code, ana::net_id);

            virtual void handle_send      (ana::error_code, ana::net_id, ana::operation_id);

            ana::client* _client;

    };
}

#endif
