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
#include <mili/mili.h>
#include "../common/combination_policy.h"
//#include <combeng/combeng.h>


template <class T>
class ComposedCombinationPolicySequencial : public comb_eng::CombinationPolicy<T>
{

private:
    typedef typename std::list<comb_eng::CombinationPolicy<T>*>::iterator   Policies_list_iterator;
    typedef typename std::list< std::list<T> >::iterator                    ReferenceSets_list_iterator;

    std::list<comb_eng::CombinationPolicy<T>*>  _combPoliciesList;
    std::list< std::list<T> >                   _referenceSetsList;


public:
    /**
     * Constructor method.
     */
    ComposedCombinationPolicySequencial(comb_eng::CombinationObserver<T>* obs, const std::string& name)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    /**
     * Destroyer method.
     */
    ~ComposedCombinationPolicySequencial()
    {
        mili::delete_container(_combPoliciesList);
    }

    /**
     * add a new policy in its group of combination policies.
     * @param policy: the new combination policy.
     * @param ref_set: the reference set of elements which the new combination policy will operate
     */
    void add_new_combination_policy(comb_eng::CombinationPolicy<T>* policy, const std::list<T>& ref_set)
    {
        _combPoliciesList.push_back(policy);
        _referenceSetsList.push_back(ref_set);
    }

    /**
    * This method will invoke in a sequencial order the combine method for each of the combination policies
    * belonging to its group of policies.
    * @param objects_to_combine : set of elements to combine by the combination policy
    * @param status : it has the status of execution of combine method (Fail or Success).
    */
    virtual void combine(const std::list<T>& obj_to_comb, comb_eng::Status& combination_status)
    {
        combination_status.set_name(this->get_name());

        if (!_combPoliciesList.empty())
        {
            StateSet<T, comb_eng::StateType> objects_to_combine(obj_to_comb, comb_eng::Applicable);
            StateSet<T, comb_eng::StateType> ref_set_aux(objects_to_combine);

            Policies_list_iterator combIt(_combPoliciesList.begin());
            //used to execute each one of the associated combination policy
            ReferenceSets_list_iterator refSetIt(_referenceSetsList.begin());
            //used to know each one of the reference set associated to each combination policy

            comb_eng::Status aux_status(comb_eng::CombinationPolicy<T>::get_name(), comb_eng::Success);
            //bool continueComb(true); // If a policy fail, it will brake the cycle

            while (combIt != _combPoliciesList.end())  // && continueComb)
            {
                ref_set_aux.set_all_state(comb_eng::Not_Applicable);
                ref_set_aux.change_states_to(*refSetIt, comb_eng::Applicable);
                StateSet<T, comb_eng::StateType> intersect;
                objects_to_combine.intersection(intersect, ref_set_aux, comb_eng::Applicable, comb_eng::Not_Applicable);
                (*combIt)->attach(comb_eng::CombinationPolicy<T>::get_observed_by());

                std::list<T> tmp_list;
                intersect.to_container(tmp_list, comb_eng::Applicable);
                (*combIt)->combine(tmp_list, aux_status);
                //continueComb = aux_status.get_status() == comb_eng::Error ? false : true; // ver como tratamos el tema de q sea mandatoria
                ++combIt;
                ++refSetIt;
            }
        }
        else
        {
            combination_status.set_status(comb_eng::Error);
            std::cout << "ERROR: Se quiere usar una politica compuesta sin agregar politica(s) simple(s)" <<  std::endl;
        }
    }
};


#endif  /* _COMPOSED_COMBINATION_POLICY_SEQUENCIAL_H */
