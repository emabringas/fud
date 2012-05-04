/**
 * \file  clients_manager.cpp
 * \brief Implementation file for ClientsManager class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
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

#include <algorithm>
#include <syslog.h>

#include <boost/bind.hpp>

#include "clients_manager.h"

using namespace fud;

ClientsManager* ClientsManager::_instance = NULL;

ClientsManager::ClientsManager() :
    _client_proxies(),
    _client_proxies_mutex(),
    _listener(NULL)
{
    _instance = this;
}

void ClientsManager::register_client(ClientProxy* client)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    syslog(LOG_NOTICE,"Registering client %u.",client->get_id());
    _client_proxies.push_back(client);
    _listener->free_client_event();
}

void ClientsManager::deregister_client(ClientProxy* client)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    syslog(LOG_NOTICE,"Deregistering client %u.",client->get_id());
    _client_proxies.remove(client);
    delete client;
}

void ClientsManager::free_client_event()
{
    _listener->free_client_event();
}

void ClientsManager::inform_completion(JobUnitID id, std::string* message)
{
    boost::mutex::scoped_lock glock(_client_proxies_mutex);
    _listener->job_unit_completed_event(id, message);
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
        client->process(job_unit); //on the same thread, works asynchronously
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
        std::list<ClientProxy *>::iterator it;

        it = find_if (_client_proxies.begin(), _client_proxies.end(),
                    !boost::bind(&ClientProxy::busy, _1) );

        if (it != _client_proxies.end())
        {
            ClientProxy* result(*it);
            _client_proxies.erase(it);
            _client_proxies.push_back(result);
            return result;
        }
        else
            return NULL;
    }
}
