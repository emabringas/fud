/**
 *  @file:      clothes_application_client_imp.h
 *  @details    Header file for ClothesApplicationClientImp class.\n
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
#ifndef _CLOTHES_APPLICATION_CLIENT_IMP_H
#define _CLOTHES_APPLICATION_CLIENT_IMP_H

//=================================
// included dependencies
#include <mili/mili.h>
#include "clothes_node.h"

using namespace comb_eng;
class ClothesApplicationClientImp : public comb_eng::L5ApplicationClient
{
private:
    // conjuntos de referencias para las diferentes politicas
    std::list<Clothe> _pantalones;
    std::list<Clothe> _remeras;
    std::list<Clothe> _medias;
    std::list<Clothe> _zapatos;

public:
    /**
     * Constructor method.
     */
    ClothesApplicationClientImp();

    /**
     * Destroyer method.
     */
    ~ClothesApplicationClientImp();

    /**
     * To Implement. From L5ApplicationClient (comb_eng)
     */
    void deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const;

};
#endif  /* _CLOTHES_APPLICATION_MAIN_CLIENT_H */
