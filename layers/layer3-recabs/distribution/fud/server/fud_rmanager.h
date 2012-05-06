/* $Id: fud_rmanager.h 589 2011-07-14 18:25:31Z marjobe $ */

/** 
 *  @file:      fud_rmanager.h
 *  @details    Header file for FuDRManager class.\n
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

#ifndef FUD_MANAGER_H
#define FUD_MANAGER_H

#include <fud/fud.h>
#include "l4_server_app.h"
#include "recursion_manager.h"

namespace recabs
{

/**
 * Concrete class that represents a FuD manager of recursion.
 */
class FuDRManager :  public RecursionManager,
                     public fud::DistributableJobImplementation
{
    public:

        /**
         * Constructor.
         *
         * @param app : the concrete L4ServerApp that handles the results.
         */
        FuDRManager(L4ServerApp& app);
        
        /**
         * Destructor.
         */
        virtual ~FuDRManager();

        /**
         * Starts the recursion.
         * RecursionManager method to implement.
         */
        virtual void start();

    private:

        /* DistributableJobImplementation methods to implement */
        void handle_results(fud::JobUnitID, fud::InputMessage& input);
        void handle_finalization(fud::JobUnitID);
        fud::JobUnit* produce_next_job_unit(fud::JobUnitSize);
        fud::DistributableJobStatus get_status() const;
        const char* get_name() const;
};

}

#endif

