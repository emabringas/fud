/*
 * File:   RNABackendProxy.h
 * Author: Santiago Videla <santiago.videla at gmail.com>
 *
 * Created on October 26, 2010, 4:31 PM
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

#ifndef _RNABACKENDPROXY_H
#define _RNABACKENDPROXY_H
#include <cstdlib>
#include <fstream>
#include <string>
#include <mili/mili.h>

#include "rna_backends_types.h"
#include "rna_backends_exceptions.h"

using std::string;

/**
 * Execute a give command using a system call
 * @param cmd the RNA backend command
 */
inline void exec(const Command& cmd) throw(RNABackendException)
{
    const int status = system(cmd.c_str());
    if (status != SUCCESS_EXEC)
        throw RNABackendException("An error ocurred trying to execute: " + cmd);
}

/**
 * Write a file with multiple lines.
 * @param file the file path
 * @param lines the lines to write
 */
void write(const FilePath& file, FileLinesCt& lines) throw(RNABackendException);

/**
 * Write a file with a single line.
 * @param file the file path
 * @param line the line to write
 */
void write(const FilePath& file, FileLine& line) throw(RNABackendException);

/**
 * Read a line from a file
 * @param file the file path
 * @param lineno the line number to read
 * @param line where to write the read line
 */
void read_line(const FilePath& file, FileLineNo lineno, FileLine& line) throw(RNABackendException);

/**
 * Read a value from a file line using offset and length
 * @param line the file line
 * @param offset the offset in the line
 * @param n the length to read
 * @param t where to write the value.
 */
template<class T>
inline void read_value(const FileLine& line, FileLine::size_type offset, size_t n, T& t) throw(RNABackendException)
{
    const bool success = mili::from_string(line.substr(offset, n), t);
    if (!success)
        throw RNABackendException("Could not read the value from given line, offset and length");
}

/**
 * Read a value from a line file.
 * @param line the file line
 * @param t where to write the value
 */
template<class T>
inline void read_value(const FileLine& line, T& t) throw(RNABackendException)
{
    const bool success = from_string(line, t);
    if (!success)
        throw RNABackendException("Could not read the value from given line");
}


#endif  /* _RNABACKENDPROXY_H */

