/**
 * \file  synchronized_containers.h
 * \brief Definition of Event class.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing classes for containers
 *                 with thread safe methods.
 *
 * System:         FuD
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

#ifndef SYNCHRONIZED_CONTAINERS_H
#define SYNCHRONIZED_CONTAINERS_H

#include <queue>
#include <boost/thread.hpp>
#include <pthread.h>

#include "mili/mili.h"
#include "mili/prepos_mutex.h"

/**
 * A thread safe Queue.
 * Uses a PrePosCaller locking and unlocking the same mutex.
 */
template < class T, class Container = std::queue<T> >
class SynchronizedQueue
{
public:
    typedef mili::PrePosCaller<Container* const, PreMutex, PosMutex> SynchQueuePPC;
private:
    pthread_mutex_t mutex;
    Container       queue;
    PreMutex        premutex;
    PosMutex        posmutex;
    SynchQueuePPC   synchQueuePPC;
public:
    SynchronizedQueue() :
        queue(),
        premutex(&mutex),
        posmutex(&mutex),
        synchQueuePPC(&queue, premutex, posmutex)
    {
        pthread_mutex_init(&mutex, NULL);
    }

    SynchQueuePPC& operator -> ()
    {
        return synchQueuePPC;
    }

};


/**
 * A thread safe List.
 * Uses a PrePosCaller locking and unlocking the same mutex.
 */
template < class T, class Container = std::list<T> >
class SynchronizedList
{
public:
    typedef mili::PrePosCaller<Container* const, PreMutex, PosMutex> SynchListPPC;
private:
    pthread_mutex_t mutex;
    Container       cont;
    PreMutex  premutex;
    PosMutex  posmutex;
    SynchListPPC    synchListPPC;
public:
    SynchronizedList() :
        cont(),
        premutex(&mutex),
        posmutex(&mutex),
        synchListPPC(&cont, premutex, posmutex)
    {
        pthread_mutex_init(&mutex, NULL);
    }

    SynchListPPC& operator -> ()
    {
        return synchListPPC;
    }
};

/**
 * A thread safe queue that locks itself when you try to pop while empty.
 * Implemented via condition variables.
 */
template < typename T, class Container = std::queue<T> >
class LockingQueue
{
public:
    /** Standard constructor. */
    LockingQueue() :
        _mutex(),
        _condition(),
        _queue()
    {
    }

    /** Copy constructor.*/
    LockingQueue(const LockingQueue<T>& other) :
        _mutex(),
        _condition(),
        _queue(other)
    {
    }

    /**
     * The same as a push on a queue, but thread safe and will also
     * notify all blocked threads waiting for an element.
     */
    void push(const T& x)
    {
        {
            boost::lock_guard<boost::mutex> lock(_mutex);
            _queue->push(x);
        }
        _condition.notify_all();
    }

    /**
     * The same as a pop() on a standard queue, it is thread safe and
     * will block the caller if the queue is empty. When the condition
     * is flagged, it will compete to obtain the lock.
     */
    T wait_for_element()
    {
        boost::unique_lock<boost::mutex> lock(_mutex);

        while (_queue->empty())
            _condition.wait(lock);

        T ret = _queue->front();
        _queue->pop();

        return ret;
    }

private:
    boost::mutex                   _mutex;
    boost::condition_variable      _condition;
    SynchronizedQueue<T, Container> _queue;
};


#endif

