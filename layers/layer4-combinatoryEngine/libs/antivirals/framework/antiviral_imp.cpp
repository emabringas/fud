/**
 * \file  antiviral.cpp
 * \brief implementation of Antiviral class.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:      CPP file for ASO providing class Antiviral.
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

#include "antiviral_imp.h"

using namespace std;

std::ostream& operator<< (std::ostream &out, const AvType& atype)
{
    switch (atype)
    {
    case tRT:
        out << "tRT";
        break;
    case tPI:
        out << "tPI";
        break;
    case tComb:
        out << "tComb";
        break;
    default:
        out.setstate(std::ios::failbit); //set error bit in is
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, const AvClass& aclass)
{
    switch (aclass)
    {
    case cPI:
        out << "cPI";
        break;
    case cNRTI:
        out << "cNRTI";
        break;
    case cNNRTI:
        out << "cNNRTI";
        break;
    case cComb:
        out << "cComb";
        break;
    default:
        out.setstate(std::ios::failbit); //set error bit in is
    }
    return out;
}

std::istream& operator>> (std::istream& is, AvType& atype)
{
    string s;

    if (is >> s)
    {
        if (s == "tRT")
            atype = tRT;
        else if (s == "tPI")
            atype = tPI;
        else if (s == "tComb")
            atype = tComb;
        else
            is.setstate(std::ios::failbit); //set error bit in is
    }
    return is;
}

std::istream& operator>> (std::istream& is, AvClass& aclass)
{
    string s;

    if (is >> s)
    {
        if (s == "cPI")
            aclass = cPI;
        else if (s == "cNRTI")
            aclass = cNRTI;
        else if (s == "cNNRTI")
            aclass = cNNRTI;
        else if (s == "cComb")
            aclass = cComb;
        else
            is.setstate(std::ios::failbit); //set error bit in is
    }
    return is;
}

void ResisBasedAntiviral::combine_with(ResisBasedAntiviral& other) const
{
    CAutonomousIterator<ResisBasedAntiviral::Resistances> it(resistances);

    while (!it.end())
    {
        size_t pos_temp = it->pos;
        std::string amin_temp = it->aminoacids;

        AutonomousIterator<ResisBasedAntiviral::Resistances> it2(other.resistances);
        bool found(false);

        while (!it2.end())
        {
            if (pos_temp == it2->pos)
            {
                for (size_t i = 0; i < amin_temp.size(); ++i)
                {
                    if (!is_in(amin_temp[i], it2->aminoacids))
                    {
                        it2->aminoacids += amin_temp[i];
                    }
                }
                found = true;
            }
            ++it2;
        }
        if (!found) other.add_resistance(pos_temp+1, amin_temp);
        ++it;
    }
}

void ResisBasedAntiviral::mutate_sequence(const PseudoNucSequence& sequence, MutantDist& mutations) const
{
    NucDistance min_dist = applies(sequence);
    if (min_dist > NucDistance(0))
    {
        CAutonomousIterator<Resistances> it(resistances);

        while (!it.end())
        {
            TripletVal tv = it->min_dist_to_resistance(sequence);
            NucDistance min_val = tv.second;
            TripletList triplets = tv.first;
            CAutonomousIterator<TripletList> trip_iter(triplets);

            while (!trip_iter.end())
            {
                PseudoNucSequence mutation = sequence;
                if (min_dist == min_val)
                {
                    mutation.set_triplet(it->pos, *trip_iter);
                    insert_into(mutations.sequences, mutation);
                }
                ++trip_iter;
            }
            ++it;
        }
        mutations.distance = min_dist;
    }
}

NucDistance ResisBasedAntiviral::applies(const PseudoNucSequence& sequence) const
{
    NucDistance min_dist(NucDistance(3));

    CAutonomousIterator<Resistances> it(resistances);
    while (!it.end() && min_dist>0)
    {
        TripletVal triplets_val = it->min_dist_to_resistance(sequence);
        min_dist = minimize(min_dist, triplets_val.second);
        ++it;
    }
    return min_dist;
}

ResisBasedAntiviral& ResisBasedAntiviral::add_resistance(size_t pos, const std::string& aminoacids)
{
    if (pos == 0)
    {
        throw "Incorrect resistence position (ResisBasedAntiviral::add_resistance)";
    }
    else
    {
        insert_into(resistances, ResistancePosition(pos-1, tolower(aminoacids)));
        return *this;
    }
}

ResisBasedAntiviral& ResisBasedAntiviral::add_attribute(const std::string& attrib, const std::string& value)
{
    set_attrib(attrib, value);
    return *this;
}

void ResisBasedAntiviral::print_resistances() const
{
    CAutonomousIterator<Resistances> it(resistances);

    while (!it.end())
    {
        std::cout << "(" << it->pos << ", " << it->aminoacids << ")" << std::endl;
        ++it;
    }
}

void ResisBasedAntiviral::print_antiviral() const
{
    std::cout << "----------Atributos---------- " << std::endl;
    print_attributes();
    std::cout << "----------Resistencias----------" << std::endl;
    print_resistances();
}

