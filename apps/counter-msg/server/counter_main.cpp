/*
  Parallel Clusterer: A distributed protein backbone clusterer.
    Copyright (C) 2009 Guillermo Biset, FuDePAN
    
    This file is part of the Parallel Clusterer Project.

    File:           clusterer_threads.cpp
    Contents:       Main application.

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

#include "counter.h"
#include "getopt_pp.h"

using namespace fud;
using namespace GetOpt;

int main(int argc, char** argv)
{
    size_t number(1000);
    size_t jobs_n(5);

    GetOpt_pp ops(argc, argv);
    ops >> Option('n', "number", number) >> Option('j',"jobs",jobs_n);

    NumberDatabase* db = new NumberDatabase(number);

    std::vector<Counter*> jobs;

    for (size_t i(0); i < jobs_n; ++i)
        jobs.push_back( new Counter(*db,i) );

    for (size_t i(0); i < jobs_n; ++i)
        jobs[i]->run();

    jobs[jobs_n-1]->wait_completion();

    std::cout << "Last number is: " << db->current_number() << std::endl;

    return 0;
}
