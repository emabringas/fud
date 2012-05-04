/**
 * \file  dummy_plugin.cpp
 * \brief implementation of functions for NucSequence.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:      CPP file for ASO providing functions for NucSequence.
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

#include "sequence.h"
#include <iostream>
#include <fstream>
#include <ctype.h>

void load_sequence(const char* seq_file, PseudoNucSequence& sequence)
{
    string line;

    std::ifstream infile(seq_file);

    if (infile)
    {
        getline(infile, line);
    }
    else
        throw "Sequence File not found";
    infile.close();

    PseudoNucSequence from_file(line);
    sequence = from_file;
    std::cout << "-- Sequence Loaded." << std::endl;
}

void print_sequence(const PseudoNucSequence& sequence)
{
    for (size_t i = 0; i < sequence.length(); ++i)
    {
        std::cout << to_str(sequence[i]);
    }
    std::cout << std::endl;
}

bool is_in(const char a, const string& s)
{
    bool is(false);

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (s[i] == a) is = true;
    }
    return is;
}

