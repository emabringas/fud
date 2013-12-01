/**
 * \file  async_io_clients_manager.h
 * \brief Definition of AsyncIOClientsManager class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AsyncIOClientsManager.
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

#ifndef ASYNC_IO_CLIENTS_MANAGER_H
#define ASYNC_IO_CLIENTS_MANAGER_H

#include <boost/asio.hpp>
#include "fud/common/common.h"
#include "fud/common/job_unit.h"
#include "fud/server/clients_manager.h"
#include "fud/server/client_proxy.h"

using boost::asio::ip::tcp;

namespace fud
{
    /**
     * The communication part of the server. Uses the boost
     * libraries asynchronous input/output library, or <b>asio</b>.
     *
     * Check the library's <a href="www.boost.org/doc/libs/release/libs/asio/"> homepage </a>.
     *
     * \sa ClientsManager
     */
    class AsyncIOClientsManager : public ClientsManager
    {
        public:
            /**
             * Standard constructor.
             *
             * @param port : The port to be used. Should be in the allowed range.
             */
            AsyncIOClientsManager(const Port& port);

            ~AsyncIOClientsManager(){};
        private:
            /**
             * A concrete ClientProxy using this distributing middleware.
             *
             * \sa ClientProxy
             */
            class AsyncIOClientProxy : public ClientProxy
            {
                public:
                    /**
                     * Standard constructor.
                     *
                     * @param io_service : The boost::asio::io_service object used in
                     *                     the communication.
                     */
                    AsyncIOClientProxy(boost::asio::io_service& io_service);

                    /**
                     * Runs the listener thread for the current client proxy.
                     */
                    virtual void run();

                    virtual ~AsyncIOClientProxy() {};

                    /** The socket used for communication. */
                    tcp::socket& socket();
                private:

                    virtual void send(const std::string& message);

                    /* Asynchrono handler */
                    void handle_receive();

                    void destroy();

                    tcp::socket  _socket;
                    boost::mutex _proxy_mutex;
            };

            /* Asynchronous handler, calls itself recursively */
            void handle_accept (const boost::system::error_code& ec,AsyncIOClientProxy* client);

            /* To register clients */
            static void run_acceptor_thread(AsyncIOClientsManager* obj);

            void run_and_die();

            void _async_accept();

            /* attr.*/
            boost::asio::io_service _io_service;
            tcp::acceptor           _acceptor;
    };
}
#endif
