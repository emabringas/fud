/**
 * \file
 * \brief Implementation of AnaDistribution class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class AnaDistribution.
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

#include <sstream>
#include "fud/middlewares/ana/client/ana_distribution.h"
#include "fud/client/processors_manager.h"

namespace fud
{

AnaDistribution::AnaDistribution(std::string address, Port port) :
    DistributionClient(),
    _client( NULL )
{
    std::stringstream ss;
    ss << port;

   _client = ana::client::create( address, ss.str() );
}

AnaDistribution::~AnaDistribution()
{
    delete _client;
}

void AnaDistribution::run()
{
    _client->connect( this );

    _client->set_listener_handler( this );
    /* WORKAROUND for the bug of issue 5: commented the next set_timeouts. This operation belongs to ANA. */
//    _client->set_timeouts(ana::FixedTime, ana::time::seconds(10));
    _client->run();

    job_listener();
}


void AnaDistribution::dispatch(const std::string& out)
{
    _client->send(ana::buffer( out ), this);
}


// ANA handlers

void AnaDistribution::handle_connect   (ana::error_code ec, ana::net_id /*id*/)
{
    if ( ec )
    {
        std::cerr << "ERROR while attempting to connect: " << ec.message() << std::endl;
        finish();
    }
}

void AnaDistribution::handle_receive   (ana::error_code  ec,
                                        ana::net_id,
                                        ana::read_buffer buf)
{
    if (ec)
    {
        std::cerr << "ERROR while attempting to receive: " << ec.message() << std::endl;
        finish();
    }
    else
    {
        InputMessage bis( mili::substr(buf->string(), Pos(0), Count(HEADER_SIZE)) );
        fud_size last_pos;
        bis >> last_pos;

        handle_incoming_message( mili::substr(buf->string(), Pos(HEADER_SIZE), Pos((size_t) last_pos)) );
    }
}

void AnaDistribution::handle_disconnect(ana::error_code ec, ana::net_id)
{
    if (ec)
        std::cerr << "Client disconnected: " << ec.message() << std::endl;
    finish();
}

void AnaDistribution::handle_send      (ana::error_code ec, ana::net_id, ana::operation_id)
{
    if ( ec )
    {
        std::cerr << "ERROR while attempting to send: " << ec.message() << std::endl;
        finish();
    }
}

namespace fud
{
    DistributionClient* create_distribution_client(std::string address, Port port)
    {
        return new AnaDistribution(address,port);
    }
}

} // end namespace