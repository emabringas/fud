/**
 * \file  asio_client.cpp
 * \brief Implementation of AsioClient class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file for FuD providing class AsioClient.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "asio_client.hpp"

using boost::asio::ip::tcp;

AsioClient::AsioClient(std::string address, Port port, size_t connections) :
    io_services_(connections, NULL),
    sockets_(connections, NULL),
    address_(address),
    port_(port)
{
}

void AsioClient::run()
{
    for (size_t connection(0) ; connection < sockets_.size(); ++connection)
    {
        io_services_[connection] = new boost::asio::io_service();

        connect(connection);
    }
    for (size_t connection(0) ; connection < sockets_.size() - 1; ++connection)
        boost::thread t(boost::bind(&boost::asio::io_service::run, io_services_[connection]));

    io_services_[sockets_.size() - 1]->run();
}

void AsioClient::handle_received_message(const boost::system::error_code& ec, const std::string& msg)
{
    if (!ec)
        std::cout << "Client: Message of size " << msg.size() << " recieved: " << msg << std::endl;
}

void AsioClient::wait_for_message(const boost::system::error_code& ec, size_t connection)
{
    if (!ec)
    {
        try
        {
            MessageSize size;

            tcp::socket& _socket(*(sockets_[connection]));

            do
            {
                char header[HEADER_LENGTH];
                boost::asio::read(_socket, boost::asio::buffer(header, HEADER_LENGTH));

                InputMessage input(std::string(header, HEADER_LENGTH));
                input >> size;

                if (size != 0)
                {
                    std::auto_ptr<char> body(new char[size]);
                    boost::asio::read(_socket, boost::asio::buffer(body.get(), size));

                    std::string msg;

                    input.clear();
                    input.str(std::string(body.get(), size));
                    input >> msg;

                    std::cout << "Client: Message of size " << msg.size() << " recieved: " << msg << std::endl;
                }
            }
            while (size != 0);

            std::cout << "Client: Connection closed succesfuly." << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << "Client: Error, connection closed by server: " << e.what() << std::endl;
        }
    }
}

void AsioClient::connect(size_t connection)
{
    std::cout << "Client: Starting at " << address_ << ':' << port_ << std::endl;
    try
    {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(address_), port_);

        sockets_[connection] = new tcp::socket(*(io_services_[connection]));

        sockets_[connection]->async_connect(endpoint, boost::bind(&AsioClient::wait_for_message,
                                            this,
                                            boost::asio::placeholders::error,
                                            connection));

        std::cout << "Client: Connected." << std::endl;
        //state: connected
    }
    catch (const std::exception& e)
    {
        std::cerr << "Client: An error ocurred, " << e.what() << std::endl;
    }
}
