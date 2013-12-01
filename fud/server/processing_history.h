/**
 * \file  processing_history.h
 * \brief Definition of ProcessingHistory class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class ProcessingHistory.
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

#ifndef PROCESSING_HISTORY_H
#define PROCESSING_HISTORY_H

#include <list>
#include "fud/server/work_stats.h"
#include "fud/common/job_unit.h"

namespace fud
{
    /**
     * Information about the processing of a single JobUnit.
     *
     * \sa JobUnit.
     */
    struct CompletedWork
    {
        /**
         * Standard constructor.
         *
         * @param size : The size of the completed JobUnit.
         * @param ms_elapsed : Milliseconds elapsed to compute the results.
         *
         * \sa JobUnit
         */
        CompletedWork(JobUnitSize size, size_t elapsed) : size(size), ms_elapsed(elapsed) {}
        JobUnitSize size;        /* Used defined.    */
        size_t      ms_elapsed;  /* In milliseconds. */
    };

    /**
     * A Dummy implementation of a WorkHistory, used for load balancig.
     * Implements a Running Average. In this case its just a simple moving
     * average of the last <b>max_size</b> values.
     *
     * \sa WorkHistory
     */
    class ProcessingHistory : public WorkHistory
    {
        public:
            /**
             * Constructs a Simple Moving Average implementation using
             * the last <b>max_size</b> data points.
             *
             * @param max_size : The maximum size of the data points list.
             */
            ProcessingHistory(size_t max_size);
        private:
            virtual void  start_work(JobUnitID id, JobUnitSize size);
            virtual void  end_work  (JobUnitID id);

            virtual float get_millisecs_per_size_unit();

            std::list<StatisticalJobUnitInfo> _history;

            size_t                            _max_size;

            std::list<CompletedWork>          _sizes_and_times; /* Its size won't go above max_size. */
    };
}
#endif
