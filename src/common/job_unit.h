/**
 * \file  job_unit.h
 * \brief Definition of JobUnit class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributableJob.
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

#ifndef JOB_UNIT_H
#define JOB_UNIT_H

#include <string>

#include "common.h"
#include "mili/mili.h"

namespace fud
{

    /**
     * Implementation of an undivisible work concept. A Job Unit represent a unit of work
     * to be performed by a processing client. Its _message_ can be obtained via the method
     * serialize, which should later be interpreted by the client, who (in turn) will produce
     * a response message.
     *
     * \sa DistributableJob
     * \sa StreamingJobUnit
     */
    class JobUnit
    {
    public:
        /** Returns the message this JobUnit has for the client that is to process it. */
        const std::string&  serialize()            const;

        /** Returns the current JobUnit's ID. */
        inline  JobUnitID   get_id()               const
        {
            return _id;
        }
        /** Returns the current JobUnit's size. */
        inline  JobUnitSize get_size()             const
        {
            return _size;
        }

        virtual ~JobUnit() {};
    protected:
        /**
         * Standard constructor, it will increment the count of total JobUnits created.
         */
        JobUnit();

        /**
         * Used by the concrete classes inhereting from JobUnit. The concept of *size* is
         * user defined and will generally be problem dependant. It is advised that the *size*
         * definition for a particular implementation is proportional to the actual size of the
         * message.
         * @param size : The size of the expected JobUnit, it is to be used as a guide and is not
         *               mandatory.
         */
        void  set_size(JobUnitSize size);
    private:
        /**
         * The implementer of the method must return the exact message he wants to transmit to
         * the processing client on the receiving end. This message should be formed using mili's
         * binary streams library[0] to pack data in a single string.
         * [0]: see <htpp://mili.googlecode.com>
         */
        virtual const std::string&  get_message()          const = 0;

        static JobUnitID    _last_generated;   /* Id of the last generated JobUnit. */
        JobUnitID           _id;               /* Id of current JobUnit. */
        JobUnitSize         _size;             /* Size of current JobUnit, this is user defined. See set_size method. */

        /* IMPORTANT: this is why they came up with mutable. Careful analysis took place before putting mutable here. */
        mutable OutputMessage       _output_message;   /* Message inmanent in the JobUnit, doesn't change. */
        mutable mili::FirstTimeFlag _string_pending;   /* Flag concerning readyness of message string. */
    };

    /**
     * A concrete JobUnit that can be used as an OutputMessage, it is very useful for simple types
     * of JobUnits
     *
     * \sa JobUnit
     */
    class StreamingJobUnit : public JobUnit
    {
    public:
        /**
         * Standard constructor.
         *
         * \sa JobUnit
         */
        StreamingJobUnit();

        /**
         * Insert an element to the JobUnit.
         *
         * @param x : The data to be inserted.
         *
         * \sa OutputMessage
         */
        template<typename T>
        StreamingJobUnit& operator<< (T x)
        {
            _output << x;
            return *this;
        }

        /**
         * Wrapper for the JobUnit method.
         *
         * @param size : The size of the JobUnit.
         *
         * \sa JobUnit
         */
        using JobUnit::set_size;
    private:
        OutputMessage _output;

        virtual const std::string& get_message() const;
    };
}

#endif

