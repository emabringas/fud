/**
 *  @file:      clothes_node.cpp
 *  @details    Implementation file for ClothesNode class.\n
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
// included dependencies
#include "clothes_node.h"
#include <combeng/combeng.h>
#include <set>
#include <list>
#include <iostream>



using namespace comb_eng;

ClothesNode::ClothesNode(std::list<Clothe> combination, ClothesNode* father)
    : L4Node<Clothe>(father->get_combination_policy()->clone(this), new PrunePolicy <Clothe> ("Prune Clothes"))
{
    _clothes_applied = father->_clothes_applied;
    std::list<Clothe>::iterator it;

    //agrega la combinacion a la ropa aplicada
    it = combination.begin();
    while (it != combination.end())
    {
        _clothes_applied.push_back(*(it));
        ++it;
    }

    //Elimina de la ropa disponible, la ropa que esta en la combinacion
    _clothes_available = (father->_clothes_available);
    it = combination.begin();
    while (it != combination.end())
    {
        _clothes_available.remove(*it);
        ++it;
    }
    set_table();
}

bool ClothesNode::is_leaf()
{
    return (_clothes_applied.size() == 4);
}

void ClothesNode::serialize(recabs::Packet& pkt)
{
    mili::bostream<> bos;
    bos << this->score() << this->_clothes_applied << this->_clothes_available;
    pkt = bos.str();
}

void ClothesNode::get_objects_to_combine(std::list<Clothe>& res)
{
    res = this->_clothes_available;
}

float ClothesNode::score()
{
    float result(0);
    if (this->is_leaf())
    {
        std::list<Clothe> cpy_applied;
        cpy_applied = (this->_clothes_applied);
        std::string remera(cpy_applied.front().get_colour());

        cpy_applied.pop_front();
        std::string pantalon(cpy_applied.front().get_colour());
        cpy_applied.pop_front();
        std::string zapato(cpy_applied.front().get_colour());
        cpy_applied.pop_front();
        std::string media(cpy_applied.front().get_colour());
        cpy_applied.pop_front();
        //std::cout << remera << " "<< pantalon << " " << zapato << " " << media << "\n" <<std::endl;
        result = _tables->remera_pantalon(remera, pantalon) + _tables->pantalon_zapato(pantalon, zapato) +
                 _tables->zapato_media(zapato, media);
    }
    return result;
}

void ClothesNode::new_children(const std::list<Clothe>& new_comb, std::list<comb_eng::L4Node<Clothe>*>& children)
{
    // for sure, the list will have just one element
    ClothesNode* child = new ClothesNode(new_comb, this);
    children.push_back(child);
}

recabs::Packet ClothesNode::get_result()
{
    mili::bostream<> bos;
    bos << this->score() << this->_clothes_applied ;

    recabs::Packet pkt = bos.str();
    return pkt;
}
