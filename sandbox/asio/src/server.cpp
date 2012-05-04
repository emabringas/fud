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

#include "asio_server.hpp"
#include "getopt_pp.h"

#include "common.hpp"

using namespace GetOpt;

const Port DEFAULT_PORT = 30303;


void show_help()
{
    std::cout << "Valid options are:\n"
        "\t-p --port        [optional] Set port. Default=" << DEFAULT_PORT << std::endl;
    ;
}

int main(int argc, char **argv)
{
    GetOpt_pp options(argc, argv);

    Port port(DEFAULT_PORT);

    if (options >> OptionPresent('h', "help"))
        show_help();
    else
    {
        options >> Option('p', "port", port);

        std::cout << "Main server app.: Starting server" << std::endl;

        AsioServer server(port);

        std::string s;

        std::cout << "All sentences typed will be sent to all clients, until you type 'q'." << std::endl;

        for( std::cin >> s; s != "q"; std::cin >> s)
        {
            OutputMessage output;

            output << s.size() + HEADER_LENGTH << s;

            server.send_all( output.str() );
        }

        //Close all connections by sending a 0.
        OutputMessage output;
        output << 0;

        server.send_all( output.str() );
    }
}
