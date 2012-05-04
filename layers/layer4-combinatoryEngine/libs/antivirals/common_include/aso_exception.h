/**
 * \file  aso_exception.h
 * \brief Definition of Exceptions.
 *
 * ASO: Antiviral Sequence Optimizer
 * <http://aso.googlecode.com/>
 * Copyright (C) 2010 Velez Ezequiel, Peralta Andres, FuDePAN
 *
 * This file is part of the ASO project.
 *
 * Contents:       Header file for ASO providing Exceptions.
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

#ifndef ASO_EXCEPTION_H
#define ASO_EXCEPTION_H

#include <mili/mili.h>

class ASOExceptionHierarchy {};

typedef GenericException<ASOExceptionHierarchy> ASOException;

/* ---------- Excepciones por valores discordantes --------------- */
DEFINE_SPECIFIC_EXCEPTION_TEXT(BadValue, ASOExceptionHierarchy, "Bad Value");

/* ----------- Excepciones por errores de usuario ---------------- */
DEFINE_SPECIFIC_EXCEPTION_TEXT(BadUseOfGUI, ASOExceptionHierarchy, "Bad Use of GUI");

/* --------- Excepciones errores internos del sistema ------------ */
DEFINE_SPECIFIC_EXCEPTION_TEXT(SystemError, ASOExceptionHierarchy, "SystemError");

/* --------- Excepciones errores internos del plugin ------------ */
DEFINE_SPECIFIC_EXCEPTION_TEXT(PluginError, ASOExceptionHierarchy, "Plugin Error");

/* --- Falta descripcion --- */
DEFINE_SPECIFIC_EXCEPTION_TEXT(SequenceError, ASOExceptionHierarchy, "Sequence Error");

#endif
