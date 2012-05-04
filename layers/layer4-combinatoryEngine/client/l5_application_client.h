/**
 *  @file:      l5_application_client.h
 *  @details    Header file for L5ApplicationClient class.\n
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
#ifndef L5_APPLICATION_CLIENT
#define L5_APPLICATION_CLIENT

//=================================
// included dependencies
#include <recabs/recabs.h>

namespace comb_eng
{
class L5ApplicationClient : public recabs::DeserializerFunctor
{

public:
    /**
     * Constructor method.
     */
    L5ApplicationClient()
    {};

    /*
     * Extract the L4_Node from given packet.
     * @param pkt: the packet containing the serialized L4_Node.
     * @param rf: the L4_Node as a result of deserialization.
     */
    virtual void deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const = 0;

};
}

#endif