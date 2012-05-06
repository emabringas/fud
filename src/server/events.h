/**
 * \file  events.h
 * \brief Definition of Event class.
 *
 * FuD: FuDePAN Ubiqutous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Header file for FuD providing class Event and derivatives.
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

#ifndef EVENTS_H
#define EVENTS_H

#include "common.h"

namespace fud
{
    class DistributableJob;

    /**
     * A generic event for an interface.
     * @param Interface : The interface of the object that will handle these events.
     */
    template <class Interface>
    struct Event
    {
        /**
         * Calls the registered method.
         * @param i : Pointer to the object handling the events.
         */
        virtual void call(Interface* i) = 0;
    };

    /**
     * A generic event with 0 parameters for an interface.
     * @param Interface : The interface of the object that will handle these events.
     */
    template <class Interface>
    class Event0Param : public Event<Interface>
    {
        void (Interface::*method)();

        virtual void call(Interface* i)
        {
            (i->*method)();
        }
    public:
        Event0Param(void (Interface::*m)()) : method(m) {}
    };

    /**
     * A generic event with 1 parameter for an interface.
     * @param Interface : The interface of the object that will handle these events.
     * @param Param : The type of the only parameter of the event.
     */
    template <class Interface, class Param>
    class Event1Param : public Event<Interface>
    {
        void (Interface::*method)(Param p);
        Param const p;

        virtual void call(Interface* i)
        {
            (i->*method)(p);
        }
    public:
        Event1Param(void (Interface::*m)(Param), Param p) : method(m), p(p) {}
    };

    /**
     * A generic event with 2 parameters for an interface.
     * @param Interface : The interface of the object that will handle these events.
     * @param Param1 : The type of the first parameter of the event.
     * @param Param2 : The type of the second parameter of the event.
     */
    template <class Interface, class Param1, class Param2>
    class Event2Param : public Event<Interface>
    {
        void (Interface::*method)(Param1 p1, Param2 p2);
        Param1 const p1;
        Param2 const p2;

        virtual void call(Interface* i)
        {
            (i->*method)(p1, p2);
        }
    public:
        Event2Param(void (Interface::*m)(Param1, Param2), Param1 p1, Param2 p2) : method(m), p1(p1), p2(p2) {}
    };

    /** Simple method to construct events without parameters. */
    template <class Interface>
    inline Event<Interface>* new_event(void (Interface::*method)())
    {
        return new Event0Param<Interface>(method);
    }

    /** Simple method to construct events with one parameter. */
    template <class Interface, class Param>
    inline Event<Interface>* new_event(void (Interface::*method)(Param), Param p)
    {
        return new Event1Param<Interface, Param>(method, p);
    }

    /** Simple method to construct events with two parameters. */
    template <class Interface, class Param1, class Param2>
    inline Event<Interface>* new_event(void (Interface::*method)(Param1, Param2), Param1 p1, Param2 p2)
    {
        return new Event2Param<Interface, Param1, Param2>(method, p1, p2);
    }
}

#endif

