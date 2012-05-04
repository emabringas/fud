/**
 * \file  common.h
 * \brief Common type definitions.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing common type definitions.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
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

#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdint.h>

#include "mili/mili.h"

namespace fud
{
    /** Standard unsigned int, to uphold portability. */
    typedef uint32_t      fud_uint;

    /** Standard int, to uphold portability. */
    typedef int32_t       fud_int;


    /**
     * ID of a JobUnit, unique.
     *
     * \sa JobUnit
     */
    typedef fud_uint       JobUnitID;

    /**
     * ID of a connected Client.
     * Should be unique for each connected client thoroughout the programs lifetime.
     *
     * \sa ClientProxy
     */
    typedef fud_uint       ClientID;

    /**
      * Size of a JobUnit, meaning is user defined. Generally it will be
      * proportional to the amount of bytes it occupies.
      *
      * \sa JobUnit
      */
    typedef fud_uint       JobUnitSize;

    /**
     * State of a ClientProxy, or connected client.
     *
     * \sa ClientProxy
     */
    enum ClientState
    {
        kBusy,
        kIdle
    };

    /**
      * Size of header for a job unit packet. For now it's just twice the length
      * of a single number, since the header consists of id + size.
      *
      * \sa JobUnit
      */
    const JobUnitSize HEADER_LENGTH = sizeof(JobUnitID) + sizeof(JobUnitSize);

    /** Possible responses from clients. */
    typedef fud_uint ResponseCode;

    const ResponseCode JobUnitCompleted  = 13; /** The JobUnit was completely computed. */

    /**
      * Size of header for a response packet. Just the length
      * of a single number, since the header consists of a ResponseCode.
      */
    const JobUnitSize RESPONSE_HEADER_LENGTH = sizeof(ResponseCode);

    /** Maximum size of the Job Unit Queue. */
    const JobUnitSize MAX_JOBUNITS_QUEUE_SIZE   = 11;

    /** A Port type. */
    typedef fud_uint Port;

    /** A message you take data from. */
    typedef mili::bistream InputMessage;

    /** A message you put data into. */
    typedef mili::bostream OutputMessage;
}

#endif