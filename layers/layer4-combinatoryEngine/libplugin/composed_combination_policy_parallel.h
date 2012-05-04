/**
 *  @file:      composed_combination_policy_parallel.h
 *  @details    Header file for ComposedCombinationPolicyParallel class.\n
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
#ifndef COMPOSED_COMBINATION_POLICY_PARALLEL
#define COMPOSED_COMBINATION_POLICY_PARALLEL


//=================================
// included dependencies
#include <list>
#include <set>
#include "../common/combination_policy.h"
#include "observer_aux.cpp"

template <class T>
class ComposedCombinationPolicyParallel : public comb_eng::CombinationPolicy<T>
{
private:
    typedef typename std::list<ObserverAux<T>*>::iterator   Obs_list_iterator;
    typedef std::set<T*>                                    Combination;

    std::list<ObserverAux<T>*> _observer_list;

public:
    /**
    * Constructor method.
    */
    ComposedCombinationPolicyParallel() {}


    /**
    * Constructor method.
    */
    ComposedCombinationPolicyParallel(CombinationObserver<T>* obs, const std::string& name)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}


    /**
    * Destructor method. It invokes the destructor method of each one of the ObserversAux belonging in the ObserverAux list.
    */
    ~ComposedCombinationPolicyParallel();


    /**
    *  Add  to the list of ObserverAux a new ObserverAux wich observes the policy passed by parameter.
    *  This method adds a new combination policy to carry out the composed combination policy.
    *  @param policy : combination policy observed
    *. @param ref_set : Reference set on wich the combination policy will work.
    *. @param is_mandaroty : If the policy is mandatory.
    */
    void add_new_combination_policy(CombinationPolicy<T>* policy, const Combination& ref_set, const bool& is_mandatory);


    /**
    *  Its work is to excecute the combine method of all asociated combination policies. Then, notyfie to its observer
    *  when it founds a new combination containing ,one or none, combination of each asocied combinatoin policy.
    *  @param objects_to_combine: General set, availables items.
    *. @param status : Represents the status of how the combine method has finished, succses or error.
    */
    virtual void combine(const Combination& objects_to_combine, Status& status);

};

#endif /* _COMPOSED_COMBINATION_POLICY_PARALLEL */
