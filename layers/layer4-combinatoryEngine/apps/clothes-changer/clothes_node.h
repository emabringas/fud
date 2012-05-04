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
// included dependencies
#include <combeng/combeng.h>
#include <mili/mili.h>
#include <list>
#include "clothe.h"
#include "tables.h"

class ClothesNode : public comb_eng::L4Node<Clothe>
{

private:
    tables* _tables;
    std::list<Clothe> _clothes_applied;
    std::list<Clothe> _clothes_available;


protected:
    /**
     * from L4Node
     */
    virtual void new_children(const std::list<Clothe>& combination, std::list<comb_eng::L4Node<Clothe>*>&);
    virtual recabs::Packet get_result();


public:
    /**
     * Constructor methods.
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

    ClothesNode(std::list<Clothe> combination, ClothesNode* father);

    /**
     * Destroyer method.   El metodo ~L4Node es virtual... VER ESTO
     */
    ~ClothesNode()
	{
		delete _tables;
	};


    /**
     * Set the table for the node. It can be imroved.
     */
    inline void set_table()
    {
        _tables = new tables();
    }

    /**
     * Get the node's table.
     */
    inline tables* get_table() const
    {
        return _tables;
    }


    /**
     * from L4Node
     */
    virtual bool is_leaf();
    virtual void serialize(recabs::Packet& pkt);
    virtual void get_objects_to_combine(std::list<Clothe>&);
    virtual float score();

};

#endif  /* _CLOTHES_NODE_H */
