/**
 *  @file:      combination_policy.h
 *  @details    Header file for CombinationPolicy class.\n
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
#ifndef COMBINATION_POLICY_H
#define COMBINATION_POLICY_H

//=================================
// included dependencies
#include <set>
#include <string>
#include"combination_oberver.h"

namespace comb_eng
{

enum StatusType
{
    Success,
    Error
};


/**
 * Represent the status of a combination policy excecution.
 */
struct Status
{
private:
    std::string _name;
    StatusType _status;

public:
    Status() {}

    Status(const std::string& name, const StatusType& status)
        : _name(name),
          _status(status)
    {}

    inline StatusType get_status()
    {
        return _status;
    }

    inline void set_status(const StatusType& status)
    {
        _status = status;
    }

    inline std::string get_name()
    {
        return _name;
    }

    inline void set_name(const std::string& name)
    {
        _name = name;
    }


};


/**
 * Abstract class containing the main features that a combination policy must have
 */
template <class T>
class CombinationPolicy
{

protected:
    CombinationObserver<T>*             _observed_by;
    std::string                         _name;

    /**
    * Notifies to its observer that a change has occured
    */
    void notify(const std::set<T*> & combination);

public:
    /**
     * Constructor method.
     */
    CombinationPolicy()
    {}

    /**
    * Constructor method.
    * @param name: name for the combination policy.
    * @param obs: Observer for the combination policy.
    */
    CombinationPolicy(CombinationObserver<T>* obs, const std::string& name)
        : _observed_by(obs), _name(name)
    {}

    /**
    * Destroyer method.
    * @param name: name for the combination policy.
    */
    virtual ~CombinationPolicy()
    {}

    /**
    * Attach an observer.
    * @param comb_observer: observer that will observe this combination policy for any change
    */
    void attach(CombinationObserver<T> *);

    /**
    * Combine a set of elements in a specific way
    * @param objects_to_combine : set of elements to combine by the combination policy
    * @param status : it has the status of execution of combine method (Fail or Success).
    */
    virtual void combine(const std::set<T*>& objects_to_combine, Status& combination_status) = 0;

    /**
    * Returns the name for the combination policy.
    */
    inline std::string get_name()
    {
        return _name;
    }

    /**
    * Returns the observer that observes the policy.
    */
    inline CombinationObserver<T>* get_observed_by()
    {
        return _observed_by;
    }

};


}
#endif
