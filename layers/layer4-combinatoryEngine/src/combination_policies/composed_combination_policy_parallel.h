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
#include <mili/mili.h>
#include "../common/combination_policy.h"
#include "../common/state_set.h"
#include "observer_aux.h"


template <class T>
class ComposedCombinationPolicyParallel : public comb_eng::CombinationPolicy<T>
{
private:
    typedef typename std::list<ObserverAux<T>*>::iterator Obs_list_iterator;
    std::list<ObserverAux<T>*> _observer_list;

public:
    /**
    * Constructor method.
    */
    ComposedCombinationPolicyParallel() {}


    /**
    * Constructor method.
    */
    ComposedCombinationPolicyParallel(comb_eng::CombinationObserver<T>* obs, const std::string& name)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}


    /**
    * Destructor method. It invokes the destructor method of each one of the ObserversAux belonging in the ObserverAux list.
    */
    ~ComposedCombinationPolicyParallel()
    {
        mili::delete_container(_observer_list);
    }


    /**
    *  Adds to the ObserverAuxs' list a new ObserverAux which observes the policy passed by parameter.
    *  This method adds a new combination policy to carry out the composed combination policy.
    *  @param policy : combination policy observed
    *. @param ref_set : Reference set on wich the combination policy will work.
    *. @param is_mandaroty : If the policy is mandatory.
    */
    void add_new_combination_policy(comb_eng::CombinationPolicy<T>* policy, const std::list<T>& ref_set, const bool& is_mandatory)
    {

        ObserverAux<T>* new_observer = new ObserverAux<T>(this->get_observed_by(), policy, is_mandatory, ref_set);
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

    /**
    *  Its work is to execute the combine method of all associated combination policies. Then, notifies to its observer
    *  when it founds a new combination containing, one or none, combination of each associated combination policy.
    *  @param obj_to_comb: available items to be combined.
    *. @param status : Represents the status of how the combine method has finished, succses or error.
    */
    virtual void combine(const std::list<T>& obj_to_comb, comb_eng::Status& combination_status)
    {
        combination_status.set_name(this->_name);
        if (!_observer_list.empty())
        {
            StateSet<T, comb_eng::StateType> objects_to_combine(obj_to_comb, comb_eng::Applicable);
            StateSet<T, comb_eng::StateType> partial_combination(obj_to_comb, comb_eng::Not_Applicable); // initial set, empty
            Obs_list_iterator it(_observer_list.begin());
            while (it != _observer_list.end())      //Initilize all ObserverAux associated with the status and the available items.
            {
                (*it)->set_items_availables(objects_to_combine);
                (*it)->set_partial_combination(partial_combination);
                (*it)->set_final_observer(this->get_observed_by());
                ++it;
            }
            //Execute the combine method of the first associated combination policy
            comb_eng::Status status("", comb_eng::Success);
            _observer_list.front() -> combine_observer(partial_combination, status);
            if (status.get_status() == comb_eng::Error)
                combination_status = status;
        }
        else
        {
            combination_status.set_status(comb_eng::Error);
            std::cout << "ERROR: Se desea usar una politica compuesta sin politica(s) simple(s)" <<  std::endl;
        }
    }



    ComposedCombinationPolicyParallel<T>* clone(comb_eng::CombinationObserver<T>* obs)
    {
        ComposedCombinationPolicyParallel<T>* ret = new ComposedCombinationPolicyParallel<T>(obs, this->get_name() );
        typename std::list<ObserverAux<T>*>::iterator it = _observer_list.begin();

        while (it != _observer_list.end())
        {
            ret->add_new_combination_policy ((*it)->get_combination_policy_obsrved()->clone(NULL), (*it)->get_reference_set(), (*it)->get_is_mandaroty());
            ++it;
        }

        return ret;
    }

};

#endif /* _COMPOSED_COMBINATION_POLICY_PARALLEL */
