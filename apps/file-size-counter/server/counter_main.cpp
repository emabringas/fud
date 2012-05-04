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

#include <syslog.h>
#include <sys/time.h>

#include "counter.h"
#include "getopt_pp.h"

using namespace fud;
using namespace GetOpt;

int main(int argc, char** argv)
{
    timeval tm;
    gettimeofday(&tm, NULL);

    size_t port(31337);

    GetOpt_pp ops(argc, argv);
    ops >> Option('p', "port", port);

    size_t const AMOUNT(10);

    Counter * jobs[AMOUNT];
    for (size_t i=0; i < AMOUNT; ++i)
        jobs[i] = new Counter("server/data/file2.txt");

    for (size_t i=0; i < AMOUNT; ++i)
        jobs[i]->run();

    for (size_t i=0; i < AMOUNT; ++i)
        jobs[i]->wait_completion();

    for (size_t i=0; i < AMOUNT; ++i)
        jobs[i]->output_results();
}
