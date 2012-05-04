/*
 * File:   IFold.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on September 26, 2010, 5:25 PM
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

#ifndef _IFOLD_H
#define _IFOLD_H

#include <biopp/biopp.h>
#include "rna_backends_types.h"
#include "rna_backends_exceptions.h"

/**
 * Interface for sequence's folding services.
 */
class IFold
{
public:
    /**
     * Fold an ARN sequence
     * @param sequence the ARN sequence to fold.
     * @param structure the structure where to write the folding.
     * @param circ if the structure it's circular.
     * @return The free energy in the structure.
     */
    virtual Fe fold(const biopp::NucSequence&, SecStructure&, bool) const THROW((RNABackendException)) = 0;

    virtual ~IFold() {}
};

#endif  /* _IFOLD_H */

