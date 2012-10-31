/**
 * @file  clients_event_listener.h
 * @brief Header file for ClientsEventListener interface.
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

#ifndef CLIENTS_EVENT_LISTENER_H
#define CLIENTS_EVENT_LISTENER_H

#include "common.h"

namespace fud
{

/**
 * Interface which declares method to listen events of the clients.
 */
struct ClientsEventListener
{

    /**
     * It should be invoked when a client is idle.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The ID of the idle client.
     */
    virtual void on_idle_client(ClientID client_id) = 0;

    /**
     * It should be invoked when a client is disconnected.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The disconnected client.
     */
    virtual void on_disconnect_client(ClientID client_id) = 0;

    /**
     * It should be invoked when a message arrived from a single client.
     * It should be handled depending on the message type.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The client message owner.
     * @param[in] message The message arrived.
     */
    virtual void on_arrive_message(ClientID client_id, const Message& message) = 0;

};

}

#endif
