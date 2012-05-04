/* $Id: by_size_result_sender.cpp 354 2010-11-03 22:22:34Z emab73 $ */

/**
 *  @file:      BySizeResultSender.cpp
 *  @details    Implementation file for BySizeResultSender class.
 *              System:     RecAbs              \n
 *              Language:   C++                 \n
 *
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       October 2010
 *  @version    0.1
 *
 * BySizeResultSender.cpp
 * This file is part of RecAbs
 *
 * Copyright (C) 2010 - Emanuel Bringas and Mariano Bessone
 *
 * RecAbs is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * RecAbs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RecAbs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#include "by_size_result_sender.h"

using namespace recabs;

BySizeResultSender::BySizeResultSender(ResultSender* next, uint maxByte):
    ChainableSender(next),
    _maxBytes(maxByte)
{
}

void BySizeResultSender::send(const Packet& packet)
{
    _packets.push_back(packet);
    _accumBytes += packet.size();
    if (_accumBytes >= _maxBytes)
        flush();
}

void BySizeResultSender::flush()
{
    std::list<Packet>::iterator it;
    for (it = _packets.begin(); it != _packets.end(); it++)
        _nextSender->send(*it);

    _nextSender->flush();
    _packets.clear();
    _accumBytes = 0;
}
