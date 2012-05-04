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

#ifndef ANTIVIRAL_IMP_H
#define ANTIVIRAL_IMP_H

#include <mili/mili.h>
#include "antiviral.h"
#include "distance_matrix.h"
#include "optimized_container.h"

const NucDistance MAX_VAL = NucDistance(3);
const NucDistance ZERO_DISTANCE = NucDistance(0);

/*! Clase del antiviral. */
enum AvClass
{
    cPI, /*! Class Protease Inhibitor.         */
    cNRTI, /*! Class Nucletotide Reverse Transcriptasa Inhibitor  */
    cNNRTI, /*! Class Non Nucletotide Reverse Transcriptase Inhibitor */
    cComb    /*! Combinated class.           */
};

/*! Tipo del Antiviral. */
enum AvType
{
    tRT, /*! Type Reverse Transcriptasa. */
    tPI, /*! Type Proteasa Inhibitor  */
    tComb /*! Combinated Type    */
};

/*! Para que funcione bien el filter con enumerados*/
std::ostream& operator<< (std::ostream& out, const AvType& atype);
std::ostream& operator<< (std::ostream& out, const AvClass& aclass);
std::istream& operator>> (std::istream& is, AvClass& aclass);
std::istream& operator>> (std::istream& is, AvType& atype);

/*! Clase Antiviral:
 Clase que implementa a un antiviral asociandoles una secuencia de aminoacidos, un nombre, un tipo,
 una clase y un id unico.
*/
class ResisBasedAntiviral: public Antiviral
{
public:
    /* Posición de las Resistencias*/
    struct ResistancePosition
    {
        size_t pos;
        string  aminoacids;

        //ResistancePosition() {}

        ResistancePosition(size_t pos, const std::string aminoacids)
            : pos(pos), aminoacids(aminoacids)
        {}

        ResistancePosition(const ResistancePosition& other)
            : pos(other.pos), aminoacids(other.aminoacids)
        {}

        ~ResistancePosition() {}

        friend inline bostream& operator<< (bostream& bos, const ResistancePosition& res_position)
        {
            bos << res_position.pos << res_position.aminoacids;

            return bos;
        }

        friend inline bistream& operator>> (bistream& bis, ResistancePosition& res_position)
        {
            size_t pos;
            string aminoacids;
            bis >> pos;
            bis >> aminoacids;
            res_position = ResisBasedAntiviral::ResistancePosition(pos, aminoacids);

            return bis;
        }

        //Retorna un par con la lista de tripletes y la distancia mínima.
        TripletVal min_dist_to_resistance(const PseudoNucSequence& sequence) const
        {
            TripletVal min_list;
            OptimizedContainer<TripletList, NucDistance, MinimumValues, IncludingZero> keepMinValue(min_list.first, MAX_VAL);
            const PseudoTriplet pos_triplet = sequence.get_triplet(pos);
            for (size_t i = 0; i < aminoacids.size(); ++i)
            {
                for (TripletsIterator itResTriplets = GeneticCode::triplets(aminoacids[i]); !itResTriplets.end(); ++itResTriplets)
                {
                    for (TripletsIterator itPureT = pos_triplet.getPureTriplets(); !itPureT.end(); ++itPureT)
                    {
                        const NucDistance distance = (*itResTriplets).distance(*itPureT, matrix);
                        keepMinValue.add(*itResTriplets, distance);
                    }
                }
            }

            min_list.second = keepMinValue.getBestValue();

            return min_list;
        }

        void getString(std::string& s) const
        {
            std::stringstream position;
            position << pos;
            s = "| " + position.str() + " --> " + aminoacids + " |";
        }

        bool operator==(const ResistancePosition& other) const
        {
            std::string s, s1;
            this->getString(s);
            other.getString(s1);
            return (s == s1);
        }


    };

    /* Lista de Resistencias */
    typedef std::list<ResistancePosition> Resistances;


    friend inline bostream& operator<< (bostream& bos, const Resistances& res)
    {
        bos << res.size();
        for (Resistances::const_iterator it = res.begin(); it != res.end(); ++it)
        {
            bos << (*it).pos;
            bos << (*it).aminoacids;
        }

        return bos;
    }

    friend inline bistream& operator>> (bistream& bis, Resistances& res)
    {
        int size, index = 0;
        bis >> size;
        while (index < size)
        {
            size_t pos;
            string aminoacids;
            bis >> pos;
            bis >> aminoacids;
            res.push_back(ResistancePosition(pos, aminoacids));
        }

        return bis;
    }

private:
    Resistances     resistances;

public:

    friend inline bostream& operator<< (bostream& bos, const ResisBasedAntiviral& rba)
    {
        /*hay antivirales, por ej con id=0, que tienen mas atributos de los q estamos serializando (percio, toxicidad...etc).
         Agregar estos atributos a la serializacin y deserializacion */

        std::string name;
        size_t id;
        AvClass aclass;
        AvType atype;
        rba.get_attrib("name", name);
        bos << name;
        rba.get_attrib("id", id);
        bos << id;
        rba.get_attrib("class", aclass);
        bos << aclass;
        rba.get_attrib("Type", atype);
        bos << atype;

        Resistances::const_iterator it = rba.get_resistances().begin();
        while (it != rba.get_resistances().end())
        {
            bos << (*it);
            ++it;
        }

        ResistancePosition aux(-1, "marca#end");
        bos << aux;

        return bos;
    }

    friend inline bistream& operator>> (bistream& bis, ResisBasedAntiviral& rba)
    {
        std::string name;
        size_t id;
        AvClass aclass;
        AvType atype;
        ResisBasedAntiviral::Resistances resistances;

        bis >> name;
        rba.set_attrib("name", name);
        bis >> id;
        rba.set_attrib("id", id);
        bis >> aclass;
        rba.set_attrib("class", aclass);
        bis >> atype;
        rba.set_attrib("Type", atype);


        Resistances resist_list;
        ResistancePosition aux(-1, " ");
        bis >> aux;
        while (aux.aminoacids != "marca#end")
        {
            insert_into(resist_list, ResistancePosition(aux.pos, tolower(aux.aminoacids)));
            bis >> aux;
        }
        rba.set_resisteces(resist_list);
        return bis;
    }


    ResisBasedAntiviral()
    {}

    /*! Constructor del tipo antiviral con todos los parametros */
    ResisBasedAntiviral(const std::string& name, size_t id, AvType avtype, AvClass avclass)
        : Antiviral(name)
    {
        set_attrib("id", id);
        set_attrib("class", avclass);
        set_attrib("Type", avtype);
    }

    /*! Constructor por copia */
    ResisBasedAntiviral(const ResisBasedAntiviral& other)
        : Antiviral(other), resistances(other.resistances)
    {}

    /*! Obtener la lista de resistencias */
    inline const Resistances& get_resistances() const
    {
        return resistances;
    }

    /*! Agregar una resistencia en una posicion determinada. */
    ResisBasedAntiviral& add_resistance(size_t pos, const std::string& aminoacid);

    /*! Agregar un nuevo atributo al antiviral.*/
    ResisBasedAntiviral& add_attribute(const std::string& attrib, const std::string& value);

    /*! Imprime la información del Antiviral.*/
    void print_antiviral() const;

    /*! Imprime las resistencas. */
    void print_resistances() const;

    /*! Combina otro antiviral con este */
    void combine_with(ResisBasedAntiviral& other) const;

    /*! Dada una secuencia, saber si esta aplica a este antiviral */
    virtual NucDistance applies(const PseudoNucSequence& sequence) const;

    /*! Devuelve las mutantes luego de aplicar este antiviral a la secuencia */
    virtual void mutate_sequence(const PseudoNucSequence& sequence, MutantDist& mutations) const;

    /*! Devuelve true si el antiviral this tiene el mismo id que other*/
    inline bool operator == (const ResisBasedAntiviral& other) const
    {
        std::string id_this;
        std::string id_other;

        this->get_attrib("id", id_this);
        other.get_attrib("id", id_other);

        return (id_this == id_other);
    }

    /*! Setea la lista de resistencias*/
    void set_resisteces(Resistances resist)
    {
        copy_container(resist, resistances);
    }

    void get_resistaces(Resistances& resist) const
    {
        copy_container(resistances, resist);
    }

};

/*! Una mutante describe la secuencia y el antiviral que se aplico */
typedef std::pair<Antiviral, PseudoNucSequence> Mutant;

#endif
