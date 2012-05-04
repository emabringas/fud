/*
 * Created on March 14, 2011, 9:27 AM
 *
 *  @file:      rnaffe_application_client.h
 *  @details    Header file for RnaFFEApplicationClient class.\n
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

#ifndef RNAFFE_APPLICATION_CLIENT_H
#define RNAFFE_APPLICATION_CLIENT_H

#include "rnaffe_node.h"

using namespace comb_eng;
class RnaFFEApplicationClient : public comb_eng::L5ApplicationClient
{
public:

    /**
    *  Construtor method.
    *  @param g_fold: Pointer to a fold type. It will be used to get the folding free energy.
    */
    RnaFFEApplicationClient(const IFold* g_fold);

    /**
    *  Destrutor method.
    */
    ~RnaFFEApplicationClient();

    /**
    *  Transform a datastream into a node.
    *  @param pkt: Data stream. Used to rebuild a node.
    *  @param rf: The new node is returned into *rf (Note: a node is a recursive functor too).
    */
    void deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const;

private:
    const IFold* fold;
};


#endif  /* RNAFFE_APPLICATION_CLIENT_H */

