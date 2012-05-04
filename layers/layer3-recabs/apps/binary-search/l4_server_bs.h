/* $Id: l4_server_bs.h 334 2010-10-14 22:36:19Z emab73 $ */

/** 
 *  @file:      l4_server_bs.h
 *  @details    Header file for L4ServerBS class.\n
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
 * This file is part of RecAbs
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * processes without data dependency for framework FuD.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Mariano Bessone and Emanuel Bringas
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

#ifndef L4_SERVER_BS_H
#define L4_SERVER_BS_H

//#include <recabs/recabs.h>
#include "recabs_dev.h"

/**
 * Class that implements the interface L4ServerApp, therefore is an assistant
 * to the start of a BinarySearch and manager of the results.
 */
class L4ServerBS : public recabs::L4ServerApp
{
    public:

        /**
         * Constructor method.
         */
        L4ServerBS ();

        /**
         * Gets the serialized initial BinarySearch.
         *
         * @param pkt : the resulting package that contains the serialized
         *              initial BinarySearch.
         */
        virtual void get_initial_packet(recabs::Packet& pkt) const;

        /**
         * Manage a single result.
         *
         * @param pkt : the received packet that we handle as a result.
         *
         */
        virtual void receive_result(const recabs::Packet& pkt);

        /**
         * Result reporter. Print the final result.
         *
         */
        virtual void results_report() const;

    private:
        /* Attribute for handle the partial result. */
        bool _result;
};

#endif

