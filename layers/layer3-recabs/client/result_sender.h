/* $$ */

/** 
 *  @file:      result_sender.h
 *  @details    Header file for Senders classes.\n
 *              System: RecAbs\n
 *              Language: C++\n
 *  
 *  @author     Mariano Bessone
 *  @email      marjobe AT gmail.com
 *
 *  @author     Emanuel Bringas
 *  @email      emab73 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * This file is part of RecAbs
 *
 * RecAbs: Recursive Abstraction, an abstraction layer to any recursive
 * processes without data dependency for framework FuD.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Mariano Bessone and Emanuel Bringas
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

#ifndef RESULT_SENDER_H
#define RESULT_SENDER_H

#include "communication.h"

namespace recabs
{
    struct ResultSender : public Communication
    {
        /**
         *  Reimplementation of method send.
         */
	    virtual void send(const Packet& packet) = 0;

        /**
         *  Added flush method for packet accumulated.
         */
	    virtual void flush() = 0;
        
    };

    class ChainableSender: public ResultSender
    {
        public: 

            /**
             *  Constructor
             */
        	ChainableSender(ResultSender* next): _nextSender(next) {};

            /**
             *  Reimplementation of method send.
             */
	        virtual void send(const Packet& packet) = 0;

            /**
             *  Added flush method for packet accumulated.
             */
	        virtual void flush() = 0;

        protected:
            
            /**
             *  Atribute
             */
        	ResultSender* const _nextSender;
    };

    class RealResultSender : public ResultSender
    {
        public: 

            RealResultSender (RecursionManager& rm);

            /**
             *  Reimplementation of method send.
             */
	        virtual void send(const Packet& packet);

            /**
             *  Added flush method for packet accumulated.
             */
	        virtual void flush(){};
    
   
        private:

            /**
             *  Atribute
             */
            Communication* _comm;

    };

}

#endif

