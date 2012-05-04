/**
 *  @file:      clothes_node.h
 *  @details    Header file for ClothesNode class.\n
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
#ifndef _CLOTHES_NODE_H
#define _CLOTHES_NODE_H

//=================================
// forward declared dependencies

//=================================
// included dependencies
#include <list>
#include "../../common/l4_node.h"
#include "clothe.h"
#include "tables.h"

class ClothesNode : public comb_eng::L4Node<Clothe>
{

private:
    tables* _tables;
    std::list<Clothe> _clothes_applied;
    std::list<Clothe> _clothes_available;


protected:
    /* from L4Node ******************************************************************/
    virtual std::list<comb_eng::L4Node<Clothe>*> new_children(const std::list<Clothe>& new_comb);
    virtual recabs::Packet get_result();
    /********************************************************************************/
    typedef  std::list<Clothe>::iterator clothes_it;
    void set_intersection(clothes_it clothes_b, clothes_it clothes_e, clothes_it comb_b, clothes_it comb_e, std::list<Clothe>* intersect);

public:
    /**
     * Constructor method.
     */
    ClothesNode()
        : comb_eng::L4Node<Clothe>()
    {};

    ClothesNode(std::list<Clothe> applied, std::list<Clothe> available, comb_eng::CombinationPolicy<Clothe>* comb_pol, comb_eng::PrunePolicy<Clothe>* prune)
        : comb_eng::L4Node<Clothe>(comb_pol, prune), _clothes_applied(applied), _clothes_available(available)
    {};

    ClothesNode(std::list<Clothe> applied, std::list<Clothe> available)
        : comb_eng::L4Node<Clothe>(), _clothes_applied(applied), _clothes_available(available)
    {};

    /**
     * Constructor method.
     */
    ClothesNode(std::list<Clothe> combination, ClothesNode* father);

    /**
     * Destroyer method.   El metodo ~L4Node es virtual... VER ESTO
     */
    ~ClothesNode()
    {};

    void set_clothes_available(const std::list<Clothe>& clothes);

    /* from L4Node ******************************************************/
    virtual bool is_leaf();
    virtual void serialize(recabs::Packet& pkt);
    virtual std::list<Clothe> get_objects_to_combine();
    virtual float score();
    /********************************************************************/

    /*  for tables ******************************************************/
    inline void set_table(tables* const t)
    {
        _tables = t;
    }

    inline tables* get_table() const
    {
        return _tables;
    }
};

#endif  /* _CLOTHES_NODE_H */
