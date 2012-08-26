/**
 *  @file:      combination_policy_predicate.cpp
 *  @details    Header file for CombinationPolicyPredicate class.\n
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
#ifndef COMBINATION_POLICY_PREDICATE_H
#define COMBINATION_POLICY_PREDICATE_H

//=================================
// included dependencies
#include <vector>
#include <string.h>
#include "../common/combination_policy.h"

template <class T, class P>
class CombinationPolicyPredicate :  public comb_eng::CombinationPolicy <T>
{
private:
    P predicate;

    struct Combination
    {
        Combination (std::set <T> elements):
            elementsAvailables (elements)
        {}


        Combination (const std::list<T>& elements):
            elementsAvailables (elements.begin(), elements.end())
        {}


        Combination (const Combination& other):
            elementsAvailables (other.elementsAvailables), 
            currentCombination (other.currentCombination)
        {}

        std::list <T> currentCombination;
        std::set <T> elementsAvailables;
    };

public:

    /**
     * Constructor method.
     */
    CombinationPolicyPredicate() ;

    /**
     * Constructor method without an observer.
     */
    CombinationPolicyPredicate(const std::string& name, const P& p)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(NULL, name), predicate (p)
    {}

    /**
     * Constructor method whit an observer.
     */
    CombinationPolicyPredicate(comb_eng::CombinationObserver<T>* obs, const std::string& name, const P& p)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name), predicate (p)
    {}

    /**
     * Destructor method.
     */
    ~CombinationPolicyPredicate()
    {}

    /**
     * It calculates the combinations and notifies to its observer.
     */
    virtual void combine(const std::list<T>& obj_to_comb, comb_eng::Status& status)
    {
        status.set_name(this->_name);
        Combination initialComb (obj_to_comb);
        combinations_builder (initialComb);        
    }

    void combinations_builder(const Combination& combination)
    {
        if (predicate.check (combination.currentCombination))
        {
            StateSet<T, comb_eng::StateType> comb(combination.currentCombination, comb_eng::Applicable);
            this->notify (comb);
        }
        else
        {
            if (combination.elementsAvailables.empty())
            {
                StateSet<T, comb_eng::StateType> comb(combination.currentCombination, comb_eng::Applicable);
                this->notify (comb);
            }
            else
            {   
                typename std::set<T>::const_iterator it;
                for (it = combination.elementsAvailables.begin(); it != combination.elementsAvailables.end();++it)                
                {
                    
                    Combination new_combination (combination);
                    new_combination.currentCombination.push_back (*it);
                    new_combination.elementsAvailables.erase (*it);                    
                    combinations_builder(new_combination);

                }
            }
        }
    }
};

#endif  // _NEWTONIAN_COMBINATION_POLICY_H
