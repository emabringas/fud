/* $Id: common.h 613 2011-08-04 16:04:47Z marjobe $ */

/**
 *  @file:      common.h
 *  @details    Header file for common utils.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * process without data dependency for the framework FuD.
 * See <http://fud.googlecode.com/>.
 *
 * Copyright (C) 2010, 2011 - Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of RecAbs project.
 *
 * RecAbs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef COMMON_RECABS_H
#define COMMON_RECABS_H

#include <string>
#include <stdint.h>
#include <list>
#include <mili/mili.h>

namespace recabs
{
    
    /** Standard unsigned int, to uphold portability. */    
    typedef uint32_t        uint;

    /** Packet representation */
    typedef std::string     Packet;

    /**
     *  Container of packets
     */
    typedef std::list<Packet> PacketContainer;

    /** MiLi input/output stream for packet streaming. */
    typedef mili::bistream<>  InputMessage;
    typedef mili::bostream<>  OutputMessage;

    typedef std::string Address;
    typedef size_t      Port;

    /** Type of sent result.  */
    enum WhenToSend
	{
		kSendThisImmediately,
		kSendAllImmediately,
		kSendWhenRecAbsWants
	};   

    /** Header client response*/
    enum RecabsPacketHeader
    {
        kRes,        /** Result packet. */
        kJob,        /** Job packet. */
        kMess        /** Intermediate Result . */
    };

    const Address   LOCALHOST    = "127.0.0.1";
    const Port      DEFAULT_PORT = 31337;

}

#endif
