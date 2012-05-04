/**
 *  @file:      clothes_application_server_imp.cpp
 *  @details    Implementation file for ClothesApplicationServerImp class.\n
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


#include "clothes_application_server_imp.h"
#include <mili/mili.h>


ClothesApplicationServerImp::ClothesApplicationServerImp()
    : L5ApplicationServer<Clothe>()
{
    std::list<Clothe> applicated;
    _root_node = new ClothesNode(applicated, get_initial_set());
}

ClothesApplicationServerImp::~ClothesApplicationServerImp()
{

}

void ClothesApplicationServerImp::get_initial_packet(recabs::Packet& pkt) const
{
    _root_node->serialize(pkt);
}

void ClothesApplicationServerImp::receive_result(const recabs::Packet& pkt)
{
    mili::bistream bis(pkt);
    float score;
    std::list<Clothe> clothes_applied;
    bis >> score >> clothes_applied;
    manage_top_dressed(score, clothes_applied);
}

void ClothesApplicationServerImp::manage_top_dressed(const float& score, const std::list<Clothe>& clothes)
{
    std::list<ResultClothe>::reverse_iterator top5_it ;
    top5_it = _top_5_dressed.rbegin();

    while (score >= top5_it->get_score() && top5_it != _top_5_dressed.rend())
        ++top5_it;

    ResultClothe new_clothe(score, clothes);
    _top_5_dressed.insert(top5_it.base(), new_clothe);
    if (_top_5_dressed.size() > 5)
        _top_5_dressed.pop_back();
}

L4Node<Clothe>* ClothesApplicationServerImp::get_initial_node()
{
    _root_node->set_clothes_available(get_initial_set());
    return _root_node;
}

std::list<Clothe> ClothesApplicationServerImp::get_initial_set()
{
    std::list<Clothe> objects;
    Clothe a("remera", "roja");
    Clothe b("remera", "amarilla");
    Clothe c("remera", "negra");
    Clothe d("pantalon", "azul");
    Clothe e("pantalon", "negro");
    Clothe f("pantalon", "marron");
    Clothe g("zapato", "goma");
    Clothe h("zapato", "deportivo");
    Clothe i("zapato", "cuero");
    Clothe j("media", "negra");
    Clothe k("media", "azul");
    Clothe l("media", "blanca");

    mili::insert_into(objects, a);
    mili::insert_into(objects, b);
    mili::insert_into(objects, c);
    mili::insert_into(objects, d);
    mili::insert_into(objects, e);
    mili::insert_into(objects, f);
    mili::insert_into(objects, g);
    mili::insert_into(objects, h);
    mili::insert_into(objects, i);
    mili::insert_into(objects, j);
    mili::insert_into(objects, k);
    mili::insert_into(objects, l);

    return objects;
}
