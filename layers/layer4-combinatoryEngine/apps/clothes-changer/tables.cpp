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