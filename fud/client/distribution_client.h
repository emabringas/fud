/**
 * \file  distribution_client.h
 * \brief Definition of class DistributionClient.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class DistributionClient.
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

#ifndef DISTRIBUTION_CLIENT_H
#define DISTRIBUTION_CLIENT_H

#include <string>
#include <queue>
#include <boost/thread.hpp>
#include "fud/common/common.h"

namespace fud
{

/**
 * Abstract class for Client Communication.
 * Concrete subclasses will depend on the actual distributing middleware.
 * Implements a Singleton pattern.
 *
 * \sa AsyncIODistribution
 * \sa AnaDistribution
 *
 */
class DistributionClient
{
    public:

        /** Singleton method. */
        static DistributionClient*  get_instance() {return _instance; }

        /**
         * Destructor.
         */
        virtual ~DistributionClient();

        /**
         * Starts the communication part of the client application.
         * It should try to connect to the server for registration and
         * then wait incoming messages.
         */
        virtual void run()                                  = 0;

        /**
         * Should be implemented to send a string to the server.
         *
         * @param out : string to send.
         */
        virtual void dispatch(const std::string& out)       = 0;

        /**
         * Sends a message to the server and waits for a response. After calling this
         * method, assume that the listener calls to 'handle_incoming_message' it is done.
         */
        virtual void dispatch_and_wait_for_response(const std::string& out);

        /**
         * Returns the header of the incoming message.
         *
         * @returns the header of the incoming message.
         */
        virtual ServerHeader header();

        /**
         * Fill the parameter with the incoming message.
         *
         * @param output : variable to set with incoming message.
         */
        virtual void message(InputMessage& message);


    protected:

        /**
         * Finish the listener job thread.
         */
        virtual void finish();

        /**
         * Constructor.
         */
        DistributionClient();

        /**
         * Jobs listener.
         */
        void job_listener();

        /**
         * Adds a new incoming job to the job queue.
         *
         * @param message : message(job) to put into the queue.
         */
         void add_job(const InputMessage& message);

        /**
         * Handles the incoming message.
         * Should be called from listener of incoming messages.
         *
         * @param in : message to handle.
         */
        virtual void handle_incoming_message(const std::string& in);

    private:

        /**
         * Waits a incoming message. After calling this method, assume that the listener
         * calls to 'handle_incoming_message' it is done.
         */
        virtual void wait_for_message();

        /**
         * Start to do the new job.
         *
         * @param message : message to extract the job.
         */
        void do_job(InputMessage& message);

        /**
         * Sets the incoming message.
         *
         * @param in : message to set.
         */
        virtual void set_header_and_message(const std::string& in);

        /**
         * Attributes
         */

        /* Finish variable. */
        bool _finished;

        /** Message header. */
        ServerHeader _header;

        /** Incoming message. */
        InputMessage _message;

        /** Instance. */
        static DistributionClient*  _instance;

        /** Mutex for handle intermediate messages. */
        boost::mutex              _message_mutex;
        /** Condition variable for notice a intermediate message. */
        boost::condition_variable _message_in;
        /** Attribute to notice a intermediate message. */
        bool _message_received;
        /* Indicates that an old intermediate message is pending. */
        bool _message_pending;

        /** Mutex for jobs. */
        boost::mutex                _job_mutex;
        /** Condition variable for notice a new job. */
        boost::condition_variable   _job_in;
        /** Job queue. */
        std::queue<InputMessage>     _job_queue;
};

/**
 * Factory method for the creation of a DistributionClient instance.
 * The implementation file for the subclass of DistributionClient should implement
 * this method and create itself.
 *
 * @param address : Address to look for the server.
 * @param port : Port to look for FuD in the given address.
 */
DistributionClient* create_distribution_client(std::string address = "127.0.0.1", Port port = 31337);

}

#endif
