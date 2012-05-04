/*
 * File:   RNAFold.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 1, 2010, 1:35 PM
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

#ifndef _RNAFOLD_H
#define _RNAFOLD_H

#include "IFold.h"
#include "RNABackendProxy.h"
/**
 * Implementation using the Vienna Package
 */
class RNAFold : public IFold
{
    static const FilePath IN;
    static const FilePath OUT;
    static const FileLineNo LINE_NO;
    size_t read_free_energy(FileLine&, size_t, Fe&) const throw(RNABackendException);
    virtual Fe fold(const biopp::NucSequence&, SecStructure&, bool circ) const throw(RNABackendException);
};

#endif  /* _RNAFOLD_H */

