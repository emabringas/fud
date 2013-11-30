/**
 * \file
 * \brief Implementation of AnaClientsManager class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class AnaClientsManager methods
 *                 and embedded (private) class AnaClientProxy. These classes
 *                 handle communication with clients using Boost.Asio. Here is also
 *                 implemented the create_clients_manager method, later linked at
 *                 compile time.
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
#include <sstream>
#include "ana_clients_manager.h"

namespace fud
{

AnaClientsManager::AnaClientsManager(const Port& port) :
    ClientsManager(),
    _server( ana::server::create() )
{
    std::stringstream ss;
    ss << port;

    _server->set_connection_handler( this );
    _server->set_listener_handler( this );

    _server->run( ss.str() );
}

AnaClientsManager::~AnaClientsManager()
{
    _server->cancel_pending();
    delete _server;
}

void AnaClientsManager::handle_connect (ana::error_code ec, ana::net_id id)
{
    if (! ec )
    {
        AnaClientProxy* new_client = new AnaClientProxy(_server);
        new_client->set_id(id);
        register_client( new_client );
    }
}

void AnaClientsManager::handle_receive (ana::error_code    ec,
                                        ana::net_id        id,
                                        ana::read_buffer   buf)
{
    if (! ec )
    {
        InputMessage bis( mili::substr(buf->string(), Pos(0), Count(HEADER_SIZE)) );

        fud_size last_pos;
        bis >> last_pos;

        get_client(id)->handle_response( mili::substr(buf->string(), Pos(HEADER_SIZE), Pos((size_t) last_pos)) );
    }
    else
    {
        syslog(LOG_NOTICE,"Error receiving results in client.");
        //_client_proxies[ id ]->destroy();
    }

}

void AnaClientsManager::handle_disconnect(ana::error_code,
                                          ana::net_id id)
{
    deregister_client( (ClientID) id );
}

// --- Proxy

AnaClientsManager::AnaClientProxy::AnaClientProxy(ana::server* server) :
    ClientProxy(),
    _server( server )
{
}

void AnaClientsManager::AnaClientProxy::send(const std::string& message)
{
    _server->send_one( ana::net_id( get_id() ), ana::buffer(message), this);
}

void AnaClientsManager::AnaClientProxy::handle_send (ana::error_code,
                                                     ana::net_id,
                                                     ana::operation_id)
{
}

ClientsManager* create_clients_manager()
{
    return new AnaClientsManager(31337);
}

} // end namespace
