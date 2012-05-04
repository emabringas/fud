/**
 *  @file:      list_combination_policy.h
 *  @details    Header file for ListCombinationPolicy class.\n
 *              System: CombEng \n
 *              Language: C++   \n
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
#ifndef _LIST_COMBINATION_POLICY_H
#define _LIST_COMBINATION_POLICY_H

//=================================
// included dependencies
#include "../common/combination_policy.h"
#include "../common/state_set.h"

template <class T>
class ListCombinationPolicy : public comb_eng::CombinationPolicy <T>
{

public:
    /**
     * Constructor method.
     */

    ListCombinationPolicy(comb_eng::CombinationObserver<T>* obs , const std::string& name)
        : comb_eng::CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    ~ListCombinationPolicy() {};

    virtual void combine(const std::list<T>& obj_to_comb, comb_eng::Status& status)
    {
        status.set_name(this->_name);
        bool isEmpty = (obj_to_comb.empty());
        StateSet <T, comb_eng::StateType>  objects_to_combine(obj_to_comb, comb_eng::Applicable);

        status.set_name(this->get_name());                  //set status name with the policy name
        if (!isEmpty)
        {

            typename StateSet<T, comb_eng::StateType>::SpecificIterator it = objects_to_combine.begin_SpecificIterator(comb_eng::Applicable);
            while (!(it.end()))
            {
                StateSet<T, comb_eng::StateType> new_comb(objects_to_combine);
                new_comb.set_all_state(comb_eng::Not_Applicable);
                new_comb.set_state(it.get_id(), comb_eng::Applicable);
                this->notify(new_comb);
                ++it;
            }
            status.set_status(comb_eng::Success);
        }
        else
        {
            status.set_status(comb_eng::Error);
        }
    }

    ListCombinationPolicy<T>* clone(comb_eng::CombinationObserver<T>* obs)
    {
        return (new  ListCombinationPolicy<T>(obs, this->get_name() ));
    }

};
#endif  /* _LIST_COMBINATION_POLICY_H */

