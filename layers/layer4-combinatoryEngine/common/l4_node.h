/**
 *  @file:      l4_node.h
 *  @details    Header file for L4Node class.\n
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
#ifndef L4_NODE_H
#define L4_NODE_H

// forward declared dependencies
//class PrunePolicy;
//class CombinationPolicy;
//class Status;
//class Result;

//=================================
// included dependencies
#include <set>
#include <recabs/recabs.h>
#include "combination_policy.h"
#include "prune_policy.h"

namespace comb_eng
{
/**
*  Abstract class L4Node.
*/
template <class T>
class L4Node : public CombinationObserver<T>, public recabs::SerializableRecursiveFunctor
{
private:
    std::set<T*> setT_2_setPtrT(const std::list<T>& list);

protected:
    CombinationPolicy<T>*           _combination_policy;
    PrunePolicy<T>*                 _prune_policy;
    recabs::ChildrenFunctors        _children_list;

    /**
    *  From a particular node, this method return the "next
    *  state", another L4Node, obtained from a combination.
    *  @param new_combination : combination used to obtain de "next state".
    */
    virtual std::list<L4Node*> new_children(const std::list<T>& combination) = 0;

    /**
    *  Return a score for a node.
    */
    virtual float score() = 0;

    /**
    *  In the case that a combination policy fails, this method return another
    *  combination policy to follow the node process
    */
    virtual CombinationPolicy<T>* get_combination_if_failure(std::string failed_comb_policy)
    {
        return NULL;
    }

    /**
    *  Define the combination policy to process the node. In case that
    *  the node decide to change the combination policy, this method returns
    *  the new combination policy. In other case, it returns null.
    */
    virtual CombinationPolicy<T>* change_combination_policy()
    {
        return NULL;
    }

    /**
    * Resturns true if if the node must be used as result, in other case
    * it returns false
    */
    virtual bool use_as_result()
    {
        return false;
    }

    /**
     * Returns a stream representing a result that will be sended to the server.
     */
    virtual recabs::Packet get_result() = 0;

public:
    /**
     * Constructor method.
     */
    L4Node()
    {}

    /**
     * Constructor method.
     * @param comb: CombinationPolicy that node will use to combine its elements.
     * @param prune: PrunePolicy which the current node will cut off their/its children.
     */
    L4Node(CombinationPolicy<T>* comb, PrunePolicy<T>* prune)
        : _combination_policy(comb),
          _prune_policy(prune)
    {}

    /**
    *  Destroyer method.
    */
    virtual ~L4Node()
    {}

    /*
     * It start the node excecution.
     *  @param children_list : List of children obtained from the excecution of this node.
     *  @param result : In the case that a node wants to send a result to the server,
     *  he node must fill this parameter
     */
    void call(recabs::ChildrenFunctors& children_list, recabs::Packet& result);

    /*
     * Its main job is generate new childrends depending on the usfull of a combination.
     * @param combination : If it is usefull, then new childrens are obtainded from it.
     */
    void update(const std::set<T*>& combination);


    /**
    *  Return the set of objects that need to be combined.
    */
    virtual std::list<T> get_objects_to_combine() = 0;


    /*
     *Returns true if there is no more elements to combine
     */
    virtual bool is_leaf() = 0;


    /*
     * Il fills the parameter pkt with the node serialization
     */
    virtual void serialize(recabs::Packet& pkt) = 0;


    /*
     * Returns the combination policy asocied to the node
     */
    inline CombinationPolicy<T>* get_combination_policy() const
    {
        return _combination_policy;
    }


    /*
     * Returns the prune policy asocied to the node
     */
    inline PrunePolicy<T>* get_prune_policy() const
    {
        return _prune_policy;
    }


    inline void set_combination_policy(CombinationPolicy<T>* comb_pol)
    {
        _combination_policy = comb_pol;
    }


    inline void set_prune_policy(PrunePolicy<T>* prune)
    {
        _prune_policy = prune;
    }



};
}

#endif
