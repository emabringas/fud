/* $Id: fud_rmanager.cpp 589 2011-07-14 18:25:31Z marjobe $ */

/** 
 *  @file:      fud_rmanager.cpp
 *  @details    Implementation file for FuDRManager class.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       March 2011
 *  @version    0.1
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * process without data dependency for the framework FuD.
 * See <http://fud.googlecode.com/>.
 *
 * Copyright (C) 2010, 2011 - Mariano Bessone & Emanuel Bringas, FuDePAN
 *
 * This file is part of RecAbs project.
 *
 * RecAbs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "fud_rmanager.h"

using namespace recabs;

FuDRManager::FuDRManager(L4ServerApp& app) :
    RecursionManager(app),
    DistributableJobImplementation()
{
}

FuDRManager::~FuDRManager()
{
    fud::finish();
}

void FuDRManager::start()
{
    /* Get the initial packet. */
    Packet initial_packet;
    _server_app.get_initial_packet(initial_packet);

    /*Pusg initial packet in the stack*/
    push_child(initial_packet);
  
    /* Run the unique DistributableJob*/
    this->run();
    this->wait_completion();    
}

void FuDRManager::handle_results(fud::JobUnitID, fud::InputMessage& input)
{
    handle_receive_packet((InputMessage&) input);
}

void FuDRManager::handle_finalization(fud::JobUnitID)
{
    handle_end_of_job();
}

fud::JobUnit* FuDRManager::produce_next_job_unit(fud::JobUnitSize)
{
    if ( get_status() == fud::ReadyToProduce)
    {
        fud::StreamingJobUnit* res = new fud::StreamingJobUnit();

        Packet top;
        pop_child(top);

        (*res) << top;

        res->set_size(1);

        return res;
    }
    else
        return NULL;
}

fud::DistributableJobStatus FuDRManager::get_status() const
{
    if (RecursionManager::finished())
        return fud::FinishedGenerating;
    else
    {
        if(empty_stack())
            return fud::WaitingMoreData;
        else
            return fud::ReadyToProduce;
    }
}

const char* FuDRManager::get_name() const
{
    return "RecAbs";
}

namespace recabs
{
    RecursionManager* create_recursion_manager(L4ServerApp& srv_app)
    {
        return new FuDRManager(srv_app);
    }
}
