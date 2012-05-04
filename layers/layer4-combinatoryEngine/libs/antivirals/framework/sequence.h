/**
 * \file  sequence.h
 * \brief Definition of SequenceSet and Resistance Type.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing type SequenceSet and Resistance.
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

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <biopp/biopp.h>
#include "aso_exception.h"
#include <mili/mili.h>

/*! Redefinición de Conjunto de Secuencias de Aminoacidos a SequenceSet */
typedef std::list<PseudoNucSequence> SequenceSet;

/*! Carga una Secuencia de Nucleótidos a partir de un archivo */
void load_sequence(const char* seq_file, PseudoNucSequence& sequence);

/*! Imprime la sequencia de aminoacidos o de nucleotidos */
void print_sequence(const PseudoNucSequence& sequence);

/*! Verifica si un caracter s se encuentra en el string s */
bool is_in(const char a, const std::string& s);
#endif

