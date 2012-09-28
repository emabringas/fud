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
 *  @date       sep 2012
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
        Combination ()
        {}

        Combination (const std::set <T>& elements):
            elementsAvailables (elements)
        {}

        Combination (const std::set <T>& elementsAvailables, const std::set <T>& currentCombination):
            elementsAvailables (elementsAvailables), 
            currentCombination (currentCombination)
        {}

        Combination (const std::list<T>& elements):
            elementsAvailables (elements.begin(), elements.end())
        {}

        Combination (const Combination& other):
            elementsAvailables (other.elementsAvailables), 
            currentCombination (other.currentCombination)
        {}

        bool operator < (const Combination& other) const 
        {
            return (currentCombination < other.currentCombination);
        }

        void print () const
        {
            std::cout << "Combination: ";
            typename std::set<T>::iterator curr_comb_it = currentCombination.begin();
            for (curr_comb_it ; curr_comb_it != currentCombination.end(); ++curr_comb_it)
                std::cout << *curr_comb_it << " - " ;

            std::cout << "       |       availables: ";
            typename std::set<T>::iterator availables_it = elementsAvailables.begin();
            for (availables_it ; availables_it !=  elementsAvailables.end(); ++availables_it)
                std::cout << *availables_it << " - " ;

            std::cout << std::endl;        

        }

        std::set <T> currentCombination;
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
        std::set <Combination> initial_set;

        //Generates the initial set to build de combinations. If the elementes are {1,2,3}, It will call combination_builder with {{1},{2},{3}}
        for (typename std::list<T>::const_iterator it = obj_to_comb.begin(); it != obj_to_comb.end(); ++it)
        {
            std::set<T> current_comb;
            current_comb.insert (*it);

            //use mili::copyContainer
            std::set<T> current_availables (obj_to_comb.begin(), obj_to_comb.end());
            current_availables.erase(*it);

            Combination newCombination (current_availables, current_comb);
            initial_set.insert (newCombination);
        }
        combinations_builder (initial_set);
    }

    //Recursive method to generate de combinations.
    void combinations_builder(const std::set <Combination>& combinations) 
    {
        //If combinations is empty, nothing can be done.
        if (! combinations.empty())
        {
            //Auxiliar set to be able to erase combinations wich hold the predicate (Since erase method invalidates the iterator)
            std::set <Combination> combinations_tmp (combinations);

            // Iterates for each combination and notifies those ones which hold the predicate. 
            typename std::set <Combination>::const_iterator combinations_it = combinations.begin();
            for (combinations_it ; combinations_it != combinations.end(); ++combinations_it)
            {
                if (predicate.check (combinations_it->currentCombination))
                {
                    //Tthe combination is notified
                    StateSet<T, comb_eng::StateType> comb(combinations_it->currentCombination, comb_eng::Applicable);
                    this->notify (comb);
                    //Tthe combination is erased and the other combinations are updated to avoid undessered combinations (PRUNE is done)
                    combinations_tmp.erase (*combinations_it);
                    update_neighbors (combinations_tmp, *combinations_it);                    
                }

            }

            //After check the predicate for each combinations, new combinations are generated.
            std::set <Combination> new_combinations;
            for (combinations_it = combinations_tmp.begin(); combinations_it != combinations_tmp.end(); ++combinations_it)
            {
                typename std::set <T>::iterator elem_availables_it = combinations_it->elementsAvailables.begin();
                for (elem_availables_it ; elem_availables_it != combinations_it->elementsAvailables.end(); ++elem_availables_it)
                {
                    Combination new_combination (*combinations_it);
                    new_combination.currentCombination.insert (*elem_availables_it);
                    new_combination.elementsAvailables.erase (*elem_availables_it);
                    new_combinations.insert (new_combination);
                }
            }
            combinations_builder (new_combinations);
        }
    }


    // It updates the availables elements for the neighbors, to aviod combinations that are included in other combinations.
    void update_neighbors (std::set<Combination>& all_combinations, const Combination& curr_combination) 
    {
        //Result will contain the combinations filtered (undesered elements will be removed from each combination's available_elements)
        std::set<Combination> result;

        // If exist a subset of the current combination (in wich only one element X was removed) within a combination neighboring "COMB", the element X is 
        // removed form the availables_elements of COMB. 
        typename std::set<Combination>::const_iterator combinations_it = all_combinations.begin();
        for (combinations_it; combinations_it!= all_combinations.end(); ++combinations_it)
        {
            Combination new_comb (*combinations_it);
            typename std::set<T>::iterator curr_comb_it = curr_combination.currentCombination.begin();
            for (curr_comb_it ; curr_comb_it != curr_combination.currentCombination.end(); ++curr_comb_it)
            {
                typename std::set<T> comb_tmp = curr_combination.currentCombination;
                comb_tmp.erase (*curr_comb_it);
                if (includes(combinations_it->currentCombination, comb_tmp))
                    new_comb.elementsAvailables.erase (*curr_comb_it);
            }
            result.insert (new_comb);
        }
        all_combinations = result;
    }

//  Returns true if set2 is included into set1, otherwise, false.
//  Maybe STL could be used
    bool includes (const std::set<T>& set1, const std::set<T>& set2) const
    {
        bool brake = false;
        typename std::set<T>::const_iterator it = set2.begin();

        while ( !brake && it != set2.end())
        {
            if (set1.find(*it) == set1.end())
                brake = true;
            ++it;

        }
        return (!brake) ;
    }
};

#endif  // _COMBINATION_POLICY_PREDICATE_H
