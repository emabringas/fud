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
#include "../../client/l5_application_client.h"
#include "clothes_node.h"


using namespace comb_eng;
class ClothesApplicationClientImp : public comb_eng::L5ApplicationClient
{
private:
    // conjuntos de referencias para las diferentes politicas
    std::set<Clothe*> _pantalones;
    std::set<Clothe*> _remeras;
    std::set<Clothe*> _medias;
    std::set<Clothe*> _zapatos;

    tables* tabla_valores;
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
     * For implementation. From L5ApplicationClient (comb_eng)
     */
    virtual void deserialize(const recabs::Packet& pkt, recabs::SerializableRecursiveFunctor** rf) const;
};
#endif  /* _CLOTHES_APPLICATION_MAIN_CLIENT_H */