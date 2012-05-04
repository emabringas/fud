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
             * The method in charge of sending the JobUnit to the client.
             * Implementation depends on the type of ClientsManager used.
             *
             * \sa JobUnit
             * \sa ClientsManager
             */
            virtual void process(const JobUnit& job_unit) = 0;

            /**
             * Check to see if the corresponding client is busy working.
             *
             * @return <b>true</b> if the client attached to this proxy is busy
             *         working, <b>false</b> otherwise.
             */
            virtual bool busy() const = 0;

            /**
             * Get the ClientID of the current proxy.
             *
             * @returns The ID of the connected client.
             *
             * \sa ClientID
             */
            inline  ClientID get_id() const {return _id;}

            /**
             * Returns the collected data on previous works performed.
             * This data may represent many different things.
             *
             * @return A reference to the accumulated WorkHistory.
             *
             * \sa WorkHistory
             */
            inline  WorkHistory& history()  {return *_history;}

            virtual ~ClientProxy();

        protected:
            /**
             * Default constructor, will increment the ids of ClientProxies while
             * assigning.
             */
            ClientProxy();

            /** Issues a free_client_event to the corresponding listener.
             *
             * \sa free_client_event()
             */
            void    i_am_free();

        private:
            WorkHistory* const _history;
            static ClientID    _last_id;
            ClientID           _id;
    };
}

#endif