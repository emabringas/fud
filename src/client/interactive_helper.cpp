/* $Id: interactive_helper.cpp 546 2011-05-09 20:21:42Z marjobe $ */

/** 
 *  @file:      interactive_helper.cpp
 *  @details    Implementation file for FuD providing InteractiveHelper class. \n
 *              System:     FuD                             \n
 *              Language:   C++                             \n
 *              Homepage:   <http://fud.googlecode.com/>
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       January 2011
 *  @version    0.1
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * Copyright (C) 2011 - Mariano Bessone and Emanuel Bringas, FuDePAN.
 *
 * This file is part of FuD
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

#include "fud/client/interactive_helper.h"
#include "fud/client/distribution_client.h"
#include "fud/common/common.h"
#include <mili/mili.h>

using namespace fud;

fud_uint InteractiveHelper::ask_for_free_clients(fud_uint n)
{
    OutputMessage req;
    fud_size size_of_message = HEADER_SIZE + CLIENT_HEADER_LENGTH + sizeof(fud_uint);
    req << size_of_message << kFreeClientsReq << n;
    DistributionClient::get_instance()->dispatch_and_wait_for_response( req.str() );

    return extract_free_clients();
}


fud_uint InteractiveHelper::extract_free_clients()
{
    if (DistributionClient::get_instance()->header() == kFreeClientsResp)
    {
        /* Response of FreeClients request. */
        fud_uint n_free_clients;
        InputMessage bis;
        DistributionClient::get_instance()->message(bis);
        bis >> n_free_clients;
        return n_free_clients;
    }
    else
    {
        /* Incorrect response. */
        std::cerr << "ERROR: incorrect response for FreeClients request." << std::endl;
        return 0;
    }
}

