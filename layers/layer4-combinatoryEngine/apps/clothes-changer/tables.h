/**
 *  @file:      tables.h
 *  @details    Header file for Tables class.\n
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
#ifndef TABLES_H
#define TABLES_H

//=================================
// included dependencies
#include <vector>

class tables
{
public:
    /*
     * constructor method. Initialization
     */
    tables();

    float remera_pantalon(std::string remera, std::string pantalon);

    float pantalon_zapato(std::string pantalon, std::string zapato);

    float zapato_media(std::string zapato, std::string media);

    //tables* void clone ();

private:
// tablas para las funciones de scoring
    std::vector < std::vector <int> > _tabla_remera_pantalon;
    std::vector < std::vector <int> > _tabla_pantalon_zapato;
    std::vector < std::vector <int> > _tabla_zapato_media;
};
#endif  /* TABLES_H */
