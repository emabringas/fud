/**
 * \file  processors_manager.cpp
 * \brief Implementation file for class ProcessorsManager.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class ProcessorsManager.
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

#include <iostream>
#include "fud/client/distribution_client.h"
#include "fud/client/processors_manager.h"
#include "fud/client/sender.h"

namespace fud
{
    
void finish_client()
{
    ProcessorsManager::destroy();
}

DistributionClient* DistributionClient::_instance = NULL;

ProcessorsManager* ProcessorsManager::_instance = NULL; // initialize pointer

ProcessorsManager* ProcessorsManager::get_instance () 
{
    if (_instance == NULL)  // is it the first call?
        _instance = new ProcessorsManager; // create sole instance

    return _instance; // address of sole instance
}

void ProcessorsManager::destroy()
{
    delete _instance;
    _instance = NULL;
}

ProcessorsManager::~ProcessorsManager() 
{

}

void ProcessorsManager::wrap_process(const std::string& message)
{
    _input.str(message);
    _output.clear();

    inform_result(_processor->process(_input,_output));
}

// boost::thread ProcessorsManager::deliver_message(const std::string& message)
void ProcessorsManager::deliver_message(const std::string& message)
{
//     return boost::thread(boost::bind(&ProcessorsManager::wrap_process,this,message));
    _message_number = 0;
    wrap_process(message);
}

ProcessorsManager::ProcessorsManager() :
    _processor()
{
}

void ProcessorsManager::register_processor(ClientProcessor* client_processor)
{
    _processor = client_processor;
}

const std::string ProcessorsManager::get_return_message() const
{
    return _output.str();
}

void ProcessorsManager::inform_result(bool result)
{
    if (result)
    {
        /* First, it sends the result. */
        if (!_output.str().empty())
        {
            Sender s;
            s.send(_output);            
        }
        /* Then, it sends the finalization signal. */
        OutputMessage bos;
        const fud_size size_of_message = HEADER_SIZE + CLIENT_HEADER_LENGTH;
        bos << size_of_message << kJobUnitCompleted;
        DistributionClient::get_instance()->dispatch(bos.str());
    }
    else // will be done differently
        std::cerr << "ERROR obtaining results " << std::endl;
}

}