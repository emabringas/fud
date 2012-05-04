/**
 * \file  asio_server_client.hpp
 * \brief Definition of AsioServerClient class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file providing class AsioServer.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include "asio_server.hpp"
#include "asio_client.hpp"

#ifndef ASIO_SERVER_CLIENT_HPP
#define ASIO_SERVER_CLIENT_HPP

class AsioServerClient : public AsioServer, public AsioClient
{
    public:
        AsioServerClient(std::string address, Port dest_port, Port port );

    private:
        virtual void handle_received_message(const std::string& msg);
};

#endif