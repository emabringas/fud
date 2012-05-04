/* $Id: by_size_result_sender.cpp 589 2011-07-14 18:25:31Z marjobe $ */

/**
 *  @file:      by_size_result_sender.cpp
 *  @details    Implementation file for BySizeResultSender class.
 *              System: RecAbs\n
 *              Language: C++\n
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

#include "by_size_result_sender.h"
#include <assert.h>

using namespace recabs;

BySizeResultSender::BySizeResultSender(MessageSender* next, uint maxByte):
    ChainableSender(next),
    _maxBytes(maxByte),
    _accumBytes(0)
{
}

void BySizeResultSender::send(const PacketContainer& packet_container)
{
    PacketContainer copy(packet_container);
    for (PacketContainer::iterator it = copy.begin(); it != copy.end(); it++)
        _accumBytes += (*it).size();
    _packets.splice(_packets.end(), copy);

    assert(copy.empty());

    if (_accumBytes >= _maxBytes)
        flush();
}

void BySizeResultSender::flush()
{
    _nextSender->send(_packets);

    _nextSender->flush();
    _packets.clear();
    _accumBytes = 0;
}
