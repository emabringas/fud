/**
 *  @file:      observer_aux.cpp
 *  @details    Implementation file for ObserverAux class.\n
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

#include "observer_aux.h"
#include "composed_combination_policy_parallel.h"


template <class T>
ObserverAux<T>::~ObserverAux()
{}


template <class T>
void ObserverAux<T>::combine_observer(const std::set <T*>& partial_combination, comb_eng::Status& last_policy_status)
{
    if (last_policy_status.get_status() == Success)
    {
        set_partial_combination(partial_combination);
        std::set <T*> intersect;
        set_intersection(_reference_set.begin(), _reference_set.end(), _items_available.begin(), _items_available.end(), intersect);
        _combination_policy_obsrved->combine(intersect, _status);
        if (_status.get_status() == Error)
        {
            if (!_is_mandatory)
            {
                if (_next_observer_aux == NULL)
                    _final_observer -> update(_partial_combination);
                else
                    _next_observer_aux->combine_observer(_partial_combination, last_policy_status);
            }
            else
            {
                last_policy_status.set_name(_combination_policy_obsrved->get_name());
                last_policy_status.set_status(Error);
            }
        }
    }
}


template <class T>
void ObserverAux<T>::update(const std::set<T*>&  combination)
{
    Combination new_partial_combination;
    merge_combinations(_partial_combination, new_partial_combination); // Agrego lo que tengo hasta el momento
    merge_combinations(combination, new_partial_combination);          // Agrego la combinacion encontrada

    if (_next_observer_aux == NULL)
        _final_observer->update(new_partial_combination);
    else
        _next_observer_aux->combine_observer(new_partial_combination, _status);
}


template <class T>
void ObserverAux<T>::set_items_availables(const Combination& items)
{
    _items_available = items;
}

template <class T>
void ObserverAux<T>::set_is_mandatory(const bool& mandatory)
{
    _is_mandatory = mandatory;
}

template <class T>
void ObserverAux<T>::set_status(const Status& status)
{
    _status = status;
}

template <class T>
void ObserverAux<T>::set_next_observer_aux(ObserverAux* next_obs_aux)
{
    _next_observer_aux = next_obs_aux;
}


template <class T>
void  ObserverAux<T>::set_intersection(set_iterator it_ref_b, set_iterator it_ref_e, set_iterator it_item_b, set_iterator it_item_e, Combination& intersect)
{
    set_iterator it_r = it_ref_b; // para iterar sobre el conj de referencia
    set_iterator it_i;              // para iterar sobre los elementos disponibles

    while (it_r != it_ref_e)
    {
        it_i = it_item_b;
        while (it_i != it_item_e)
        {
            if (*(*it_r) == *(*it_i))      // esto deberia poderse hacer de forma mas general
            {
                intersect.insert(*it_i);
            }
            ++it_i;
        }
        ++it_r;
    }
}


template <class T>
void ObserverAux<T>::set_partial_combination(const Combination& origin)
{
    _partial_combination.clear();
    merge_combinations(origin, _partial_combination);
}



template <class T>
void ObserverAux<T>::merge_combinations(Combination origin, Combination& destination)
{
    set_iterator it;
    it = origin.begin();
    while (it != origin.end())
    {
        destination.insert(*it);
        ++it;
    }
}