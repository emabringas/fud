/*
  Parallel Clusterer: A distributed protein backbone clusterer.
    Copyright (C) 2009, 2010, 2011 - Guillermo Biset & Mariano Bessone & Emanuel Bringas, FuDePAN
    
    This file is part of the Parallel Clusterer Project.

    File:           clusterer_client.cpp
    Contents:       Implementation file for Parallel Cluster providing class 
                    CounterProcessor. This type of client is designed to solve
                    job units from each of the three concrete distributable 
                    jobs of the clusterer. There is also an implementation
                    of the create_client method, which will later be linked at
                    compile time.

    System:         Parallel Clusterer
    Language:       C++
  
    Author:     Guillermo Biset
    E-mail:     billybiset AT gmail.com
     
    Author:     Mariano Bessone
    E-mail:     marjobe AT gmail.com

    Author:     Emanuel Bringas
    E-mail:     emab73 AT gmail.com
  
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

#include "counter_processor.h"

using namespace fud;

CounterProcessor::CounterProcessor() :
    ClientProcessor()
{
}

bool CounterProcessor::process(InputMessage& input, OutputMessage& output)
{
    Sender s;
    OutputMessage msg;
    msg << 17 << "Empece a laburar";
    for (unsigned int i = 0; i < 10; i++)
        s.send(msg);

    InteractiveHelper h;
    h.ask_for_free_clients(5);
//    std::cout << h.ask_for_free_clients(5) << std::endl;

    fud_uint n;
    input  >> n;
    output << 79 << fud_uint(n + 1);
    
//     sleep(1);
    return true;
}
