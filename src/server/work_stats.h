/**
 * \file  work_stats.h
 * \brief Definition of the abstract load balancer classes.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing the abstract load balancing classes.
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

#ifndef WORK_STATS_H
#define WORK_STATS_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include "common.h"

namespace fud
{
    /**
     * Statistical information about JobUnit being processed by a client.
     *
     * \sa JobUnit
     * \sa ClientProxy
     */
    struct StatisticalJobUnitInfo
    {
        /**
         * Standard constructor, should be avoided.
         */
        StatisticalJobUnitInfo() :
            id(0),
            size(0),
            time(boost::posix_time::microsec_clock::local_time())
        {
        }

        /**
         * Complete constructor.
         *
         * @param id : ID of the JobUnit being processed.
         * @param size : Size of the JobUnit being processed.
         * @param time : The time at which the JobUnit was sent to the client.
         *
         * \sa JobUnit
         * \sa ClientProxy
         */
        StatisticalJobUnitInfo(JobUnitID id, JobUnitSize size, boost::posix_time::ptime time) :
            id(id),
            size(size),
            time(time)
        {
        }

        JobUnitID                id;   /** ID of the JobUnit being processed. */
        JobUnitSize              size; /** ID of the JobUnit being processed. */
        boost::posix_time::ptime time; /** The time at which the JobUnit was sent to the client. */
    };

    /**
     * Abstract class to be used for load balancing.
     * Concrete instances of the class should implement some type of Running Average.
     * The results of the average should be returned in get_millisecs_per_size_unit.
     */
    struct WorkHistory
    {
        /**
         * Start work on a JobUnit.
         *
         * @param id : ID of the JobUnit being processed.
         * @param size : Size of the JobUnit being processed.
         */
        virtual void  start_work(JobUnitID id, JobUnitSize size) = 0;

        /**
         * End work on a JobUnit. Invoked when the results arrive.
         *
         * @param id : ID of the JobUnit being processed.
         */
        virtual void  end_work(JobUnitID id)              = 0;

        /**
         * Results on the calculated Running Average.
         * This is some type of mean of milliseconds used for
         * each JobUnitSize unit.
         *
         * \sa JobUnit
         * \sa JobUnitSize
         */
        virtual float get_millisecs_per_size_unit()      = 0;
    };
}
#endif

