/**
 * \file  antiviral_selector.h
 * \brief Definition of Antiviral Selector class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010, 2012 Velez Ezequiel, Peralta Andres, FuDePAN, Bettiol Favio, Diaz Diego
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
#ifndef ANTIVIRAL_SELECTOR_H
#define ANTIVIRAL_SELECTOR_H


#include <iostream>
#include <cmath>

#include "data_base.h"
#include "optimized_container.h"

const double PMUT = 1.0 / 10000;

struct Av_ProbPair
{
    Av_ProbPair(const ResisBasedAntiviral& av, double prob)
        : _av(av), _prob(prob) {}

    ResisBasedAntiviral _av;
    double _prob;

    bool operator < (const Av_ProbPair& other) const
    {
        return (_prob < other._prob);
    }
};


struct Av_ProbPair_Unique
{
    bool operator()(const Av_ProbPair& p1, const Av_ProbPair& p2) const
    {
        std::string av_1;
        std::string av_2;
        p1._av.get_attrib("name", av_1);
        p2._av.get_attrib("name", av_2);
        return av_1 > av_2;
    }
};

struct Av_ProbPair_Ranking
{
    bool operator()(const Av_ProbPair& p1, const Av_ProbPair& p2) const
    {
        return p1._prob < p2._prob;
    }
};

typedef UniqueRanker<Av_ProbPair, Av_ProbPair_Ranking, Av_ProbPair_Unique> Rank_Av_Prob;

class AntiviralSelector
{
public:
    void select_antivirals(const AntiviralSet& antiviral_set, const PseudoNucSequence& sequence, AntiviralSet& applicable_avs);
    void rank_antivirals(const AntiviralSet& antiviral_set, const PseudoNucSequence& sequence, Rank_Av_Prob& rank);

private:

    template <class T>
    static inline T factorial(size_t n)
    {
        static const T value[] = { T(1), T(1), T(2), T(6) };
        return value[n];
    }


};

/* Selecciona los antivirales que aplican del conjunto antiviral_set y que tienen distancia maxima */
inline void AntiviralSelector::select_antivirals(const AntiviralSet& antiviral_set, const PseudoNucSequence& sequence, AntiviralSet& applicable_avs)
{
    /* iterador hacia los antivirales disponibles */
    AVIterator it(antiviral_set.antivirals);

    OptimizedContainer<Avs, NucDistance, MaximumValues, NotIncludingZero> keepMaxValue(applicable_avs.antivirals, NucDistance(0));

    while (!it.end())
    {
        /* distancia que tiene el antiviral al que esta apuntando el iterador */
        const NucDistance distance = (*it)->applies(sequence);
        keepMaxValue.add(*it, distance);
        ++it;
    }
}



//Devuelve una lista de pares (antiviral, probabilidad), donde "probabilidad" representa las chances que tiene el virus de escapar a tal antiviral
inline void AntiviralSelector::rank_antivirals(const AntiviralSet& antiviral_set, const PseudoNucSequence& sequence, Rank_Av_Prob& rank)
{
    for (AVIterator it_av(antiviral_set.antivirals); !it_av.end(); ++it_av)
    {
        double p = 0.0;
        if ((*it_av)->applies(sequence) > 0)
        {
            ResisBasedAntiviral::Resistances resistances;
            (*it_av)->get_resistaces(resistances);
            for (std::list<ResisBasedAntiviral::ResistancePosition>::const_iterator it_res = resistances.begin(); it_res != resistances.end(); ++it_res)
            {
                for (std::string::const_iterator amino = it_res->aminoacids.begin(); amino != it_res->aminoacids.end(); ++amino)
                {
                    for (TripletsIterator it_t = GeneticCode::triplets(*amino); !it_t.end(); ++it_t)
                    {
                        const PseudoTriplet original_triplet = sequence.get_triplet(it_res->pos);
                        const size_t distance = original_triplet.distance(PseudoTriplet(it_t->to_string()));
                        p += std::pow(PMUT, distance) * factorial<double>(distance);
                    }
                }
            }
        }
        Av_ProbPair pair(**it_av, p);
        rank.insert(pair);
    }
}



#endif
