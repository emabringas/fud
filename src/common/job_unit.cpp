/**
 * \file  job_unit.cpp
 * \brief Implementation file for JobUnit class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * @author     Guillermo Biset
 * @email      billybiset AT gmail.com
 *  
 * @author     Mariano Bessone
 * @email      marjobe AT gmail.com
 *
 * @author     Emanuel Bringas
 * @email      emab73 AT gmail.com
 *
 * FuD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FuD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FuD.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "job_unit.h"

using namespace fud;

JobUnitID JobUnit::_last_generated = 0;

JobUnit::JobUnit() :
    _id(++_last_generated),
    _output_message(),
    _string_pending()
{
}

void  JobUnit::set_size(JobUnitSize size)
{
    _size = size;
}

/* All JobUnits are serialized the same way. */
const std::string& JobUnit::serialize() const
{
    if (_string_pending)  /* header + message */
    {
        fud_size size_of_message = HEADER_SIZE + SERVER_HEADER_LENGTH + sizeof(JobUnitID) + sizeof(fud_size) + get_message().size() * sizeof(char);
        _output_message << size_of_message << kJob << get_id() << get_message();
    }
    return _output_message.str();
}

StreamingJobUnit::StreamingJobUnit() :
    _output()
{
}

const std::string& StreamingJobUnit::get_message() const
{
    return _output.str();
}
