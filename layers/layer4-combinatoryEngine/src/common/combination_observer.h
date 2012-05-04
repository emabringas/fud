/**
 *  @file:      CombinationObserver.h
 *  @details    Header file for combination_observer class.\n
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
 * along with CombEng. If not, see <http://www.gnu.org/licenses/>.
 *
 */

//=================================
// include guard
#ifndef _COMBINATION_OBSERVER_H
#define _COMBINATION_OBSERVER_H

//=================================
// included dependencies
#include <iostream>
#include "state_set.h"
#include "combination_policy.h"

namespace comb_eng
{
enum StateType
{
    Applicable,
    Not_Applicable
};

/**
* Interface to be implemented by the combination policy observers
*/

template <class T>
class CombinationObserver
{

public:
    /**
     * Constructor method.
     */
    CombinationObserver()
    {}

    /**
     * Constructor method.
     */
    virtual ~CombinationObserver()
    {}

    /**
    * Update, method executed after being notified by the combination policy
    * @param : combination. The combination policy notifies it has produced
    *          a new combination.
    *          Its observers must update the change automatically.
    */
    virtual void update(const std::list<T>&  combination) = 0;
};

}
#endif
