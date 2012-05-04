/**
 * \file  distributable_job.h
 * \brief Definition of DistributableJob class.
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

#ifndef DISTRIBUTABLE_JOB_H
#define DISTRIBUTABLE_JOB_H

#include <string>
#include <set>

#include <boost/thread.hpp>

#include "job_unit.h"
#include "common.h"
#include "events.h"

/**
 * \namespace fud
 * Namespace for FuD project.
 */
namespace fud
{

    /** Status of a DistributableJob instance. */
    enum DistributableJobStatus
    {
        ReadyToProduce      /** Its ready to produce another Job Unit. */ ,
        WaitingMoreData     /** Its waiting for more data or some event, can't produce a Job Unit at the moment. */ ,
        FinishedGenerating  /** From here on, it won't produce any more Job Units. */
    };

    /** Interface for events generated by DistributableJob instances. */
    struct DistributableJobListener
    {
        /**
         * Event signaling the completion of a DistributableJob.
         * @param distob : The pointer to the DistributableJob instance that is completed.
         */
        virtual void distributable_job_completed_event(DistributableJob* distob) = 0;
    };

    /**
     * A general work concept.
     * A DistributableJob is a concept of work that can be further subdivided. It is a central notion
     * of the framework. A DistributableJob will be divided into one or more JobUnits.
     *
     * One should note that processing clients can't handle DistributableJobs, but only JobUnits or,
     * to be more precise, their messages.
     *
     * \sa JobUnit
     * \sa DistributableJobImplementation
     */
    struct DistributableJob
    {
        /* Used by the JobManager. */
        /**
         * Wrapper invoked to handle the results of a particular JobUnit. It will forward the
         * call to handle_results, implemented by the inhereting class.
         * @param id      : ID of the completed JobUnit.
         * @param message : The result itself (contains the message from the processing client.)
         *
         * \sa handle_results
         */
        virtual void        process_results  (JobUnitID id, const std::string* message) = 0;
        /**
         * Produces a JobUnit. It wraps a call to produce_next_job_unit and generates the
         * corresponding event. The DistributableJob must change state after generating it,
         * so calls to the method won't produce duplicate JobUnits.
         *
         * @param size : The size suggested for the JobUnit that is to be generated. It is only
         *               to be taken as a guidance.
         *
         * \sa JobUnit
         */
        virtual JobUnit*               get_next_job_unit(JobUnitSize  size) = 0;

        /* What the application layer developer needs to implement. */
        /**
         * Returns the status of a DistributableJob. This method is used for synchronization with the
         * rest of the system, so care must be taken in its implementation. It is imperative that the
         * method returns ReadyToProduce iff it is immediately ready to produce a JobUnit and also
         * return FinishedGenerating iff it won't produce any more JobUnits in the future.
         * \sa DistributableJobStatus
         */
        virtual DistributableJobStatus get_status()                   const = 0;
        /** Returns the name of this particular DistributableJob. Used for logging purposes. */
        virtual const char*            get_name()                     const = 0;
    };

    /**
     * Implementation of a general work concept that can be subdivided. This is an abstract
     * class. Its divisions will be JobUnits.
     * \sa DistributableJob
     * \sa JobUnit
     */
    class DistributableJobImplementation : protected DistributableJob
    {
        public:
            /* Interface for main*/
            /**
             * Standard way to get the job started. The Job will enqueue itself on the JobManager.
             * The L3-Implementer should only call this method if the Job will be ready to answer
             * to get_status(), so whatever data is used in the project should be initialized.
             * \sa JobManager
             */
            void  run();
            /**
             * Standard way to wait for the completion of this Job. This method will lock the calling
             * thread until it completes.
             */
            void  wait_completion();

            virtual ~DistributableJobImplementation(){};
        protected:
            /**
             * Used internally, enqueues itself on the JobManager.
             * \sa JobManager
             */
            DistributableJobImplementation();

        private:
            /**
             * Checks to see if this JobUnit was completed. To prevent the handling of duplicate
             * results this method checks with the set of completed JobUnitIDs.
             * @param id : The JobUnitID to check for.
             * \sa JobUnit
             * \sa JobUnitID
             */
            bool  completion_accepted(JobUnitID id);

            /* For app-layer developer.*/
            /**
             * Handle the results of a completed JobUnit.
             * The method is called upon completion of a JobUnit, the resulting message is
             * encapsulated by the processing client in the input parameter.
             *
             * @param id    : The JobUnitID of the completed JobUnit.
             * @param input : The stream of data with the results.
             *
             * \sa JobUnit
             * \sa JobUnitID
             */
            virtual void                   handle_results   (JobUnitID id, InputMessage& input) = 0;
            /**
             * To produce another JobUnit. It will only be called on a DistributableJob whose status is
             * ReadyToProduce.
             *
             * @param size : The size of the expected JobUnit, it is to be used as a guide and is not
             *               mandatory.
             *
             * The concept of size is user defined and will generally be problem dependant.
             * It is advised that the size definition for a particular implementation is proportional to
             * the actual size of the message.
             *
             * \sa JobUnit
             */
            virtual JobUnit*               produce_next_job_unit(JobUnitSize  size)             = 0;
            /**
             * Returns the status of a DistributableJob. This method is used for synchronization with the
             * rest of the system, so care must be taken in its implementation. It is imperative that the
             * method returns ReadyToProduce iff it is immediately ready to produce a JobUnit and also
             * return FinishedGenerating iff it won't produce any more JobUnits in the future.
             * \sa DistributableJobStatus
             */
            virtual DistributableJobStatus get_status()                                   const = 0;
            /** Returns the name of this particular DistributableJob. Used for logging purposes. */
            virtual const char*            get_name()                                     const = 0;

            /* Implemented here, checks with completion_accepted first, then calls handle_results. */
            virtual void        process_results (JobUnitID id, const std::string* message);

            /* Calls produce_next_job_unit, if not null, calls inform_generation. */
            JobUnit* get_next_job_unit(JobUnitSize  size);

            /* Used by wait_completion. */
            bool    finished();

            /* Called by get_next_job_unit. */
            void  inform_generation();

            /* Attributes. */
            DistributableJobListener* const _listener;

            /** Stores the set of IDs of all completed JobUnits from this DistributableJob. */
            std::set<JobUnitID> _completed;           /*when _completed.size() = _j_u_gen then */
                                                      /*the job is completed.                  */
            /** Amount of generated job units. */
            size_t              _job_units_generated;

            boost::mutex              _completed_mutex;
            boost::mutex              _job_units_generated_mutex;
            boost::condition_variable _condition;

            InputMessage              _input;
    };
}
#endif
