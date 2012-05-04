/**
 * \file  antiviral_set.h
 * \brief Definition of AntiviralSet class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing class AntiviralSet.
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

#ifndef ANTIVIRAL_SET_H
#define ANTIVIRAL_SET_H

#include <mili/mili.h>
#include "antiviral_imp.h"

typedef std::set<const ResisBasedAntiviral*> Avs;
typedef std::list< ResisBasedAntiviral::Resistances > AvsResistancesList;


struct TripletPos_Pair
{
    size_t pos;
    Triplet triplet;

    TripletPos_Pair(size_t p, Triplet t)
    {
        pos = p;
        triplet = t;
    }
};

typedef std::list <std::list <TripletPos_Pair> > AvResistanceTriplets;

struct AntiviralSet
{
    ~AntiviralSet() {}

    /*! Redefinicion uns a lista de antivirales a Antiviral Set. */
    Avs antivirals;

    /*! Operador de Equivalencia */
    inline bool operator==(const AntiviralSet& other) const
    {
        return antivirals == other.antivirals;
    }

    /*! Agrega un antiviral al conjunto */
    void add_antiviral(const ResisBasedAntiviral& antiviral);

    /*! Funcion para obtener un conjunto de secuencias producto de aplicar este antiviral a la secuencia dada */
    void observe_mutants(const PseudoNucSequence& sequence, MutantDist& mutant_list);

    /*! Combina un conjunto de antivirales. */
    void combine_set(ResisBasedAntiviral& combined);

    /*! Imprime los nombres de los antivirales que contiene */
    void get_info(std::string& out) const;

    /*! Serializa en antiviralSet*/
    friend inline bostream& operator<< (bostream& bos, const AntiviralSet& avs)
    {
        Avs::iterator it = avs.antivirals.begin();

        while (it != avs.antivirals.end())
        {
            bos << (**it);
            ++it;
        }

        ResisBasedAntiviral aux("marca#end", 0, tComb, cComb);
        bos << aux;

        return bos;
    }

    /*! Deserializa en antiviralSet*/
    friend inline bistream& operator>> (bistream& bis, AntiviralSet& avs)
    {

        ResisBasedAntiviral* aux = new ResisBasedAntiviral("aux", 0, tComb, cComb);
        bis >> (*aux);

        std::string name;
        aux->get_attrib("name", name);

        //cambiar la estructura del ciclo a un do-while
        while (name != "marca#end")
        {
            avs.add_antiviral(*aux);
            aux = new ResisBasedAntiviral("aux", 0, tComb, cComb);
            bis >> *aux;
            aux->get_attrib("name", name);
        }
        return bis;
    }


    void split_antivirals_by_type(std::list<ResisBasedAntiviral>& nrti, std::list<ResisBasedAntiviral>& nnrti, std::list<ResisBasedAntiviral>& pi) const
    {
        std::string avclass;
        Avs::const_iterator it = this->antivirals.begin();
        while (it != this->antivirals.end())
        {
            (*it)->get_attrib("class", avclass);
            if (avclass == "cNRTI")
                nrti.push_back(**it);
            else if (avclass == "cNNRTI")
                nnrti.push_back(**it);
            else if (avclass == "cPI")
                pi.push_back(**it);

            ++it;
        }
    }

    void clone(AntiviralSet& new_avs) const
    {

        Avs::iterator it_a = new_avs.antivirals.begin();
        for (Avs::iterator it = this->antivirals.begin(); it != this->antivirals.end(); ++it)
        {
            ResisBasedAntiviral* aux = new ResisBasedAntiviral(**it);
            new_avs.antivirals.insert(aux);
            ++it_a;
        }
    }


    /*!Ddevuelve una lista con el id de cada antiviral*/
    void to_id_list(std::list<size_t>& res_list) const
    {
        size_t id;
        for (Avs::iterator it = antivirals.begin(); it != antivirals.end(); ++it)
        {
            (*it)->get_attrib("id", id);
            res_list.push_back(id);
        }
    }


    /*!Eelimina del antiviralSet this, todos los antivirales cuya id pertenezca al parametro*/
    void remove(const std::list<size_t>& id_to_rem)
    {
        for (std::list<size_t>::const_iterator it_ids = id_to_rem.begin(); it_ids != id_to_rem.end(); ++it_ids)
            remove_id(*it_ids);
    }


    /*!Elimina, si existe, el antiviral con id = id_to_rem */
    void remove_id(size_t id_to_rem)
    {
        Avs::iterator it_av = find(id_to_rem);
        if (it_av != antivirals.end())
            antivirals.erase(it_av);
    }


    /*! Devuelve el iterador posicionado en el elemento con id = it_target, si el mismo pertenece. Si no, en antivirals.end().*/
    Avs::iterator find(size_t id_target) const
    {
        Avs::iterator it_av = antivirals.begin();
        bool found = false;
        size_t id;
        while (it_av != antivirals.end() and !found)
        {
            (*it_av)->get_attrib("id", id);
            found = (id == id_target);
            if (!found)
                ++it_av;
        }
        return it_av;
    }


    /*!Devuelve un conjunto de antivirales igual al this, pero solo con los ids de la lista*/
    void select(const std::list<size_t>& ids, AntiviralSet& selection) const
    {
        for (Avs::const_iterator it = antivirals.begin(); it != antivirals.end(); ++it)
        {
            size_t id;
            (*it)->get_attrib("id", id);

            for (std::list<size_t>::const_iterator itt = ids.begin(); itt != ids.end(); ++itt)
            {
                if (id == (*itt))
                    selection.add_antiviral(**it);
            }
        }
    }


    /*! Calcula las mutaciones que se obtienen de una secuencia a partir de este antiviralSet*/
    void get_mutants(const PseudoNucSequence& seq, std::list<PseudoNucSequence>& mutants) const
    {
        std::list<PseudoNucSequence> mutants_tmp;
        std::list<PseudoNucSequence> new_seqs;
        AvsResistancesList list_of_resistances;

        combine_resistances(list_of_resistances);
        for (AvsResistancesList::iterator it = list_of_resistances.begin(); it != list_of_resistances.end(); ++it)
        {
            apply_resistances(*it, seq, new_seqs);
            copy_container(new_seqs, mutants);
            new_seqs.clear();

        }

    }


private:

    /*********************************************************************
    	Metodos untilizados para la manipulacion de resistencias
    **********************************************************************/
    /*! Obtiene el producto carteciano de resistencias, aplica las reglas y se queda con las listas de menor longitud */
    void combine_resistances(AvsResistancesList& result) const
    {
        std::set<const ResisBasedAntiviral*>::const_iterator it_avs = this->antivirals.begin();
        generate_resistances_lists(this->antivirals, it_avs, result);
        filter_by_rules(result);
        //No puedo ir calculando el conjunto minimo mientras lo obtengo porque puede que las reglas me modifiquen algun subconjunto.
        minimize(result);
    }


    /*! Genera el producto cartesiano de las resistencias de los antivirales */
    void generate_resistances_lists(const Avs& avs, const Avs::const_iterator& it_avs, AvsResistancesList& result,
                                    ResisBasedAntiviral::Resistances partial_result = ResisBasedAntiviral::Resistances()) const
    {
        // base case
        if (it_avs == avs.end())
        {
            insert_into(result, partial_result);
        }
        // inductive case
        else
        {
            ResisBasedAntiviral::Resistances current_resistances = (*it_avs)->get_resistances();
            split_resistances(current_resistances);
            for (ResisBasedAntiviral::Resistances::iterator it_res = current_resistances.begin(); it_res != current_resistances.end(); ++it_res)
            {
                ResisBasedAntiviral::ResistancePosition res_position = (*it_res);
                ResisBasedAntiviral::Resistances new_partial_result;
                copy_container(partial_result, new_partial_result);
                insert_into(new_partial_result, res_position);
                Avs::const_iterator it_avs_tmp = it_avs;
                generate_resistances_lists(avs, ++it_avs_tmp , result, new_partial_result);
            }
        }
    }


    /*! Aplica a cada subconjunto de resistencias las dos reglas*/
    void filter_by_rules(AvsResistancesList& in_out) const
    {
        for (AvsResistancesList::iterator it = in_out.begin(); it != in_out.end(); ++it)
        {
            if (it->size() > 1)
            {
                if (check_rule_1(*it)) // Si se da el caso, este subconjunto debe eliminarse dado que no es posible que
                    // en una misma posicion hayan dos aminoacidos diferentes.
                    it->clear();
                else
                    apply_rule_2(*it);
            }
        }
    }


    /*! Es el caso de P1(X) ^ P1(Y)
     * Retorna true si se da el caso diferentes aminoacidos en una misma posicion. False, en caso contrario.
     */
    bool check_rule_1(const ResisBasedAntiviral::Resistances& resistances) const
    {
        bool ret = false;
        ResisBasedAntiviral::Resistances::const_iterator it = resistances.begin();
        while (it != resistances.end() and !ret)
        {
            ResisBasedAntiviral::Resistances::const_iterator it_in = it;
            ++it_in;
            while (it_in != resistances.end() and !ret)
            {
                if ((it->pos == it_in->pos) and (it->aminoacids != it_in->aminoacids))
                    ret = true;
                ++it_in;
            }
            ++it;
        }
        return ret;
    }


    /*! Caso de P1(X) ^ P1(X). Elimina repetidos, dejando una sola instancia */
    void apply_rule_2(ResisBasedAntiviral::Resistances& resistances) const
    {
        ResisBasedAntiviral::Resistances resistance_tmp;
        bool is_in;
        for (ResisBasedAntiviral::Resistances::iterator it = resistances.begin(); it != resistances.end() ; ++it)
        {
            is_in = check_membership(*it, resistance_tmp);
            if (!is_in)
                insert_into(resistance_tmp, *it);
        }
        resistances = resistance_tmp;
    }


    /*!Devuelve true si "res_pos" es una de las posiciones de resistencia de "resistance" */
    bool check_membership(const ResisBasedAntiviral::ResistancePosition& res_pos, const ResisBasedAntiviral::Resistances& resistance) const
    {
        ResisBasedAntiviral::Resistances::const_iterator it = resistance.begin();
        bool found = false;
        while (it != resistance.end() and !found)
        {
            if (*it == res_pos)
                found = true;
            ++it;
        }
        return found;
    }


    /*! Filtra la lista quedandose solo con aquellos subconjuntos de resistencia de longitud minima */
    void minimize(AvsResistancesList& result) const
    {
        AvsResistancesList result_tmp;
        // en lugar de 10 habria q poner una cota superior
        OptimizedContainer<AvsResistancesList, size_t, MinimumValues, NotIncludingZero> keepMinValues(result_tmp, 10);
        for (AvsResistancesList::iterator it = result.begin(); it != result.end(); ++it)
        {
            size_t size = it->size();
            keepMinValues.add(*it, size);
        }
        result = result_tmp;
    }


    /*! Si existen resistencia de la forma "pos 1 -> GT", las separa en dos, "pos 1 -> G" y "pos 1 -> T" */
    void split_resistances(ResisBasedAntiviral::Resistances& resistances) const
    {
        ResisBasedAntiviral::Resistances result;
        for (ResisBasedAntiviral::Resistances::iterator it_res = resistances.begin(); it_res != resistances.end(); ++it_res)
        {
            if (it_res->aminoacids.size() == 1)
            {
                insert_into(result, *it_res);
            }
            else
            {
                for (std::string::iterator it_amin = it_res->aminoacids.begin(); it_amin != it_res->aminoacids.end(); ++it_amin)
                {
                    std::string aminoacid = std::string(&(*it_amin), 1); // strings of size one.
                    ResisBasedAntiviral::ResistancePosition res_tmp(it_res->pos, aminoacid);
                    insert_into(result, res_tmp);
                }
            }
        }
        resistances = result;
    }


    /*********************************************************************
    		Metodos untilizados para la manipulacion de Tripletes
    **********************************************************************/
    /*!Aplica una resistencia (lista de posiciones con sus respectivos aminoacidos) a una secuancia y obtiene las mutantes. */
    void apply_resistances(const ResisBasedAntiviral::Resistances& resistances, const PseudoNucSequence& seq, std::list<PseudoNucSequence>& seqs) const
    {
        AvResistanceTriplets triplets_for_resistance;
        for (ResisBasedAntiviral::Resistances::const_iterator it_resis = resistances.begin(); it_resis != resistances.end(); ++it_resis)
        {
            //Para cada posicion de resistencia, se guardan los tripletes de minima distancia con respecto al aminoacido de la posicion.
            std::list <TripletPos_Pair> triplets_one_position;
            get_min_triplets(seq, *it_resis, triplets_one_position);
            insert_into(triplets_for_resistance, triplets_one_position);
        }

        AvResistanceTriplets triplets_combined;
        combine_triplets(triplets_for_resistance, triplets_for_resistance.begin(), triplets_combined);
        for (AvResistanceTriplets::const_iterator it_all = triplets_combined.begin(); it_all != triplets_combined.end(); ++it_all)
        {
            PseudoNucSequence new_seq;
            mutate_sequence(seq, *it_all, new_seq);
            insert_into(seqs, new_seq);
        }
    }



    /*! Genera el producto cartesiano de los tripletes */
    void combine_triplets(const AvResistanceTriplets& triplets_for_resistance,
                          const AvResistanceTriplets::const_iterator& it_triplet,
                          AvResistanceTriplets& result,
                          std::list <TripletPos_Pair> partial_result = std::list <TripletPos_Pair> ()
                         ) const
    {
        /*!si triplets_for_resistance = A, luego de aplicar combine_triplets(), deberia quedar como B:

                                   {(1,[acg]) , (1,[gdc])}                          {(1,[acg]),(2,[tas]),(3,[saw])}
                            A= {   {(2,[tas])}               }              B= {    {(1,[acg]),(2,[tas]),(3,[sad])}    }
                                   {(3,[saw]), (3,[sad])}                           {(1,[gdc]),(2,[tas]),(3,[saw])}
                                                                                    {(1,[gdc]),(2,[tas]),(3,[sad])}
        */

        // base case
        if (it_triplet == triplets_for_resistance.end())
        {
            insert_into(result, partial_result);
        }
        // inductive case
        else
        {
            for (std::list<TripletPos_Pair>::const_iterator it_res = it_triplet->begin(); it_res != it_triplet->end(); ++it_res)
            {
                std::list <TripletPos_Pair>  new_partial_result;
                new_partial_result = partial_result;
                insert_into(new_partial_result, *it_res);
                AvResistanceTriplets::const_iterator it_triplet_tmp = it_triplet;
                combine_triplets(triplets_for_resistance, ++it_triplet_tmp, result, new_partial_result);
            }
        }
    }


    /*!Dada una secuencia y una posicion de resistencia con su amino, devuelve los tripletes con min dist por los q se puede reemplazar el amino.*/
    void get_min_triplets(const PseudoNucSequence& seq, const ResisBasedAntiviral::ResistancePosition& res_position,
                          std::list <TripletPos_Pair>& result_triplets) const
    {
        size_t pos = res_position.pos;
        //amino es siempre un string de longitud 1 (porque las posiciones de resistencia ya vienen filtradas por split_resistances()
        std::string amino = res_position.aminoacids;
        Triplet triplet_seq(seq.get_triplet(pos).to_string());

        size_t max_dist(3);
        OptimizedContainer<std::list <TripletPos_Pair>, size_t, MinimumValues, IncludingZero> min_triplets(result_triplets, max_dist);
        for (TripletsIterator triplet = GeneticCode::triplets(amino[0]); !triplet.end(); ++triplet)
        {
            TripletPos_Pair triplet_tmp(pos, *triplet);
            size_t distance = triplet_seq.distance(*triplet);
            min_triplets.add(triplet_tmp, distance);
        }
    }

    /*!Cambia los tripletes de la secuencia seq por los que se encuentran en "triplets".*/
    void mutate_sequence(const PseudoNucSequence& seq, const std::list <TripletPos_Pair>& triplets, PseudoNucSequence& new_seq) const
    {
        new_seq = seq;
        for (std::list <TripletPos_Pair>:: const_iterator it = triplets.begin(); it != triplets.end(); ++it)
            new_seq.set_triplet(it->pos, it->triplet);
    }

};

/*! Filtra el conjunto de antivirales de acuerdo a un atributo */
template<class T>
bool filter(const Avs& in, const std::string& condName, const T& condValue, Avs& out)
{
    bool success(false);
    CAutonomousIterator<Avs> it(in);
    while (!it.end())
    {
        T aux;
        if ((*it)->get_attrib(condName, aux))       //! si contiene el atributo
        {
            if (aux == condValue)                   //! si concuerda el valor
            {
                insert_into(out, *it);
                success = true;
            }
        }
        ++it;
    }
    return success;
}

/*! Filtra el conjunto de antivirales de acuerdo a un conjunto de atributos */
void filter_by_group(const Avs& in, const AttribSet& terms, Avs& out);

/*! Iterador del Conjunto de Antivirales */
typedef CAutonomousIterator<Avs> AVIterator;

#endif
