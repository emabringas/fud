/**
 * \file  client_proxy.h
 * \brief Definition of ClientProxy class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributableJob.
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

#ifndef CLIENT_PROXY_H
#define CLIENT_PROXY_H

#include "fud/common/job_unit.h"
#include "fud/common/common.h"
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
             *
             * \sa JobUnit
             * \sa ClientsManager
             */
            virtual void process(const JobUnit& job_unit);

            /**
             *  Send to the client the given message
             */
            virtual void send(const std::string& message) = 0;

            /**

             * Check to see if the corresponding client is busy working.
             *
             * @return <b>true</b> if the client attached to this proxy is busy
             *         working, <b>false</b> otherwise.
             */
            virtual bool busy() const;

            /**
             * Get the ClientID of the current proxy.
             *
             * @returns The ID of the connected client.
             *
             * \sa ClientID
             */
            inline ClientID get_id() const {return _id;}

            /**
             * Get the ClientID of the current proxy.
             *
             * @returns The ID of the connected client.
             *
             * \sa ClientID
             */
            inline void set_id(ClientID id) {_id = id;}

            /**
             * Returns the collected data on previous works performed.
             * This data may represent many different things.
             *
             * @return A reference to the accumulated WorkHistory.
             *
             * \sa WorkHistory
             */
            inline  WorkHistory& history()  {return *_history;}

 
            /**
             * Handles incoming message.
             *
             * @param message : the message to handle.
             */
            virtual void handle_response(const std::string& message);
            
            /**
             *  Verify if JobUnit given is incomplete and in this case enqueue to job queue.
             */
            virtual void check_incomplete_job();            

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

            /* Attributes that implementations classes maybe handles it. */
            JobUnitID       _current_id;
            ClientState     _state;

        private:
            WorkHistory* const  _history;
            static ClientID     _last_id;
            ClientID            _id;

    };
}

#endif
