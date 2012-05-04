/**
 *  @file:      list_combination_policy.h
 *  @details    Implementation file for ListCombinationPolicy class.\n
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

#include "list_combination_policy.h"

template <class T>
void ListCombinationPolicy<T>::combine(const Combination& objects_to_combine, Status& status)
{
    const bool isEmpty(objects_to_combine.size() == 0);
    status.set_name(this->get_name());                  //set status name with the policy name
    if (!isEmpty)
    {
        set_iterator objIt(objects_to_combine.begin());
        Combination new_comb;
        while (objIt != objects_to_combine.end())
        {
            new_comb.clear();
            new_comb.insert(*objIt);
            notify(new_comb);
            ++objIt;
        }
        status.set_status(Success);
    }
    else
    {
        status.set_status(Error);
    }
}