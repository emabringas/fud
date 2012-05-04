/**
 * \file  asio_server.cpp
 * \brief Implementation of a boost::asio server.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 *
 * Contents:       Implementation file for FuD providing class AsyncIOClientsManager methods
 *                 and embedded (private) class AsioClientProxy. These classes
 *                 handle communication with clients using Boost.Asio. Here is also
 *                 implemented the create_clients_manager method, later linked at
 *                 compile time.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include <memory>
#include <boost/bind.hpp>

#include "asio_server.hpp"

using boost::asio::ip::tcp;

AsioServer::AsioServer(Port port) :
    _io_service(),
    _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)),
    _client_proxies()
{
    std::cout << "Server: Starting." << std::endl;
    // To connect clients
    boost::thread acceptor( boost::bind( &AsioServer::run_acceptor_thread, this));
}

void AsioServer::send_one(ClientID id, const std::string& message)
{
    std::list<ClientProxy*>::iterator it;
    it = find_if(_client_proxies.begin(),_client_proxies.end(),
                boost::bind(&ClientProxy::get_id, _1) == id);

    if (it != _client_proxies.end())
        (*it)->process(message);
}

void AsioServer::send_all(const std::string& message)
{
    for (std::list<ClientProxy*>::iterator it( _client_proxies.begin() ); it != _client_proxies.end(); ++it)
        (*it)->process(message);
}


void AsioServer::run_acceptor_thread(AsioServer* obj)
{
    obj->_async_accept();
    obj->run_and_die();
    //Each connection springs recursively another async_accept, so this won't finish.
}

void AsioServer::run_and_die()
{
    _io_service.run();
}

void AsioServer::_async_accept()
{
    AsioClientProxy* client = new AsioClientProxy(_io_service);
    _acceptor.async_accept(client->socket(), boost::bind(&AsioServer::handle_accept,
                                                         this,
                                                         boost::asio::placeholders::error,
                                                         client));

    std::cout << "Server: Accepting incoming connections." << std::endl;
}

void AsioServer::register_client(ClientProxy* client)
{
    std::cout << "Server: Registering client " << client->get_id() << std::endl;
    _client_proxies.push_back(client);
}

void AsioServer::handle_accept(const boost::system::error_code& ec,AsioClientProxy* client)
{
    if (! ec)
        register_client(client);
    else
    {
        std::cerr << "Server: Error accepting client connection." << std::endl;
        delete client;
    }
    _async_accept();
}

AsioServer::AsioClientProxy::AsioClientProxy(boost::asio::io_service& io_service) :
    ClientProxy(),
    _socket(io_service),
    _code_buf()
{
}

void AsioServer::AsioClientProxy::handle_response(ResponseCode code)
{
    try
    {
        if (code == Ok) // get result
        {
            char size_buf[RESPONSE_HEADER_LENGTH];
            boost::asio::read(_socket,boost::asio::buffer(size_buf,RESPONSE_HEADER_LENGTH));

            MessageSize size;

//             InputMessage bis2(std::string(size_buf,RESPONSE_HEADER_LENGTH));
//             bis2 >> size;

            if (size > 0)
            {
                std::auto_ptr<char> msg(new char[size]);
                boost::asio::read(_socket,boost::asio::buffer(msg.get(),size));
                std::cout << "Server: Message received succesfuly." << std::endl;
            }
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Server: Error(handle_response): " << e.what() << std::endl;
        destroy();
    }
}

tcp::socket& AsioServer::AsioClientProxy::socket()
{
    return _socket;
}

void AsioServer::AsioClientProxy::handle_receive(const boost::system::error_code& ec)
{
    if (!ec)
    {
        InputMessage bis(std::string(_code_buf,RESPONSE_HEADER_LENGTH));

        ResponseCode code;
        bis >> code;

        handle_response(code);
    }
    else
    {
        std::cerr << "Server: Error receiving results in client" << get_id() << std::endl;
        destroy();
    }
}

void AsioServer::AsioClientProxy::handle_send(const boost::system::error_code& ec)
{
    if (!ec)
    {
        std::cout << "Server: Sending Message to Client " << get_id() << std::endl;

        boost::asio::async_read(_socket,boost::asio::buffer(_code_buf,RESPONSE_HEADER_LENGTH),
                                boost::bind(&AsioServer::AsioClientProxy::handle_receive,this,
                                boost::asio::placeholders::error));
    }
    else
    {
        std::cerr << "Server: Error sending Message to Client " << get_id() << std::endl;
        destroy();
    }
}

void AsioServer::AsioClientProxy::process(const Message& message)
{
    try {
        boost::asio::async_write(_socket, boost::asio::buffer(message),
                                boost::bind(&AsioServer::AsioClientProxy::handle_send,this,
                                boost::asio::placeholders::error));
    }
    catch(std::exception& e)
    {
        std::cerr << "Server: Error(process/write): " << e.what() << std::endl;
        destroy();
    }
}

void AsioServer::AsioClientProxy::destroy()
{
//     ClientsManager::get_instance()->deregister_client(this);
}
