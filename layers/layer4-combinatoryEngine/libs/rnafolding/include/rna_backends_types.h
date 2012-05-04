/*
 * File:   rna_backends_types.h
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

#ifndef _RNA_BACKENDS_TYPES_H
#define _RNA_BACKENDS_TYPES_H

#include <set>
#include <list>
#include <string>
#include <vector>

#include "rna_backends_exceptions.h"

/**
 * Index position in a sequence
 */
typedef unsigned int SeqIndex;

class SecStructure
{
    static const char OPEN_PAIR = '(';
    static const char CLOSE_PAIR = ')';
    static const char UNPAIR = '.';

    std::vector<SeqIndex> structure;

    void parse_structure(const std::string& structure, size_t length) throw(InvalidStructureException);
    inline SeqIndex unpaired_value() const
    {
        return structure.size();
    }
public:
    SecStructure();
    SecStructure(const std::string& structure) throw(InvalidStructureException);
    SecStructure& operator=(const std::string& str) throw(InvalidStructureException);

    void pair(SeqIndex, SeqIndex) throw(InvalidStructureException);
    void unpair(SeqIndex);
    std::string to_str() const;

    inline bool is_paired(SeqIndex idx) const
    {
        return structure[idx] != unpaired_value();
    }

    inline size_t pair_length() const
    {
        size_t paired = 0;
        for (SeqIndex i = 0; i < structure.size(); ++i)
        {
            if (is_paired(i))
                paired++;
        }
        return paired / 2;
    }

    inline size_t size() const
    {
        return structure.size();
    }
};

/**
 * Distance between sequences
 */
typedef float Distance;

/**
 * Similitude between sequences or structures
 */
typedef float Similitude;

/**
 * Free eneregy in secodary structure
 */
typedef float Fe;

/**
 * Container of raw (string) RNA sequences
 */
typedef std::set<std::string> StringSequencesCt;

/**
 * Number of combination attemps.
 */
typedef unsigned int CombinationAttempts;

/**
 * Filename path
 */
typedef std::string FilePath;

typedef std::string FileLine;

typedef std::string Command;

typedef unsigned int FileLineNo;

typedef std::list<std::string> FileLinesCt;

#define SUCCESS_EXEC 0
#define MATRIX_SIZE 4

#endif  /* _RNA_BACKENDS_TYPES_H */

