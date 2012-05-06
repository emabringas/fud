/**
 * \file  server_client.cpp
 * \brief Implementation of a boost::asio server and client.
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

#include "asio_server_client.hpp"
#include "getopt_pp.h"

#include "common.hpp"

using namespace GetOpt;

const Port DEFAULT_PORT = 30303;
const char* const DEFAULT_ADDRESS = "127.0.0.1";

void show_help()
{
    std::cout << "Valid options are:\n"
              "\t-p --port        [optional] Set port. Default=" << DEFAULT_PORT << std::endl <<
              "\t-d --dest        [optional] Set destination port. Default=" << DEFAULT_PORT << std::endl <<
              "\t-a --address     [optional] Set address. Default=" << DEFAULT_ADDRESS << std::endl;

    ;
}

int main(int argc, char **argv)
{
    GetOpt_pp options(argc, argv);

    Port port(DEFAULT_PORT);
    Port dest(DEFAULT_PORT);

    std::string address(DEFAULT_ADDRESS);

    if (options >> OptionPresent('h', "help"))
        show_help();
    else
    {
        options >> Option('p', "port", port) >> Option('d', "dest", dest) >> Option('a', "address", address);

        std::cout << "Main server app.: Starting server/client" << std::endl;

        AsioServerClient server(address, dest, port);

        std::string s;

        std::cin >> s;

        //Close all connections by sending a 0.
        OutputMessage output;
        output << 0;

        server.send_all(output.str());
    }
}
