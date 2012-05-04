/**
 *  @file:      tables.cpp
 *  @details    Implementation file for Tables class.\n
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
#include <string>
#include <iostream>
#include <stdexcept>
#include "tables.h"

using namespace std;

tables::tables()
{
    _tabla_remera_pantalon.resize(3);
    _tabla_pantalon_zapato.resize(3);
    _tabla_zapato_media.resize(3);
    int i;
    for (i = 0; i < 3; ++i)
    {
        _tabla_remera_pantalon[i].resize(3);
        _tabla_pantalon_zapato[i].resize(3);
        _tabla_zapato_media[i].resize(3);
    }
    // inicializacion de las 3 tablas
    int value(-1);
    int j;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            ++value;
            _tabla_remera_pantalon.at(i).at(j) = value;
            _tabla_pantalon_zapato.at(i).at(j) = value;
            _tabla_zapato_media.at(i).at(j) = value;
        }
    }

    /*******************************************
     *    azul    *    negro     *   marron    *
    *****************************************************
    * roja    *     0      *      1       *      2      *
    *****************************************************
    * amarilla*     3      *      4       *      5      *
    *****************************************************
    * negra   *     6      *      7       *      8      *
    *****************************************************/
}

float tables::remera_pantalon(std::string remera, std::string pantalon)
{
    int row_index;  // indice de remera
    if (remera.compare("roja") == 0)
        row_index = 0;
    else if (remera.compare("amarilla") == 0)
        row_index = 1;
    else
        row_index = 2;

    int col_index;
    if (pantalon.compare("azul") == 0)
        col_index = 0;
    else if (pantalon.compare("negro") == 0)
        col_index = 1;
    else
        col_index = 2;
    return _tabla_remera_pantalon[row_index][col_index];
}

float tables::pantalon_zapato(std::string pantalon, std::string zapato)
{
    int row_index;  // indice de pantalon
    if (pantalon.compare("azul") == 0)
        row_index = 0;
    else if (pantalon.compare("negro") == 0)
        row_index = 1;
    else
        row_index = 2;

    int col_index;
    if (zapato.compare("goma") == 0)
        col_index = 0;
    else if (zapato.compare("cuero") == 0)
        col_index = 1;
    else
        col_index = 2;
    return _tabla_pantalon_zapato[row_index][col_index];
}

float tables::zapato_media(std::string zapato, std::string media)
{
    int row_index;  // indice de pantalon
    if (zapato.compare("goma") == 0)
        row_index = 0;
    else if (zapato.compare("cuero") == 0)
        row_index = 1;
    else
        row_index = 2;

    int col_index;
    if (media.compare("negra") == 0)
        col_index = 0;
    else if (media.compare("azul") == 0)
        col_index = 1;
    else
        col_index = 2;
    return _tabla_zapato_media[row_index][col_index];
}
