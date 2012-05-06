/**
 * \file  client_proxy.h
 * \brief Definition of ClientProxy class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributableJob.
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

#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "job_unit.h"
#include "common.h"
#include "work_stats.h"


namespace fud
{
    /**
     * A dummy proxy to represent a Client, later on, it will be
     * implemented by private Proxy classes inside a concrete ClientsManager.
     *
     * \sa ClientsManager
     */
    class ClientProxy
    {
    public:
        /**
         * The method in charge of sending the JobUnit to the client calling to process() method.
         *
         * \sa JobUnit
         * \sa ClientsManager
         */    
        void send_to_process(const JobUnit& job_unit);

        /**
         * Check to see if the corresponding client is busy working.
         *
         * @return <b>true</b> if the client attached to this proxy can process other job concurrently,
         * <b>false</b> otherwise.
         */
        inline bool send_me_job() const
        {
            return (_concurrent_jobs == UNLIMITED_JOBS) || (_current_concurrent_jobs < _concurrent_jobs);
        }
        
        /** 
         * This method should be called in the ClientsManager implementation to 
         * setup the maximum number of concurrent jobs that this client can process.
         */
        void set_concurrent_jobs(fud_uint concurrent_jobs_number);

        /**
         * Get the ClientID of the current proxy.
         *
         * @returns The ID of the connected client.
         *
         * \sa ClientID
         */
        inline  ClientID get_id() const
        {
            return _id;
        }

        /**
         * Returns the collected data on previous works performed.
         * This data may represent many different things.
         *
         * @return A reference to the accumulated WorkHistory.
         *
         * \sa WorkHistory
         */
        inline  WorkHistory& history()
        {
            return *_history;
        }

        virtual ~ClientProxy();

    protected:
        /**
         * Default constructor, will increment the ids of ClientProxies while
         * assigning.
         */
        ClientProxy();

        /**
         * The method in charge of sending the JobUnit to the client.
         * Implementation depends on the type of ClientsManager used.
         *
         * \sa JobUnit
         * \sa ClientsManager
         */
        virtual void process(const JobUnit& job_unit) = 0;

        /** Issues a free_client_event to the corresponding listener.
         *
         * \sa free_client_event()
         */
        void    finish_one_job();// ex i_am_free() method;
        
    private:
        WorkHistory* const _history;
        static ClientID    _last_id;
        ClientID            _id;
        
        /** Indicates the total concurrents jobs of this client. The value 0 indicates that this client can 
         *  process a number undefined of concurrent jobs (designed for BOINC). This attribute should be modify when 
         *  a ClientProxy is created.
         */
        fud_uint            _concurrent_jobs;
        
        /** 
         * Indicates the current concurrent jobs of this client
         */
        fud_uint            _current_concurrent_jobs;
    };
}

#endif

