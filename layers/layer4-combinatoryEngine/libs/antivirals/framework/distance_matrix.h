/**
 * \file  distance_matrix.h
 * \brief Definition of Distance Matrix.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing Distance Matrix.
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

#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "sequence.h"
const size_t SIZE = 4;

extern DistanceMatrix matrix; //global (:()

/*! Esta funcion define la mariz de distancia entre nucleótidos.*/
void set_default_matrix(DistanceMatrix& defaultm);

#endif

