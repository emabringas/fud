/**
 * \file  antiviral.h
 * \brief Definition of Antiviral class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing class Antiviral.
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

#ifndef ANTIVIRAL_H
#define ANTIVIRAL_H

#define NO_BITWISE_ENUMS
#include <mili/mili.h>
#include "sequence.h"


/*! Lista de tripletes para la aplicacion de las resistencias.*/
typedef std::set<Triplet> TripletList;

/*! Valor para las distancias entre mutantes. */
typedef float DistanceValue;

/*! Par que guarda las mutantes y la distancia mínima*/
struct MutantDist
{
    SequenceSet sequences;
    DistanceValue distance;

    /*! Constructor */
    MutantDist(): sequences(), distance()
    {}
    /*! Constructor por copia. */
    MutantDist(const SequenceSet& sequences, DistanceValue distance)
        : sequences(sequences), distance(distance)
    {}
};

/*! Par con la lista de tripletes y la distancia mínima.*/
typedef std::pair<TripletList, DistanceValue> TripletVal;
typedef VariantsSet AttribSet;

/*! Interfaz de Antiviral */
class Antiviral
{
    AttribSet attributes; //! todo el conjunto de atributos

public:
    Antiviral()
    {}
    /*! Constructor */
    Antiviral(const std::string& name)
    {
        attributes.insert("name", name);
    }

    /*! Constructor de Antiviral */
    Antiviral(const Antiviral& other)
    {
        attributes = other.attributes;
    }

    /*! Set/Reset de un atributo */
    template<class T>
    void set_attrib(const std::string& name, const T& initValue)
    {
        attributes.insert(name, initValue);
    }

    /*! Retorna un atributo de acuerdo al nombre */
    template<class T>
    bool get_attrib(const std::string& name, T& value) const throw(SystemError)
    {
        bool found(true);
        try
        {
            attributes.get_element(name, value);
        }
        catch (const BadElementType& exc)
        {
            throw SystemError("at Antiviral : Bad Attribute Type");
        }
        catch (const BadElementName& exc)
        {
            found = false;
        }
        return found;
    }

    /*! Dada una secuencia, saber si esta aplica a este antiviral */
    virtual NucDistance applies(const PseudoNucSequence& sequence) const = 0;

    /*! Devuelve las mutantes luego de aplicar este antiviral a la secuencia */
    virtual void mutate_sequence(const PseudoNucSequence& sequence, MutantDist& mutations) const = 0;

    /*! Destructor del tipo antiviral */
    ~Antiviral() {};

    /*! Imprime la lista de atributos del antiviral. */
    inline void print_attributes() const
    {
        std::string name, value;
        CAutonomousIterator<AttribSet> it(attributes);
        while (!it.end())
        {
            get_attrib(it->first, value);
            std::cout << it->first << ": " << value << "." << std::endl;
            ++it;
        }
    }

};

#endif
