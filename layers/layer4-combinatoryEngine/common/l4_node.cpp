/**
 *  @file:      l4_node.cpp
 *  @details    Implementation file for L4Node class.\n
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

#include "l4_node.h"

using namespace comb_eng;

template <class T>
void L4Node<T>::call(recabs::ChildrenFunctors& children, recabs::Packet& result)
{
    std::set <T*> objects_to_combine = setT_2_setPtrT(get_objects_to_combine());
    Status status;

    if (objects_to_combine.empty() || is_leaf() || this-> use_as_result())
        result = get_result();

    if (! objects_to_combine.empty() && !is_leaf())
    {
        CombinationPolicy<T>* comb_pol = change_combination_policy();
        if (comb_pol != NULL)
            _combination_policy = comb_pol;

        _combination_policy->combine(objects_to_combine, status);

        while (status.get_status() == Error && _combination_policy != NULL)
        {
            //informar que la politica fallo
            std::cout << "FALLO DE POLITICA : " << status.get_name() << std::endl; //escribo la politica q fallo
            _combination_policy = get_combination_if_failure(status.get_name());
            if (_combination_policy != NULL)
            {
                status.set_status(Success);
                _combination_policy->attach(this);
                _children_list.clear();
                _combination_policy->combine(objects_to_combine, status);
            }
        }

        if (status.get_status() == Error)
        {
            //ver que hacemos si no se pudo recuperar del fallo de la politica
        }
        else
        {
            manage_combinations();
        }
        children = _children_list;
    }

}

template <class T>
void L4Node<T>::update(const std::set<T*>& combination)
{
    if (_prune_policy->is_useful(combination))
    {
        _combiations_holder.push_back(combination);

    }
}

template <class T>
std::list<T> setPtrT_2_listT(std::set<T*> combination)
{
    std::list<T> new_comb;
    typename std::set<T*>::iterator it;
    for (it = combination.begin(); it != combination.end(); ++it)
    {
        T elem = (*(*it));
        new_comb.push_back(elem);
    }

    return new_comb;
}



template <class T>
std::set<T*> L4Node<T>::setT_2_setPtrT(const std::list<T>& list)
{
    typename std::list<T>::const_iterator it;

    std::set<T*> result_set;
    T* aux;
    for (it = list.begin(); it != list.end(); ++it)
    {
        aux = new T();
        *aux = (*it);
        result_set.insert(aux);
    }
    return result_set;
}
