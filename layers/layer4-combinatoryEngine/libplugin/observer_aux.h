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
#include "../common/combination_oberver.h"
#include "../common/combination_policy.h"
#include <iostream>
#include <set>

template <class T>
class ObserverAux: public comb_eng::CombinationObserver<T>
{
private:
    typedef std::set<T*>                         Combination;
    typedef typename std::set<T*>::iterator      set_iterator;

    comb_eng::CombinationPolicy<T>*      _combination_policy_obsrved;  // la politica simple observada
    bool                                 _is_mandatory;
    comb_eng::CombinationObserver<T>*    _final_observer;              // es un puntero al obs de la politica compuesta. Cuando se encuentra
    Combination                          _reference_set;

    Combination                          _partial_combination;
    Combination                          _items_available;
    ObserverAux*                         _next_observer_aux ;  // no deberia ser un  puntero..
    comb_eng::Status                     _status;                      // cada observerAux lleva el status de la politica observada




    /**
    * This method calculate the intersection of two sets
    * @param it_b : Iterator representing the begin of de first set.
    * @param it_e : Iterator representing the end of de first set
    * @param it1_b : Iterator representing the begin of de second set.
    * @param it1_e : Iterator representing the end of de second set
    * @param res : set where the common elements will be stored.
    */
    void set_intersection(set_iterator, set_iterator, set_iterator, set_iterator, Combination&);

    /**
    * This metod adds to a set all elements of other set.
    * @param origin : set of elements to be added.
    * @param destination : set on wich will be added the element of the first parameter.
    */
    void merge_combinations(Combination origin, Combination& destination);




public:

    /*
     * constructor */
    ObserverAux()
    {}

    /*
     * constructor */
    ObserverAux(CombinationObserver<T>* final_observer, comb_eng::CombinationPolicy<T>*  combination_policy_obsrved, bool is_mandatory, Combination reference_set)
        : _combination_policy_obsrved(combination_policy_obsrved),
          _is_mandatory(is_mandatory),
          _final_observer(final_observer),
          _reference_set(reference_set)
    {}

    /*
     * destructor
     */
    ~ObserverAux();


    /**
    *  Set the partial combination to the member variable ande then invokes the combine methot of the asociated combination policy.
    *  @param partial_combination : Set of the combinations founded by the previus combination policies.
    */
    void combine_observer(const Combination& partial_combination, comb_eng::Status&); //, std::set<comb_eng::Objects*> items_availables);


    /**
    * If the observer is not the last, it appends the new conmbination to the partial result
    * and send it to the next observer. Otherwise, it calls the general update.
    *  @param combination: The combination founded by the asociated policy
    */
    void update(const std::set<T*>& combination) ;

    /*
     * setters*/
    void set_combination_policy_observed(const comb_eng::CombinationPolicy<T>& combination_policy);

    void set_is_mandatory(const bool& is_mandatory);

    //void set_reference_set(const Combination& refence_set);

    void set_next_observer_aux(ObserverAux* next_obs_aux);

    //void set_final_observer(ObserverAux final_observer);  //capas q no se usa.. borrar?

    void set_items_availables(const Combination& combination);

    void set_status(const comb_eng::Status&);

    void set_partial_combination(const Combination&);


};
#endif
