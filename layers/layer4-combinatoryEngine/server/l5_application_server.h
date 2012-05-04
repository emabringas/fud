/**
 *  @file:      l5_application_server.h
 *  @details    Header file for L5ApplicationServer class.\n
 *              System: CombEng \n
 *              Language: C++\n
 *
 *  @author     Favio Bettiol
 *  @email      favio.bettiol AT gmail.com
 *
 *  @author     Diego Diaz
 *  @email      diazdiego86 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * This file is part of CombEng
 *
 * CombEng : Combinatory Engine, an FuD's abstraction layer for problems that
 * require to combine elements. Also, this layer provides ranking and prune
 * features for these combinations.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Favio Bettiol and Diego Diaz
 *
 * CombEng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CombEng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CombEng .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//=================================
// include guard
#ifndef L5_APPLICATION_SERVER
#define L5_APPLICATION_SERVER

//=================================
// forward declared dependencies


//=================================
// included dependencies
#include <recabs/recabs.h>
#include <set>
#include "../common/l4_node.h"


namespace comb_eng
{

template <class T>
class L5ApplicationServer : public recabs::L4ServerApp
{

public:

    L5ApplicationServer() {}

    /**
     * Gets the serialized initial L4_Node.
     *
     * @param pkt: the resulting package which contains the serialized initial L4_Node
     */
    virtual void get_initial_packet(recabs::Packet& pkt) const = 0;


    /**
     * Manage a single result.
     *
     * @param pkt: the received packet that it will be handle as result.
     */
    virtual void receive_result(const recabs::Packet& pkt) = 0;


    /**
     * Returns the L4Node root
     */
    virtual L4Node<T>* get_initial_node() = 0;


    /**
     * returns the initial set of elements which root node will use to combine
     */
    virtual std::list<T> get_initial_set() = 0;

};

}
#endif
