/**
*  @file:      observer_aux.h
*  @details    Header file for ObserverAux class.\n
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
#ifndef OBSERVER_AUX_H
#define OBSERVER_AUX_H


//=================================
// included dependencies
#include "../common/combination_observer.h"
#include "../common/combination_policy.h"
#include "../common/state_set.h"
#include <iostream>

template <class T>
class ObserverAux: public comb_eng::CombinationObserver<T>
{
private:

    comb_eng::CombinationPolicy<T>*      _combination_policy_obsrved;  // la politica simple observada
    bool                                _is_mandatory;
    comb_eng::CombinationObserver<T>*    _final_observer;
    std::list<T>                         _reference_set;

    StateSet<T, comb_eng::StateType>     _partial_combination;
    StateSet<T, comb_eng::StateType>     _items_available;
    ObserverAux*                         _next_observer_aux ;        // no deberia ser un  puntero..
    comb_eng::Status                     _local_status;              // cada observerAux lleva el status de la politica observada
    comb_eng::Status                     _global_status;             // cada observerAux lleva el status de la politica observada


public:

    /*
     * constructor */
    ObserverAux()
    {}

    /*
     * constructor */
    ObserverAux(comb_eng::CombinationObserver<T>* final_observer, comb_eng::CombinationPolicy<T>* combination_policy_obsrved, bool is_mandatory, std::list<T> reference_set)
        : _combination_policy_obsrved(combination_policy_obsrved),
          _is_mandatory(is_mandatory),
          _final_observer(final_observer),
          _reference_set(reference_set),
          _next_observer_aux(0),
          _local_status(_combination_policy_obsrved->get_name(), comb_eng::Success),
          _global_status (_combination_policy_obsrved->get_name(), comb_eng::Success)
    {}

    /*
     * destructor
     */
    ~ObserverAux()
    {
        delete _combination_policy_obsrved;
    }


    /**
    *  Set the partial combination to the member variable ande then invokes the combine method of the associated combination policy.
    *  @param partial_combination : Set of the combinations founded by the previous combination policies.
    */
    void combine_observer(const StateSet<T, comb_eng::StateType>& partial_combination, comb_eng::Status& last_policy_status)
    {
        _local_status.set_status (comb_eng::Success);

        if (last_policy_status.get_status() == comb_eng::Success)
        {
            set_partial_combination(partial_combination);
            StateSet<T, comb_eng::StateType> ref_set_aux(_items_available);
            ref_set_aux.set_all_state(comb_eng::Not_Applicable);
            ref_set_aux.change_states_to(_reference_set, comb_eng::Applicable);
            std::list<T> tmp_list;
            ref_set_aux.to_container(tmp_list, comb_eng::Applicable);
            _combination_policy_obsrved->combine(tmp_list, _local_status);
            if (_local_status.get_status() == comb_eng::Error)
            {
                if (!_is_mandatory)
                {
                    if (_next_observer_aux == NULL)
                    {
                        _partial_combination.to_container(tmp_list, comb_eng::Applicable);
                        _final_observer -> update(tmp_list);
                    }
                    else
                    {
                        _local_status.set_status (comb_eng::Success);
                        _next_observer_aux->combine_observer(_partial_combination, _local_status);
                    }
                }
                else
                {
                    _global_status = _local_status;
                    last_policy_status = _global_status;
                }
            }

            if (_next_observer_aux != NULL)
            {
                if (_next_observer_aux -> get_global_status().get_status() == comb_eng::Error)
                    _global_status = _next_observer_aux->get_global_status();

                last_policy_status = _global_status;

            }

        }
    }



    /**
    * If the observer is not the last, it appends the new conmbination to the partial result
    * and send it to the next observer. Otherwise, it calls the general update.
    *  @param combination: The combination founded by the asociated policy
    */
    void update(const std::list<T>&  combination)
    {
        StateSet<T, comb_eng::StateType> new_partial_combination(_partial_combination);
        new_partial_combination.change_states_to(combination, comb_eng::Applicable);
        if (_next_observer_aux == NULL)
        {
            std::list<T> tmp_list;
            new_partial_combination.to_container(tmp_list, comb_eng::Applicable);
            _final_observer->update(tmp_list);
        }
        else
        {
            _next_observer_aux->combine_observer(new_partial_combination, _local_status);
        }
    }

    /*
     * setters*/
    void set_is_mandatory(const bool& mandatory)
    {
        _is_mandatory = mandatory;
    }

    void set_next_observer_aux(ObserverAux* next_obs_aux)
    {
        _next_observer_aux = next_obs_aux;
    }

    void set_final_observer (comb_eng::CombinationObserver<T>* final_observer)
    {
        _final_observer = final_observer;
    }

    void set_items_availables(const StateSet<T, comb_eng::StateType>& items)
    {
        _items_available = items;
    }

    void set_partial_combination(const StateSet<T, comb_eng::StateType>& origin)
    {
        _partial_combination = origin;
    }

    comb_eng::Status get_global_status()
    {
        return _global_status;
    }


    comb_eng::CombinationPolicy<T>* get_combination_policy_obsrved()
    {
        return _combination_policy_obsrved;
    }


    std::list<T> get_reference_set()
    {
        return  _reference_set;
    }


    bool get_is_mandaroty()
    {
        return _is_mandatory;
    }



};
#endif
