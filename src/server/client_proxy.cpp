/**
 * \file  client_proxy.cpp
 * \brief Implementation file for ClientProxy class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
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

#include "client_proxy.h"
#include "clients_manager.h"
#include "processing_history.h"
#include <syslog.h>
#include "job_manager.h"

using namespace fud;

ClientID ClientProxy::_last_id = 0;

ClientProxy::ClientProxy() :
    _current_id(0),
    _state(kIdle),
    _history(new ProcessingHistory(10)),
    _id(++_last_id)
{
}

ClientProxy::~ClientProxy()
{
}

bool ClientProxy::busy() const
{
    return _state == kBusy;
}

void ClientProxy::i_am_free()
{
    ClientsManager::get_instance()->free_client_event();
}

void ClientProxy::process(const JobUnit& job_unit)
{
    assert(_state == kIdle);

    _current_id = job_unit.get_id();
    _state = kBusy;
    send(job_unit.serialize());
}

void ClientProxy::handle_response(const std::string& message)
{
    InputMessage bis(message);

    ClientHeader header;
    bis >> header;

    std::string     body;
    fud_uint        n_clients;
    OutputMessage   out;
    fud_uint        message_number;

    fud_size size_of_message = 0;

    switch(header)
    {
        case kJobUnitCompleted:
            ClientsManager::get_instance()->inform_completion(_current_id);
            _state = kIdle;
            i_am_free();
            #ifndef RESEND_PENDING_JOBS
                syslog(LOG_NOTICE, "Client %d is free now.", _id);
            #endif
            break;

        case kFreeClientsReq:
            bis >> n_clients;
            n_clients = ClientsManager::get_instance()->handle_free_clients_request(n_clients);
            out.clear();
            size_of_message = HEADER_SIZE + SERVER_HEADER_LENGTH + sizeof(fud_uint);
            out << size_of_message << kFreeClientsResp << n_clients;            
            if (n_clients > 0)
            {
                /* Place orders. */
                ClientsManager::get_instance()->place_orders(n_clients);
                syslog(LOG_NOTICE, "Client %d place orders for %d helpers.", _id, n_clients);
                /* Enqueue free client event. It's going to redistribute JobUnits. */
                ClientsManager::get_instance()->free_client_event();
            }                        
            send(out.str());
            break;

        case kMessage:
            bis >> message_number >> body;
            ClientsManager::get_instance()->inform_incoming_message(_current_id, message_number, new std::string(body) );
            /* Enqueue free client event. It's going to redistribute JobUnits. */
            ClientsManager::get_instance()->free_client_event();
            break;

        default:
            syslog(LOG_NOTICE, "Error receiving message: Header does not exist.");      
    }
}

void ClientProxy::check_incomplete_job()
{
    JobManager::get_instance()->rescue_inclomplete_job_unit(_current_id);
}
