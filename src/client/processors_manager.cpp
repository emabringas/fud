/**
 * \file  processors_manager.cpp
 * \brief Implementation file for class ProcessorsManager.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Implementation file for FuD providing class ProcessorsManager.
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

#include <iostream>

#include "distribution_client.h"
#include "processors_manager.h"

using namespace fud;

DistributionClient* DistributionClient::_instance = NULL;

ProcessorsManager* ProcessorsManager::_instance = NULL; // initialize pointer

ProcessorsManager* ProcessorsManager::get_instance()
{
    if (_instance == NULL)  // is it the first call?
        _instance = new ProcessorsManager; // create sole instance
    return _instance; // address of sole instance
}

void ProcessorsManager::wrap_process(const std::string& message)
{
    _input.str(message);
    _output.clear();
    DistributionClient::get_instance()->inform_result(_processor->process(_input, _output));
}

// boost::thread ProcessorsManager::deliver_message(const std::string& message)
void ProcessorsManager::deliver_message(const std::string& message)
{
//     return boost::thread(boost::bind(&ProcessorsManager::wrap_process,this,message));
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

