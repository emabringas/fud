/**
 *  @file:      newtonian_combination_policy.cpp
 *  @details    Header file for NewtonianCombinationPolicy class.\n
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
#ifndef _NEWTONIAN_COMBINATION_POLICY_H
#define _NEWTONIAN_COMBINATION_POLICY_H

//=================================
// included dependencies
#include <vector>
#include <string.h>
#include "../common/combination_policy.h"
//#include <combeng/combeng.h>

template <class T>
class NewtonianCombinationPolicy :  public comb_eng::CombinationPolicy <T>

{
private:
    size_t _MIN;
    size_t _MAX;
    StateSet<T, comb_eng::StateType> _state_set_local;

    void choose(std::vector<int>& objects_to_combine, size_t n)
    {
        std::vector<int> combination(n);  // Creates a vector of length n.
        combinations_builder(combination, n, objects_to_combine.begin(), objects_to_combine.end());
    }


    void combinations_builder(std::vector<int> combination, size_t pos, std::vector<int>::iterator start, std::vector<int>::iterator end)
    {
        std::vector<int>::iterator it = start;
        if (pos == 0)
        {
            StateSet<T, comb_eng::StateType> comb(_state_set_local);
            comb.set_all_state(comb_eng::Not_Applicable);
            std::vector<int>::iterator comb_it = combination.begin();
            while (comb_it != combination.end())
            {
                comb.set_state(*comb_it, comb_eng::Applicable);
                ++comb_it;
            }
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
public:

    /**
     * Constructor method.
     */
    NewtonianCombinationPolicy() ;

    /**
     * Constructor method without an observer.
     */
    NewtonianCombinationPolicy(size_t min, size_t max, std::string name)
        : _MIN(min),
          _MAX(max),
          comb_eng::CombinationPolicy<T>::CombinationPolicy(NULL, name)
    {}

    /**
     * Constructor method whit an observer.
     */
    NewtonianCombinationPolicy(comb_eng::CombinationObserver<T>* obs , size_t min, size_t max, const std::string& name)
        : _MIN(min),
          _MAX(max),
          comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    /**
     * Destructor method.
     */
    ~NewtonianCombinationPolicy()
    {}

    /**
     * It calculates the combinations and notifies to its observer.
     */
    virtual void combine(const std::list<T>& obj_to_comb, comb_eng::Status& status)
    {
        status.set_name(this->_name);
        _state_set_local = StateSet<T, comb_eng::StateType> (obj_to_comb, comb_eng::Applicable);
        std::vector<int> positions;
        typename StateSet<T, comb_eng::StateType>::ConstSpecificIterator it = _state_set_local.begin_SpecificIterator_const(comb_eng::Applicable);
        while (! it.end())
        {
            positions.push_back(it.get_id());
            ++it;
        }

        const size_t size = positions.size();

        status.set_status(comb_eng::Success);
        status.set_name(this->get_name());

        if ((size < _MIN) or(_MAX < _MIN))
            status.set_status(comb_eng::Error);
        else
        {
            size_t k = _MIN;
            const size_t k_max = std::min(size, _MAX);
            while (k <= k_max)
            {
                choose(positions, k);
                ++k;
            }
        }
    }


    NewtonianCombinationPolicy<T>* clone(comb_eng::CombinationObserver<T>* obs)
    {
        return (new  NewtonianCombinationPolicy<T>(obs,_MIN,_MAX, this->get_name() ));
    }

};

#endif  // _NEWTONIAN_COMBINATION_POLICY_H
