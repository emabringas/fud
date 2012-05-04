/**
 *  @file:      composed_combination_policy_sequencial.cpp
 *  @details    Implementation file for ComposedCombinationPolicySequencial class.\n
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

#include"composed_combination_policy_sequencial.h"

template <class T>
ComposedCombinationPolicySequencial<T>::~ComposedCombinationPolicySequencial()
{
    // destroy all combination policies belonging to the Sequencial policy
    Policies_list_iterator combIt;
    for (combIt = _combPoliciesList.begin(); combIt == _combPoliciesList.end(); ++combIt)
        (*combIt)->~CombinationPolicy();
}


template <class T>
void ComposedCombinationPolicySequencial<T>::add_new_combination_policy(CombinationPolicy<T>* policy, const std::set<T*>& ref_set)
{
    _combPoliciesList.push_back(policy);
    _referenceSetsList.push_back(ref_set);
}


template <class T>
void ComposedCombinationPolicySequencial<T>::combine(const std::set<T*>& objects_to_combine, Status& combination_status)
{
    Policies_list_iterator combIt(_combPoliciesList.begin()); //used to excecute each one of the asociated combination policy
    ReferenceSets_list_iterator refSetIt(_referenceSetsList.begin()); //used to now each one of the reference set asociated to each combination policy

    Status aux_status(CombinationPolicy<T>::get_name(), Success);

    bool continueComb(true); // If a policy fail, it will brake the cycle
    while (combIt != _combPoliciesList.end() && continueComb)
    {
        std::set<T*> intersect;
        set_intersection((*refSetIt).begin(), (*refSetIt).end(), objects_to_combine.begin(), objects_to_combine.end(), intersect);
        (*combIt)->attach(CombinationPolicy<T>::get_observed_by());
        (*combIt)->combine(intersect, aux_status);
        continueComb = aux_status.get_status() == Error ? false : true; // ver como tratamos el tema de q sea mandatoria
        ++combIt;
        ++refSetIt;
    }
}

template <class T>
void ComposedCombinationPolicySequencial<T>::set_intersection(Set_iterator it_ref_b, Set_iterator it_ref_e, Set_iterator it_item_b, Set_iterator it_item_e, std::set<T*>& intersect)
{
    Set_iterator it_r = it_ref_b;
    Set_iterator it_i;

    while (it_r != it_ref_e)
    {
        it_i = it_item_b;
        while (it_i != it_item_e)
        {
            if ((*it_r) == (*it_i)) // Hay que hacerlo de forma mas general
            {
                intersect.insert(*it_i);
            }
            ++it_i;
        }
        ++it_r;
    }
}

