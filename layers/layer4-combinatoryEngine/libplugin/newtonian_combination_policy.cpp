/**
 *  @file:      newtonian_combination_policy.h
 *  @details    Implementation file for NewtonianCombinationPolicy class.\n
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


#include "newtonian_combination_policy.h"

template <class T>
void NewtonianCombinationPolicy <T>::combine(const Combination& objects_to_combine, Status& status)
{
    const size_t size = objects_to_combine.size();

    status.set_status(Success);
    status.set_name(this->get_name());

    if ((size < _MIN) or(_MAX < _MIN))
        status.set_status(Error);
    else
    {
        size_t k = _MIN;
        const size_t k_max = std::min(size, _MAX);
        while (k <= k_max)
        {
            choose(objects_to_combine , k);
            ++k;
        }
    }
}

template <class T>
void NewtonianCombinationPolicy<T> ::choose(const Combination& objects_to_combine, size_t n)
{
    CombinationAux combination(n);  // Creates a vector of length n.
    combinations_builder(combination, n, objects_to_combine.begin(), objects_to_combine.end());
}

template <class T>
void NewtonianCombinationPolicy<T>::combinations_builder(CombinationAux combination, size_t pos, set_iterator start, set_iterator end)
{
    set_iterator it = start;
    if (pos == 0)
    {
        //std::cout << this->get_name() << "------------------" << std::endl;
        Combination comb = vector_to_set(combination);
        this->notify(comb);
    }
    else
    {
        while (it != end)
        {
            combination[pos - 1] = (*it);
            combinations_builder(combination, pos - 1, ++it, end);
        }
    }
}

template <class T>
std::set<T*> NewtonianCombinationPolicy<T>::vector_to_set(CombinationAux combination)
{
    Combination result;
    vec_iterator it(combination.begin());
    while (it != combination.end())
    {
        result.insert(*it);
        ++it;
    }
    return result;
}
