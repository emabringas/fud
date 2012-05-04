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
#include "../common/combination_policy.cpp"

template <class T>
class ListCombinationPolicy : public comb_eng::CombinationPolicy <T>
{
    typedef std::set<T*>                        Combination;
    typedef typename std::set<T*>::iterator     set_iterator;

public:
    /**
     * Constructor method.
     */
    ListCombinationPolicy(CombinationObserver<T>* obs , const std::string& name)
        : CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    virtual void combine(const Combination&, Status& status);

};
#endif  /* _LIST_COMBINATION_POLICY_H */

