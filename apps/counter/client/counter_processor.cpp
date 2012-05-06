/*
 * Parallel Clusterer: A distributed protein backbone clusterer.
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 * 
 * This file is part of the Parallel Clusterer Project.
 * 
 * File:           clusterer_client.cpp
 * Contents:       Implementation file for Parallel Cluster providing class
 *                 CounterProcessor. This type of client is designed to solve
 *                 job units from each of the three concrete distributable
 *                 jobs of the clusterer. There is also an implementation
 *                 of the create_client method, which will later be linked at
 *                 compile time.
 * 
 * System:         Parallel Clusterer
 * Language:       C++
 * 
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 * 
 *
 * @Last Update:
 *     $Id: 
 *     $URL: 
 *     $LastChangedBy: 
 * 
 * 
 * Parallel Clusterer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Parallel Clusterer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Parallel Clusterer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "counter_processor.h"


CounterProcessor::CounterProcessor() :
    ClientProcessor()
{
}

bool CounterProcessor::process(fud::InputMessage& input, fud::OutputMessage& output)
{
    fud::fud_uint n;
    input  >> n;
    std::cout<<"valor de n es: "<<n<<std::endl;
    output << fud::fud_uint(n + 1);
    
//     sleep(1);
    return true;
}


