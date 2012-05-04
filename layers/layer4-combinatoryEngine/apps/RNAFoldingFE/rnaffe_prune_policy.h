/*
 * Created on March 14, 2011, 6:48 PM
 *
 *  @file:      rnaffe_application_server.h
 *  @details    Header file for RnaFFEApplicationServer class.\n
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

#ifndef RNAFFE_PRUNE_POLICY_H
#define RNAFFE_PRUNE_POLICY_H

#include <combeng/combeng.h>
#include <antivirals/antivirals.h>
#include <mili/mili.h>

using namespace comb_eng;


class RnaFFEPrunePolicy: public comb_eng::PrunePolicy<ResisBasedAntiviral>
{
public:
    /**
    *  Construtor method.
    *  @param name: String representing the prune policy name.
    */
    RnaFFEPrunePolicy(std::string name)
        : PrunePolicy<ResisBasedAntiviral>(name) {}

    /**
    *  Destrutor method.
    */
    ~RnaFFEPrunePolicy() {}

    /**
    *  Decides if a combination is useful or not. With this implementation, all combinations are useful.
    *  @param combination: Combination that will be analyzed to decide if it is useful or not.
    */
    bool is_useful(const std::list<ResisBasedAntiviral>  combination)
    {
        return true;
    }
};
#endif  /* RNAFFE_PRUNE_POLICY_H */

