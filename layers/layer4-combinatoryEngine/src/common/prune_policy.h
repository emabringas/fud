/**
 *  @file:      prune_policy.h
 *  @details    Header file for PrunePolicy class.\n
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
#ifndef PRUNE_POLICY_H
#define PRUNE_POLICY_H

//=================================
// included dependencies
#include <string>

namespace comb_eng
{

template <class T>
class PrunePolicy
{
private:
    std::string _name;

public:
    /**
     * Constructor method.
     */
    PrunePolicy(const std::string& name)
        : _name(name)
    {}

    /**
     * Destructor Method.
     */
    virtual ~PrunePolicy()
    {}

    /**
     * The method is_useful establishes when a node should continue its execution.
     */
    virtual bool is_useful(const std::list<T>  combination)
    {
        return true;
    }

    /**
     * Get the name for the prune policy.
     */
    inline std::string get_name()
    {
        return _name;
    }

};

}

#endif
