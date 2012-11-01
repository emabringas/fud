#ifndef JOB_LISTENER_H
#define JOB_LISTENER_H

namespace fud
{
    struct JobListener
    {
        /**
         * Tries to assign a JobUnit to client_id.
         *
         * @param[in] client_id The client to assign the job unit
         * @param[in] job_unit The job to send to client_id
         *
         * @returns <b>true</b> if the JobUnit was succesfully assigned
         *          to a free client, <b>false</b> otherwise.
         *
         * \sa JobUnit
         */
        virtual bool assign_job_unit(ClientID client_id, const JobUnit& job_unit) = 0;
    };
}


#endif
