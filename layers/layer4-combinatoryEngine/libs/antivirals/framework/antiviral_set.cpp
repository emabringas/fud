/**
 * \file  antiviral_set.cpp
 * \brief implementation of AntiviralSet class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:      CPP file for ASO providing class AntiviralSet.
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

#include "antiviral_set.h"


void AntiviralSet::combine_set(ResisBasedAntiviral& combined)
{
    ResisBasedAntiviral aux("Aux", 0, tComb, cComb);
    AVIterator it(antivirals);

    while (!it.end())
    {
        (*it)->combine_with(combined);
        ++it;
    }
}

void AntiviralSet::observe_mutants(const PseudoNucSequence& sequence, MutantDist& mutant_list)
{
    AVIterator it(antivirals);
    while (!it.end())
    {
        (*it)->mutate_sequence(sequence, mutant_list);
        ++it;
    }
}

void AntiviralSet::add_antiviral(const ResisBasedAntiviral& antiviral)
{
    insert_into(antivirals, &antiviral);
}

/*! Filtra el conjunto de antivirales y retorna un ativiralSet con los antivirales filtrados */
void filter_by_group(const Avs& in, const AttribSet& terms, Avs& out)
{
    out = in;
    AttribSet::const_iterator it = terms.begin();
    while (it != terms.end() && !out.empty())
    {
        Avs aux2;
        filter(out, it->first, it->second, aux2);
        out = aux2;
        ++it;
    }
}

void AntiviralSet::get_info(std::string& out) const
{
    std::string name;
    CAutonomousIterator<Avs> it(antivirals);
    while (!it.end())
    {
        (*it)->get_attrib("name", name);
        out += name;
        out += " + ";
        ++it;
    }
}

