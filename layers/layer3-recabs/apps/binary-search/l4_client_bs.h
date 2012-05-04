/* $Id: l4_client_bs.h 357 2010-11-05 14:42:13Z emab73 $ */

/** 
 *  @file:      l4_client_bs.h
 *  @details    Header file for Recabs providing L4ClientBS class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
 *  
 *  @author     Mariano Bessone
 *  @author     Emanuel Bringas
 *  @date       August 2010
 *  @version    0.1
 *
 * l4_client_bs.h
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

#include "recabs_dev.h"

/**
 * Class that implements the interface L4ServerApp, therefore is an assistant
 * to the start of a BinarySearch and manager of the results.
 */
class L4ClientBS : public recabs::L4ClientApp
{
    virtual recabs::ResultSender* createResultSender(recabs::ResultSender* realSender);
};

