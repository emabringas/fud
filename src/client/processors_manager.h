/**
 * \file  processors_manager.h
 * \brief Definition of class ProcessorsManager.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class ProcessorsManager.
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

#ifndef PROCESSORS_MANAGER_H
#define PROCESSORS_MANAGER_H

#include <string>

#include "common.h"
#include "client_processor.h"

namespace fud
{
    /**
     * A client counterpart to the JobManager, it will handle instances of ClientProcessor.
     * Since there is only one ClientProcessor per client, then it only manages an instance.
     * Implements a Singleton pattern.
     *
     * \sa ClientProcessor
     */
    class ProcessorsManager
    {
    public:
        /** Singleton method. */
        static ProcessorsManager* get_instance();

        /**
         * Deliver the incoming message to the ClientProcessor.
         *
         * @param message : The message to be processed, it is set directly as the InputMessage.
         *
         * \sa InputMessage
         */
        void   deliver_message(const std::string& message);

        /**
         * Register a ClientProcessor. Invoked from the constructor of a concrete
         * ClientProcessor instance.
         *
         * @param client_processor : The memory address of the processing client.
         */
        void   register_processor(ClientProcessor* client_processor);

        /**
         * Wraps the call to the ClientProcessor setting up the input and output
         * messages.
         *
         * @param message : The message to be processed, set directly as the InputMessage.
         */
        void   wrap_process(const std::string& message);

        /**
         * Obtains the message with the results. It will only be called if the process
         * method returned true. Also, it will access the string of the OutputMessage.
         *
         * @returns : The string containing the return message.
         *
         * \sa OutputMessage
         * \sa ClientProcessor
         */
        const  std::string get_return_message() const;

        virtual ~ProcessorsManager() {}
    private:
        /*methods*/
        ProcessorsManager();
        ProcessorsManager(const ProcessorsManager& other);
        ProcessorsManager& operator=(const ProcessorsManager& other);

        /*attributes*/
        static ProcessorsManager* _instance;  /* Singleton.*/
        ClientProcessor*          _processor; /* The only registered processor. */

        InputMessage              _input;   /* Used for efficiency. */
        OutputMessage             _output;  /* Idem. */
    };
}

#endif

