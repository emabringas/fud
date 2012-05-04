/**
 * \file  asio_server_client.cpp
 * \brief Implementation of AsioServerClient class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file for FuD providing class AsioServerClient.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include <iostream>

#include "asio_server_client.hpp"
#include "mili/mili.h"

AsioServerClient::AsioServerClient(std::string address, Port dest_port, Port port) :
    AsioServer(port),
    AsioClient(address,dest_port)
{
    run();
}

void AsioServerClient::handle_received_message(const std::string& msg)
{
    OutputMessage output;

    output << msg.size() + HEADER_LENGTH << msg;

    send_all( output.str() );
}