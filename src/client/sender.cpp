/* $Id: sender.cpp 585 2011-07-05 14:18:48Z marjobe $ */

/** 
 *  @file:      sender.cpp
 *  @details    Implementation file for FuD providing Sender class. \n
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

#include <mili/mili.h>
#include "fud/common/common.h"
#include "fud/client/sender.h"
#include "fud/client/distribution_client.h"
#include "fud/client/processors_manager.h"

using namespace fud;

void Sender::send(const OutputMessage& message)
{
    OutputMessage out;
    fud_size size_of_message = HEADER_SIZE + CLIENT_HEADER_LENGTH + sizeof(fud_uint) + sizeof(fud_size) + message.str().size() * sizeof(char);
    out << size_of_message << kMessage << ProcessorsManager::get_instance()->get_next_message_number() << message.str();
    DistributionClient::get_instance()->dispatch(out.str());
}
