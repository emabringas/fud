/**
 * @file  delegator.h
 * @brief Header file for Delegator class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2012 - Mariano Bessone & Lucas Besso, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * @author     Mariano Bessone
 * @email      marjobe AT gmail.com
 *
 * @author     Lucas Besso
 * @email      lbesso AT gmail.com
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

#ifndef DELEGATOR_H
#define DELEGATOR_H

#include "job_manager_listener.h"
#include "clients_request_listener.h"
#include "common.h"


namespace fud
{

class Delegator : private ClientsEventListener
{

    public:

        Delegator( JobManagerListener const * job_manager_listener,
                   ClientsRequestListener const * clients_request_listener );

        /**
         * Destructor.
         */
        virtual ~Delegator() {};

    private:

        /**
         * Handle message depending on the message type.
         *
         * @param[in] client_id The ID of the client which sent the message.
         * @param[in] header The header of the message.
         * @param[in] message The message to handle.
         */
        void handle_message(ClientID client_id, const Header& header, const Message& mesage);

        /** Methods of ClientsEventListener interface. */
        void on_idle_client(ClientID client_id);
        void on_disconnect_client(ClientID client_id);
        void on_arrive_message(ClientID client_id, const Message& message);

        /** Listeners. */
        JobManagerListener const *        _job_manager_listener;
        ClientsRequestListener const *    _clients_request_listener;

};

}

#endif /* DELEGATOR_H */

