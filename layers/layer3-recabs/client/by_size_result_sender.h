/* $Id: by_size_result_sender.h 352 2010-11-03 03:29:15Z emab73 $ */

/** 
 *  @file:      bySizeResultSender.h
 *  @details    Header file for Recabs providing BySizeResultSender class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
 *  
 *  @author     Mariano Bessone
 *  @author     Emanuel Bringas
 *  @date       August 2010
 *  @version    0.1
 *
 * bySizeResultSender.h
 * This file is part of RecAbs
 *
 * Copyright (C) 2010 - Emanuel Bringas and Mariano Bessone
 *
 * RecAbs is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#ifndef BY_SIZE_RESULT_SENDER_H
#define BY_SIZE_RESULT_SENDER_H

#include "common.h"
#include "result_sender.h"
#include <list>

namespace recabs
{
    class BySizeResultSender : public ChainableSender
    {
        public:
           BySizeResultSender (ResultSender* next, uint maxByte);

            /**
             *  
             */
	        virtual void send(const Packet& packet);

            /**
             *  
             */
	        virtual void flush();

        private:
            /**
             *  Attributes
             */
            const uint _maxBytes;
        	std::list<Packet> _packets;
        	uint _accumBytes;

    };
}
#endif
