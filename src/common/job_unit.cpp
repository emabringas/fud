/**
 * \file  job_unit.cpp
 * \brief Implementation file for JobUnit class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class DistributableJob.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
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
       _output_message << get_id() << get_message(); // inserting the string completes the header

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
