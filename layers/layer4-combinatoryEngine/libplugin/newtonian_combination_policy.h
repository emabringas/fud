/**
 *  @file:      newtonian_combination_policy.cpp
 *  @details    Header file for NewtonianCombinationPolicy class.\n
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
#ifndef _NEWTONIAN_COMBINATION_POLICY_H
#define _NEWTONIAN_COMBINATION_POLICY_H

//=================================
// included dependencies
#include <set>
#include <vector>
#include <string.h>
#include "../common/combination_policy.cpp"

template <class T>
class NewtonianCombinationPolicy :  public comb_eng::CombinationPolicy <T>

{
private:
    typedef std::vector<T*>                      CombinationAux;
    typedef std::set<T*>                         Combination;
    typedef typename std::set<T*>::iterator      set_iterator;
    typedef typename std::vector<T*>::iterator   vec_iterator;

    size_t _MIN;
    size_t _MAX;

    void choose(const Combination&, size_t);

    void combinations_builder(CombinationAux , size_t , set_iterator , set_iterator);

    Combination vector_to_set(CombinationAux);

public:

    /**
     * Constructor method.
     */
    NewtonianCombinationPolicy() ;

    /**
     * Constructor method whitout a observer.
     */
    NewtonianCombinationPolicy(size_t min, size_t max, std::string name)
        : _MIN(min),
          _MAX(max),
          CombinationPolicy<T>::CombinationPolicy(NULL, name)
    {}

    /**
     * Constructor method whit a observer.
     */
    NewtonianCombinationPolicy(CombinationObserver<T>* obs , size_t min, size_t max, const std::string& name)
        : _MIN(min),
          _MAX(max),
          CombinationPolicy<T>::CombinationPolicy(obs, name)
    {}

    /**
     * Destructor method.
     */
    ~NewtonianCombinationPolicy()
    {}

    /**
     * It calculates the combinations and notyfies to its observer.
     */
    virtual void combine(const Combination&, Status&);



};

#endif  // _NEWTONIAN_COMBINATION_POLICY_H
