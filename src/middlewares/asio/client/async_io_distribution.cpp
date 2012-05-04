/**
 * \file  async_io_distribution.cpp
 * \brief Implementation of AsyncIODistribution class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AsyncIODistribution.
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

#include "async_io_distribution.h"
#include "processors_manager.h"

using boost::asio::ip::tcp;

using namespace fud;

AsyncIODistribution::AsyncIODistribution(std::string address, Port port) :
    DistributionClient(),
    _socket(0),
    _address(address),
    _port(port)
{
}

void AsyncIODistribution::run()
{
    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(_address),_port);
        _socket = new tcp::socket(io_service);
        boost::system::error_code error = boost::asio::error::host_not_found;
        _socket->connect(endpoint,error);
        if (error)
            throw boost::system::system_error(error);

        _connected = true;
        while (_connected)
        {
            wait_for_message();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error ocurred: " << e.what() << std::endl;
    }
}

void AsyncIODistribution::wait_for_message()
{
    try
    {
        char header_size[HEADER_SIZE];
        boost::asio::read(*_socket, boost::asio::buffer(header_size, HEADER_SIZE) );

        fud_size size;
        InputMessage bis( std::string(header_size, HEADER_SIZE) );
        bis >> size;
        assert (size > 0);

        std::auto_ptr<char> body(new char[size - HEADER_SIZE]);
        boost::asio::read(*_socket, boost::asio::buffer(body.get(), size - HEADER_SIZE) );

        handle_incoming_message( std::string(body.get(), size - HEADER_SIZE) );
    }
    catch (std::exception& e)
    {
        std::cerr << "Connection closed by server: " << e.what() << std::endl;
        _connected = false;
    }
}

void AsyncIODistribution::dispatch(const std::string& out)
{
    try
    {
        boost::asio::write(*_socket, boost::asio::buffer(out));
    }
    catch(std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
        _connected = false;
    }
}


namespace fud
{
    DistributionClient* create_distribution_client(std::string address, Port port)
    {
        return new AsyncIODistribution(address,port);
    }
}
