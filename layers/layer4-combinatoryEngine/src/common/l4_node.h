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

//=================================
// included dependencies
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
protected:
    CombinationPolicy<T>*       _combination_policy;
    PrunePolicy<T>*             _prune_policy;
    recabs::ChildrenFunctors    _children_list;

    /**
    *  It returns the "next state" (another L4Node), obtained from a combination.
    *
    *  @param new_combination : combination used to obtain de "next state".
    *  @param                 : the list of children nodes. When a new L4Node is created from a particular one,
    *          it is put into this list.
    */
    virtual void new_children(const std::list<T>&  combination, std::list<L4Node*>&) = 0;

    /**
    *  Returns the score of the current node.
    */
    virtual float score() = 0;

    /**
    *  In case that a combination policy fails, this method returns another
    *  combination policy so the node can keep working.
    *
    *  @param failed_comb_policy: the name of the policy that has failed.
    */
    virtual CombinationPolicy<T>* get_combination_if_failure(const std::string& failed_comb_policy)
    {
        return 0;
    }

    /**
    *  In case the node decides to change the combination policy, this method returns
    *  that new combination policy. if not, it returns null.
    */
    virtual CombinationPolicy<T>* change_combination_policy()
    {
        return 0;
    }

    /**
    * Resturns true if the node must be used as result, in other case
    * it returns false
    */
    virtual bool use_as_result()
    {
        return false;
    }

    /**
     * Returns a Packet representing a result that will be sent to the server.
     */
    virtual recabs::Packet get_result() = 0;

public:
    /**
     * Constructor method.
     */
    L4Node()
        : _combination_policy(NULL),
          _prune_policy(NULL)
    {}

    /**
     * Constructor method.
     * @param comb  : CombinationPolicy that node will use to combine its elements.
     * @param prune : PrunePolicy which the current node will cut off their/its children.
     */
    L4Node(CombinationPolicy<T>* comb, PrunePolicy<T>* prune)
        : _combination_policy(comb),
          _prune_policy(prune)
    {}

    /**
    *  Destructor method.
    */
    ~L4Node()
    {
        delete _combination_policy;
        delete _prune_policy;
    }

    /**
     *  It starts the node execution.
     *  If the current node has some objects available,
     *  it will combine them and the rest of its behaviour
     *  is defined by both combination and prune policies.
     *  The call method tries to fill the node's children list.
     *
     *  @param children : List of children obtained from the excecution of this node.
     *  @param result   : In case that a node wants to send a result to the server,
     *                    it has to fill this parameter with the desired information.
     *  @param when     : it establishes when the result packet has to be sent to
     *                    the server.
     */
    void call(recabs::ChildrenFunctors& children, recabs::Packet& result, recabs::WhenToSend&)
    {
        /* By default: when = recabs::kSendWhenYouWant; */
        std::list <T> objects_to_combine;
        get_objects_to_combine(objects_to_combine);
        Status status ("status", comb_eng::Success);

        if (objects_to_combine.empty() || is_leaf() || use_as_result())
        {
       //     std::cout << " =========================  SENT A RESULT  ======================"<<std::endl;
            result = get_result();
        }

        if (! objects_to_combine.empty() && !is_leaf())
        {
            CombinationPolicy<T>* comb_pol = change_combination_policy();
            if (comb_pol != NULL)
                _combination_policy = comb_pol;
            _combination_policy->combine(objects_to_combine, status);
            while (status.get_status() == Error && _combination_policy != NULL)
            {
                delete (_combination_policy);
                _combination_policy = get_combination_if_failure(status.get_name());
                if (_combination_policy != NULL)
                {
                    status.set_status(Success);
                    _children_list.clear();
                    _combination_policy->combine(objects_to_combine, status);
                }
            }

            if (status.get_status() == Error)
            {
                //ver que hacemos si no se pudo recuperar del fallo de la politica
            }
            else
            {
                mili::copy_container(_children_list, children);
            }
        }
    }


    /*
     * Its main job is generate new childrends depending on the usfull of a combination.
     * @param combination : If it is usefull, then new childrens are obtainded from it.
     */
    void update(const std::list<T>&  combination)
    {
        if (_prune_policy->is_useful(combination))
        {
            std::list<L4Node*> children;
            typename std::list< L4Node<T>*>::iterator it;

            new_children(combination, children);
            it =  children.begin();
            while (it != children.end())
            {
                _children_list.push_back(*it) ;
                ++it;
            }
        }
    }


    /**
    *  Return the set of objects that need to be combined.
    */
    virtual void get_objects_to_combine(std::list<T>&) = 0;


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
