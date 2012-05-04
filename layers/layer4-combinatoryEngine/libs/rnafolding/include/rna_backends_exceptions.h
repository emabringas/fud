/*
 * File:   rna_backends_exceptions.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 27, 2010, 6:42 PM
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

#ifndef _RNA_BACKENDS_EXCEPTIONS_H
#define _RNA_BACKENDS_EXCEPTIONS_H

#include <mili/mili.h>
#ifndef NO_THROW_SPEC
#       define THROW(x) throw x
#else
#       define THROW(x)
#endif

class RNABackendExceptionRoot {};

DEFINE_SPECIFIC_EXCEPTION_TEXT(RNABackendException, RNABackendExceptionRoot, "RNABackend");

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidStructureException, RNABackendExceptionRoot, "Invalid structure");

DEFINE_SPECIFIC_EXCEPTION_TEXT(CombinatorException, RNABackendExceptionRoot, "Out of range");

#endif  /* _RNA_BACKENDS_EXCEPTIONS_H */

