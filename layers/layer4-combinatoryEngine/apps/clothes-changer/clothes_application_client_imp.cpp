/**
 *  @file:      clothes_application_client_imp.cpp
 *  @details     Implementation file for ClothesApplicationClientImp class.\n
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

#include "clothes_application_client_imp.h"
#include <combeng/combeng.h>

ClothesApplicationClientImp::ClothesApplicationClientImp()
    : L5ApplicationClient()
{
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

    mili::insert_into(_remeras, a);
    mili::insert_into(_remeras, b);
    mili::insert_into(_remeras, c);

    mili::insert_into(_pantalones, d);
    mili::insert_into(_pantalones, e);
    mili::insert_into(_pantalones, f);

    mili::insert_into(_zapatos, g);
    mili::insert_into(_zapatos, h);
    mili::insert_into(_zapatos, i);

    mili::insert_into(_medias, j);
    mili::insert_into(_medias, k);
    mili::insert_into(_medias, l);
}

ClothesApplicationClientImp::~ClothesApplicationClientImp()
{}

void ClothesApplicationClientImp::deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const
{
    mili::bistream<> bis(pkt);
    float score;
    std::list<Clothe> clothes_applied;
    std::list<Clothe> clothes_available;
    bis >> score >> clothes_applied >> clothes_available;

    // Crear 4 politicas lista.
    ListCombinationPolicy<Clothe>* comb_pantalones = new ListCombinationPolicy<Clothe>(NULL, "pantalones comb");
    ListCombinationPolicy<Clothe>* comb_remeras = new ListCombinationPolicy<Clothe>(NULL, "remeras comb");
    ListCombinationPolicy<Clothe>* comb_zapatos = new ListCombinationPolicy<Clothe>(NULL, "zapatos comb");
    ListCombinationPolicy<Clothe>* comb_medias = new ListCombinationPolicy<Clothe>(NULL, "medias comb");

    //creo el nodo
    ClothesNode* node = new ClothesNode(clothes_applied, clothes_available);

    // Crear politica compuesta
    ComposedCombinationPolicyParallel<Clothe>* composed = new ComposedCombinationPolicyParallel<Clothe>(node, "Clothes Changer");
    composed->add_new_combination_policy(comb_remeras, _remeras, false);
    composed->add_new_combination_policy(comb_pantalones, _pantalones, false);
    composed->add_new_combination_policy(comb_zapatos, _zapatos, false);
    composed->add_new_combination_policy(comb_medias, _medias, false);

    // Politica de poda
    PrunePolicy<Clothe>* prune = new PrunePolicy<Clothe>("Prune Clothes");

    node->set_combination_policy(composed);
    node->set_prune_policy(prune);
    node->set_table();

    //Lleno el parametro **rf
    *rf = node;
}
