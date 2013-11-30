/* $Id: interactive_helper.h 401 2011-02-03 00:38:37Z marjobe $ */

/** 
 *  @file:      interactive_helper.h
 *  @details    Header file for FuD providing InteractiveHelper class. \n
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

#ifndef INTERACTIVE_HELPER_H
#define INTERACTIVE_HELPER_H

#include "fud/common/common.h"

namespace fud
{

/**
 *  Interface for client communications to server and back.
 */
struct InteractiveHelper
{
    private:

        /**
         * Extracts the number of free clients from the input message.
         *
         * @param message : input message to extract data.
         *
         * @returns the number of free clients.
         */
        virtual fud_uint extract_free_clients();

    public:

        /**
         * Asks if the server has N clients to and then returns the number of idle
         * clients that the server returned as such.
         *
         * @param n : number of clients required to complete the job.
         *
         * @returns the number of free clients that the server brings us.
         */
        virtual fud_uint ask_for_free_clients(fud_uint n);
};

}
#endif
