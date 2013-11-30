/**
 * \file  clients_manager.cpp
 * \brief Implementation file for ClientsManager class.
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

#include <syslog.h>
#include <map>

#include <boost/bind.hpp>

#include "fud/server/clients_manager.h"
#include "fud/common/common.h"

using namespace fud;

ClientsManager* ClientsManager::_instance = NULL;

ClientsManager::ClientsManager() :
    _client_proxies(),
    _client_proxies_mutex(),
    _listener(NULL),
    _free_clients(0),
    _available_clients(0),
    _reservations(0)
{
    _instance = this;
}

ClientsManager::~ClientsManager()
{
    for (std::map<ClientID, ClientProxy*>::iterator it(_client_proxies.begin()); it != _client_proxies.end(); it++)
        delete it->second;
}

void ClientsManager::register_client(ClientProxy* client)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    syslog(LOG_NOTICE,"Registering client %u.",client->get_id());
    _client_proxies.insert( std::pair<ClientID, ClientProxy*>(client->get_id(), client) );
    _listener->free_client_event();
    _free_clients++;
    _available_clients++;
}

void ClientsManager::deregister_client(ClientID id)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    syslog(LOG_NOTICE,"Deregistering client %u.",id);
    if (!get_client(id)->busy())
        _free_clients--;

    /* Reset reservations. This is a trivial solution to the
     * reserve-and-disconect problem.
     */
    _available_clients = _free_clients;
    _reservations = 0;

    ClientProxy* client_to_disconect = get_client(id);

    #ifndef RESEND_PENDING_JOBS
        client_to_disconect->check_incomplete_job();
    #endif

    delete client_to_disconect;
    _client_proxies.erase(id);

}

void ClientsManager::free_client_event()
{
    _listener->free_client_event();
}

void ClientsManager::inform_completion(JobUnitID id)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    _listener->job_unit_completed_event(id);
    _free_clients++;
    _available_clients++;
}

void ClientsManager::inform_incoming_message(JobUnitID id, fud_uint message_number, std::string* message)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    _listener->incoming_message_event(id, message_number, message);
}

void ClientsManager::set_listener(ClientsManagerListener* const listener)
{
    _listener = listener;
}

bool ClientsManager::assign_job_unit (const JobUnit& job_unit)
{
    ClientProxy* client(get_available_client());
    if (client != NULL)
    {
        /* At least, there is a reserve or a client available. */
        assert(orders() > 0 || _available_clients > 0);

        client->process(job_unit); //on the same thread, works asynchronously
        syslog(LOG_NOTICE, "Assigned Job Unit %d to client %d.", job_unit.get_id(), client->get_id());
        _free_clients--;
        if (orders() > 0)
            take_an_order();
        else
            _available_clients--;
        return true;
    }
    else
    {
        syslog(LOG_NOTICE,"There are no clients available.");
        return false;
    }
}


ClientProxy* ClientsManager::get_available_client()
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    if (_client_proxies.size() == 0)
        return NULL;
    else
    {
        std::map<ClientID, ClientProxy*>::iterator it = _client_proxies.begin();
        bool found(false);
        while (it != _client_proxies.end() && !found)
        {
            found = ! (it->second)->busy();
            if (!found)
                it++;
        }

        if (found)
        {
            return it->second;
        }
        else
            return NULL;
    }
}

fud_uint ClientsManager::handle_free_clients_request(fud_uint clients_requested)
{
    return std::min(_available_clients, clients_requested);
}

ClientProxy* ClientsManager::get_client(ClientID id)
{
    return _client_proxies[id];
}

void ClientsManager::place_orders(fud_uint count)
{
    for (unsigned int i = 0; i < count; i++)
        place_an_order();
}

void ClientsManager::place_an_order()
{
    _reservations++;
    _available_clients--;
}

void ClientsManager::take_an_order()
{
    _reservations--;
}

fud_uint ClientsManager::orders()
{
    return _reservations;
}
