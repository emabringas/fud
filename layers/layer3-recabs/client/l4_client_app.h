/* $Id: l4_client_app.h 356 2010-11-04 13:38:16Z emab73 $ */

/** 
 *  @file:      l4_client_app.h
 *  @details    Header file for Recabs providing L4ClientApp class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
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
 * l4_client_app.h
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

#ifndef L4_CLIENT_APP_H
#define L4_CLIENT_APP_H

#include "result_sender.h"

namespace recabs
{
    /**
     * Interface that represents a helper for the creation of result sender.
     */
    struct L4ClientApp
    {
        virtual ResultSender* createResultSender(ResultSender* realSender) {return realSender;};
    };

}

#endif
