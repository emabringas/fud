/* $Id: l4_client_app.h 607 2011-08-04 03:47:06Z marjobe $ */

/** 
 *  @file:      l4_client_app.h
 *  @details    Header file for Recabs providing L4ClientApp class.
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       October 2010
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

#ifndef L4_CLIENT_APP_H
#define L4_CLIENT_APP_H

#include "result_sender.h"
#include "by_size_result_sender.h"

namespace recabs
{
    /**
     * Interface that represents a helper for the creation of result sender.
     */
    struct L4ClientApp
    {
        /**
         * Creates the result sender of your choice.
         *
         * @param realSender : final sender.
         *
         * @returns the result sender created by this implementation.
         */
        virtual MessageSender* createMessageSender(RecabsPacketHeader header) const
        {
            return new BySizeResultSender(new InmediatelySender(header), 10000);
        };
    };

}

#endif
