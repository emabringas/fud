/*
 * File:   RNAFold.cpp
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on November 10, 2010, 4:26 PM
 *
 * Copyright (C) 2010  Santiago Videla, FuDePAN
 *
 * This file is part of vac-o
 *
 * vac-o is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vac-o is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vac-o.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <sstream>
#include <mili/mili.h>
#include "RNAFold.h"
#include "RNABackendsConfig.h"
#include "RNABackendsFactory.h"

using std::stringstream;

const FilePath RNAFold::IN = "fold.in";
const FilePath RNAFold::OUT = "fold.out";
const FileLineNo RNAFold::LINE_NO = 1;

class RNAFoldRegisterer
{
public:
    RNAFoldRegisterer() { RNABackendsFactory::Instance()->Register<RNAFold>("rnafold"); }
//    static RNAFoldRegisterer _hiden;
};
static RNAFoldRegisterer _hiden;

Fe RNAFold::fold(const biopp::NucSequence& sequence, SecStructure& structure, bool circ) const throw(RNABackendException)
{
    FileLine sseq;
    for (size_t i = 0; i < sequence.length(); ++i)
        sseq += sequence[i].as_char();

    write(IN, sseq);

    stringstream ss;
    ss << "RNAfold" << " -noPS ";
    if (circ)
        ss << "-circ ";
    ss << "< " << IN << " > " << OUT;
    const Command CMD = ss.str();
    exec(CMD);

    /* fold.out look like this:
     * CGCAGGGAUCGCAGGUACCCCGCAGGCGCAGAUACCCUA
     * ...(((((((....(..((.....))..).))).)))). (-10.80)
    */
    FileLine aux;
    read_line(OUT, LINE_NO, aux);

    string str;
    read_value(aux, 0, sequence.length(), str);
    structure = str;

    Fe energy;
    read_free_energy(aux, sequence.length(), energy);
    return energy;
}

size_t RNAFold::read_free_energy(FileLine& line, size_t offset, Fe& energy) const throw(RNABackendException)
{
    try
    {
        const size_t from = mili::ensure_found(line.find_first_of("(", offset)) + 1;
        const size_t to = mili::ensure_found(line.find_first_of(")", from)) - 1;
        read_value(line, from, to - from, energy);
        return to;
    }
    catch (const mili::StringNotFound& e)
    {
        throw RNABackendException("Could not read free energy");
    }
}
