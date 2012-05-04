/**
 * \file  server.cpp
 * \brief Implementation of a boost::asio server.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 *
 * Contents:       Server Implementation
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include <iostream>

#include "asio_client.hpp"
#include "getopt_pp.h"

#include "common.hpp"

using namespace GetOpt;

const Port DEFAULT_PORT = 30303;

const char* const DEFAULT_ADDRESS = "127.0.0.1";

void show_help()
{
    std::cout << "Valid options are:\n"
        "\t-p --port        [optional] Set port. Default=" << DEFAULT_PORT << std::endl <<
        "\t-a --address     [optional] Set address. Default=" << DEFAULT_ADDRESS << std::endl <<
        "\t-c --connections [optional] Set connection amount (for multiplexing). Default = 1" << std::endl;
    ;
}

int main(int argc, char **argv)
{
    GetOpt_pp options(argc, argv);

    if (options >> OptionPresent('h', "help"))
        show_help();
    else
    {

        Port port(DEFAULT_PORT);

        std::string address(DEFAULT_ADDRESS);

        size_t connections(1);

        options >> Option('p', "port", port) >> Option('a',"address",address) >> Option('c',"connections",connections);

        std::cout << "Main client app.: Starting client" << std::endl;

        AsioClient client(address,port,connections);

        client.run();
    }
}
