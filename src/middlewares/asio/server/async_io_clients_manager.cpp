/**
 * \file  async_io_clients_manager.cpp
 * \brief Implementation of AsyncIOClientsManager class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class AsyncIOClientsManager methods
 *                 and embedded (private) class AsyncIOClientProxy. These classes
 *                 handle communication with clients using Boost.Asio. Here is also
 *                 implemented the create_clients_manager method, later linked at
 *                 compile time.
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

#include <syslog.h>
#include <memory>
#include <boost/thread.hpp>
#include "async_io_clients_manager.h"

using boost::asio::ip::tcp;

namespace fud
{

AsyncIOClientsManager::AsyncIOClientsManager(const Port& port) :
    _io_service(),
    _acceptor(_io_service, tcp::endpoint(tcp::v4(), port))
{
    // To connect clients
    boost::thread acceptor( boost::bind( &AsyncIOClientsManager::run_acceptor_thread, this));
}

void AsyncIOClientsManager::run_acceptor_thread(AsyncIOClientsManager* obj)
{
    obj->_async_accept();
    obj->run_and_die();
    //Each connection springs recursively another async_accept, so this won't finish.
}

void AsyncIOClientsManager::run_and_die()
{
    _io_service.run();
}

void AsyncIOClientsManager::_async_accept()
{
    AsyncIOClientProxy* client = new AsyncIOClientProxy(_io_service);
    _acceptor.async_accept(client->socket(),
            boost::bind(&AsyncIOClientsManager::handle_accept,this,boost::asio::placeholders::error,client));
}

void AsyncIOClientsManager::handle_accept(const boost::system::error_code& ec, AsyncIOClientProxy* client)
{
    if (! ec)
    {
        register_client(client);
        client->run();
    }
    else
    {
        syslog(LOG_NOTICE,"Error accepting client connection.");
        delete client;
    }
    _async_accept();
}

AsyncIOClientsManager::AsyncIOClientProxy::AsyncIOClientProxy(boost::asio::io_service& io_service) :
    ClientProxy(),
    _socket(io_service),
    _proxy_mutex()
{
}

void AsyncIOClientsManager::AsyncIOClientProxy::run()
{
    boost::thread thr( boost::bind( &AsyncIOClientsManager::AsyncIOClientProxy::handle_receive, this ) );
}

tcp::socket& AsyncIOClientsManager::AsyncIOClientProxy::socket()
{
    return _socket;
}

void AsyncIOClientsManager::AsyncIOClientProxy::handle_receive()
{
    try
    {
        char header_size[HEADER_SIZE];
        boost::asio::read(socket(), boost::asio::buffer(header_size, HEADER_SIZE) );
        {
            boost::mutex::scoped_lock glock(_proxy_mutex);

            fud_size size;
            InputMessage bis( std::string(header_size, HEADER_SIZE) );
            bis >> size;
            assert (size > 0);

            std::auto_ptr<char> body(new char[size - HEADER_SIZE]);
            boost::asio::read(socket(), boost::asio::buffer(body.get(), size - HEADER_SIZE) );

            handle_response( std::string(body.get(), size - HEADER_SIZE) );
        }
    }
    catch (std::exception& e)
    {
        syslog(LOG_NOTICE, "Error receiving data from client %u.", get_id());
        destroy();
    }
    /* Listen again */
    handle_receive();
}

void AsyncIOClientsManager::AsyncIOClientProxy::send(const std::string& message)
{
    try
    {
        boost::mutex::scoped_lock glock(_proxy_mutex);

        boost::asio::write(socket(), boost::asio::buffer(message));
        syslog(LOG_NOTICE,"Sending something to Client %u", get_id());
    }
    catch(std::exception& e)
    {
        syslog(LOG_NOTICE,"Error(process/write): %s.",e.what());
        destroy();
    }
}

void AsyncIOClientsManager::AsyncIOClientProxy::destroy()
{
    ClientsManager::get_instance()->deregister_client( get_id() );
}

ClientsManager* create_clients_manager()
{
    return new AsyncIOClientsManager(31337);
}

} // end namespace
