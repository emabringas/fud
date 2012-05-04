/*
  Parallel Clusterer: A distributed protein backbone clusterer.
    Copyright (C) 2009 Guillermo Biset, FuDePAN
    
    This file is part of the Parallel Clusterer Project.

    File:           representatives_processor.h
    Contents:       Header file for Parallel Cluster providing class RepresentativesProcessor.
                    This type of client is designed to solve job units from the RepresentativesJob
                    from L3 in the server side.

    System:         Parallel Clusterer
    Language:       C++
  
    Author:         Guillermo Biset
    E-Mail:         billybiset AT gmail.com
  
    Parallel Clusterer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Parallel Clusterer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Parallel Clusterer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COUNTER_PROCESSOR_H
#define COUNTER_PROCESSOR_H

#include "fud/fud_client.h"

namespace fud
{
    class CounterProcessor : ClientProcessor
    {
        public:
            CounterProcessor();

            virtual bool process(InputMessage& input, OutputMessage& output);
    };
}

#endif
