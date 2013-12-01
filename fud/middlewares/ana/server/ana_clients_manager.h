/**
 * \file
 * \brief Definition of AnaClientsManager class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AnaClientsManager.
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

#ifndef ANA_CLIENTS_MANAGER_H
#define ANA_CLIENTS_MANAGER_H

#include <map>
#include <ana/ana.hpp>
#include "fud/common/common.h"
#include "fud/common/job_unit.h"
#include "fud/server/clients_manager.h"
#include "fud/server/client_proxy.h"

namespace fud
{
    /**
     * The communication part of the server. Uses the boost
     * libraries asynchronous input/output library, or <b>asio</b>.
     *
     * Check the library's <a href="www.boost.org/doc/libs/release/libs/asio/"> homepage </a>
     *
     * \sa ClientsManager
     */
    class AnaClientsManager : public ClientsManager,
                              public ana::connection_handler,
                              public ana::listener_handler
    {
        public:
            /**
             * Standard constructor.
             *
             * @param port : The port to be used. Should be in the allowed range.
             */
            AnaClientsManager(const Port& port);

            virtual ~AnaClientsManager();
        private:

            virtual void handle_connect   (ana::error_code, ana::net_id);

            virtual void handle_receive   (ana::error_code, ana::net_id, ana::read_buffer);
            virtual void handle_disconnect(ana::error_code, ana::net_id);

            /**
             * A concrete ClientProxy using this distributing middleware.
             *
             * \sa ClientProxy
             */
            class AnaClientProxy :  public ClientProxy,
                                    public ana::send_handler
            {
                public:
                    /**
                     * Standard constructor.
                     */
                    AnaClientProxy(ana::server* server);

                    virtual ~AnaClientProxy() {};
                private:
                    virtual void send(const std::string& message);

                    virtual void handle_send      (ana::error_code, ana::net_id, ana::operation_id);

                    ana::server*   _server;
            };

            ana::server* _server;

    };
}
#endif
