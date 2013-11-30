/**
 * \file  processing_history.cpp
 * \brief Implementation file for ProcessingHistory class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class ProcessingHistory.
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

#include "fud/server/processing_history.h"

namespace fud
{

ProcessingHistory::ProcessingHistory(size_t max_size) :
    _history(),
    _max_size(max_size),
    _sizes_and_times()
{
}

void  ProcessingHistory::start_work(JobUnitID id, JobUnitSize size)
{
    _history.push_back(StatisticalJobUnitInfo(id, size,boost::posix_time::ptime(boost::posix_time::microsec_clock::local_time())) );
}

void  ProcessingHistory::end_work  (JobUnitID id)
{
    std::list<StatisticalJobUnitInfo>::iterator it;
    for (it = _history.begin(); it != _history.end() && it->id != id; ++it)
        ;

    if (it != _history.end())
    {         // add elapsed time
        _sizes_and_times.push_back(CompletedWork(it->size, boost::posix_time::time_period(it->time, boost::posix_time::ptime(boost::posix_time::microsec_clock::local_time())).length().total_milliseconds() ));

        if (_max_size > 0)
            --_max_size;
        else  // forget the old values
            _sizes_and_times.pop_front();

        _history.erase(it);
    }
}

float ProcessingHistory::get_millisecs_per_size_unit()
{
    JobUnitSize acum_size(0);
    size_t acum_time(0);

    for (std::list<CompletedWork>::iterator it(_sizes_and_times.begin()); it != _sizes_and_times.end(); ++it)
    {
        acum_size += it->size;
        acum_time += it->ms_elapsed;
    }
    return static_cast<float>(acum_time) / static_cast<float>(acum_size);
}

} // end namespace