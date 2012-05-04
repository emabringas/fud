/**
 *  @file:      composed_combination_policy_parallel.cpp
 *  @details    Implementation file for ComposedCombinationPolicyParallel class.\n
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

#include "composed_combination_policy_parallel.h"

template <class T>
ComposedCombinationPolicyParallel<T>::~ComposedCombinationPolicyParallel()
{
    Obs_list_iterator it(_observer_list.begin());
    while (it != _observer_list.end())
    {
        (*it)->~ObserverAux();
        ++it;
    }
}

template <class T>
void ComposedCombinationPolicyParallel<T>::add_new_combination_policy(CombinationPolicy<T>* policy, const Combination& ref_set, const bool& is_mandatory)
{

    ObserverAux<T>* new_observer = new ObserverAux<T>(this->get_observed_by(), policy, is_mandatory, ref_set); /*this->get_observed_by()==final Observer*/
    policy->attach(new_observer);

    if (_observer_list.empty())
    {
        _observer_list.push_front(new_observer);
    }
    else
    {
        _observer_list.back()->set_next_observer_aux(new_observer);
        _observer_list.push_back(new_observer);
    }
}




template <class T>
void ComposedCombinationPolicyParallel<T>::combine(const Combination& objects_to_combine, Status& combination_status)
{

    Combination partial_combination;        //conjunto vacio

    Obs_list_iterator it(_observer_list.begin());
    while (it != _observer_list.end())      //Inicilize all ObserverAux asocied with the satus and the available items.
    {
        (*it)->set_items_availables(objects_to_combine);
        ++it;
    }

    //Excecute the combine of the first asociated combination policy
    combination_status.set_status(Success);
    _observer_list.front() -> combine_observer(partial_combination, combination_status);


}


