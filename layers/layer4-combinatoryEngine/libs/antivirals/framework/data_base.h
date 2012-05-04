/**
 * \file  data_base.h
 * \brief Definition of DataBase class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing class DataBase.
 *
 * System:         ASO
 * Language:       C++
 *
 * Author:         Velez Ezequiel, Peralta Andres
 * E-Mail:
 *
 * ASO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ASO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ASO.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <mili/mili.h>
#include "antiviral_set.h"

/*! Definicion de la Clase DataBase */
class DataBase
{
private:

    /*! Conjunto real de antivirales */
    typedef std::list<ResisBasedAntiviral> Antivirals;
    typedef std::list<std::string> Names;

    const char* file;
    Antivirals antivirals;
    Antivirals validated_antivirals;

public:

    /*! Constructor*/
    DataBase(const char* file_name)
    {
        file = file_name;
        load_file(file_name);
        copy_antivirals();
    }

    /*! Destructor */
    ~DataBase() {}

    /*! Carga la base de datos a partir de un XML. */
    void load_file(const char* file_name);

    /*! Imprime los datos de la base. */
    void print_database();

    /*! Copia los antivirales */
    void copy_antivirals();

    /*! Devuelve el iterador del conjunto */
    AVIterator get_iterator();

    /*! Referencia un conjunto de antivirales a uno de punteros de antivirales!*/
    void get_antivirals(AntiviralSet& antiviral_set);

    /*! Ignora los antivirales de la lista. Es utilizado por el plugin */
    void ignore_antivirals(const Names& names);

    /*! Retorna la cantidad de registros que la BD posee. */
    inline size_t size() const
    {
        return antivirals.size();
    }
};


#endif

