/**
 * \file  asio_client.hpp
 * \brief Definition of AsioClient class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file providing class AsioClient.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

#include "common.hpp"

#ifndef ASIO_CLIENT_HPP
#define ASIO_CLIENT_HPP

class AsioClient
{
    public:
        /**
         * Standard constructor.
         *
         * @param address : Address to try to connect to. The server should be there.
         * @param port : Port to use for the connection. The server should have opened it.
         */
        AsioClient(std::string address, Port port, size_t connections = 1);

        /**
         * Start communication. It will try to connect to the server using
         * the address:port combination.
         *
         * If the connection is succesful, it will listen for incoming messages.
         */
        virtual void run();

        virtual void connect(size_t connection);
    private:
        /* Override, as per -Weffc++ */
        AsioClient(const AsioClient& other);
        AsioClient& operator= (const AsioClient& other);

        void wait_for_message(const boost::system::error_code& ec,size_t connection);

        virtual void handle_received_message(const boost::system::error_code& ec,const std::string& msg);

        /*attr*/
        std::vector<boost::asio::io_service*>   io_services_;

        std::vector<tcp::socket*> sockets_;
        std::string               address_;
        Port                      port_;

};

#endif