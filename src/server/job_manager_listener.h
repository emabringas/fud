/**
 * @file  job_manager_listener.h
 * @brief Header file for JobManagerListener interface.
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

#ifndef JOB_MANAGER_LISTENER_H
#define JOB_MANAGER_LISTENER_H

namespace fud
{

struct JobManagerListener
{

    /**
     * It should be invoked when a client becomes idle.
     * Requeriment: constantly time.
     */
    virtual void on_idle_client() = 0;

    /**
     * It should be invoked when a client is disconnected.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The disconnected client.
     */
    virtual void on_disconnect_client(ClientID client_id) = 0;

    /**
     * It should be invoked when a result arrives from a single client.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The ID of the client which sent the message.
     * @param[in] message The message arrived. It could be a result or a intermediate message.
     */
    virtual void on_client_message_arrived(ClientID client_id, const Message& message) = 0;

    /**
     * It should be invoked when a JobUnit has ended.
     * Requeriment: constantly time.
     *
     * @param[in] client_id The ID of the client which completes the JobUnit.
     * @param[in] job_unit_id The ID of the completed JobUnit.
     */
    virtual void on_finish_job_unit(ClientID client_id, JobUnitID job_unit_id) = 0;

};

}

#endif /* JOB_MANAGER_LISTENER_H */
