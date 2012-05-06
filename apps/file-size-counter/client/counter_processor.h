/*
 * Copyright (C) 2010 Guillermo Biset, FuDePAN
 *
 * File:           counter_processor.h
 * System:         FuD
 *
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
