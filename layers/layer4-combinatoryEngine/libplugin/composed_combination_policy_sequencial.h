/**
 *  @file:      composed_combination_policy_sequencial.h
 *  @details    Header file for ComposedCombinationPolicySequencial class.\n
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
 * */

//=================================
// include guard
#ifndef _COMPOSED_COMBINATION_POLICY_SEQUENCIAL_H
#define _COMPOSED_COMBINATION_POLICY_SEQUENCIAL_H

//=================================
// included dependencies
#include <list>
#include <set>
#include <mili/mili.h>
#include "../common/combination_policy.h"


template <class T>
class ComposedCombinationPolicySequencial : public CombinationPolicy<T>
{

private:
    typedef std::set<T*>                                            Combination;
    typedef typename Combination::iterator                          Set_iterator;
    typedef typename std::list<CombinationPolicy<T>*>::iterator     Policies_list_iterator;
    typedef typename std::list< std::set <T*> >::iterator           ReferenceSets_list_iterator;

    std::list<CombinationPolicy<T>*>         _combPoliciesList;
    std::list< Combination >                 _referenceSetsList;

    /**
    * This method calculate the intersection of two sets
    * @param it_b : Iterator representing the begin of de first set.
    * @param it_e : Iterator representing the end of de first set
    * @param it1_b : Iterator representing the begin of de second set.
    * @param it1_e : Iterator representing the end of de second set
    * @param res : set where the common elements will be stored.
    */
    void set_intersection(Set_iterator it_b, Set_iterator it_e, Set_iterator it1_b, Set_iterator it1_e, Combination& res);


public:
    /**
     * Constructor method.
     */
    ComposedCombinationPolicySequencial(CombinationObserver<T>* obs, const std::string& name)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    /**
     * Destroyer method.
     */
    ~ComposedCombinationPolicySequencial();          // no se si es virtual, creo que no, se deberian llamar los destructores de politicas simples

    /**
     * add a new policy in its group of combination policies.
     * @param policy: the new combination policy.
     * @param ref_set: the reference set of elements which the new combination policy will operate
     */
    void add_new_combination_policy(CombinationPolicy<T>* policy, const Combination& ref_set);

    /**
    * This method will invoke in a sequencial order the combine method for each of the combination policies
    * belonging to its group of policies.
    * @param objects_to_combine : set of elements to combine by the combination policy
    * @param status : it has the status of execution of combine method (Fail or Success).
    */
    virtual void combine(const Combination&, Status&);

};


#endif  /* _COMPOSED_COMBINATION_POLICY_SEQUENCIAL_H */