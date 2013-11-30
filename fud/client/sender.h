/* $Id: sender.h 395 2011-01-24 18:59:47Z marjobe $ */

/** 
 *  @file:      sender.h
 *  @details    Header file for FuD providing Sender class. \n
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

#ifndef SENDER_H
#define SENDER_H

#include "fud/common/common.h"

namespace fud
{

/**
 *  Interface for send messages to the server.
 */
struct Sender
{
    public:

        /**
         * Sends a regular message to the server.
         *
         * @param message : message to send.
         */
        void send(const OutputMessage& message);
};

}
#endif
