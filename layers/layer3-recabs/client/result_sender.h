/* $Id: result_sender.h 589 2011-07-14 18:25:31Z marjobe $ */

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

#ifndef RESULT_SENDER_H
#define RESULT_SENDER_H

#include "common.h"

namespace recabs
{

/**
 * RealSender interface.
 * Should be implemented by another interface which know send, in the layer below.
 */
struct RealSender
{
    /**
     * Destructor
     */
    virtual ~RealSender(){};
    
    /**
     * Sends a message to the server
     * Should be implemented by the layer below.
     *
     * @param out : message to send.
     */
    virtual void send(const OutputMessage& out) = 0;
};

/**
 *  RealSender Factory Method.
 */
RealSender* create_real_sender();

struct MessageSender
{
    /**
     * Destructor.
     */
    virtual ~MessageSender(){};

    /**
     *  Reimplementation of method send.
     */
    virtual void send(const PacketContainer& packet_container) = 0;

    /**
     *  Added flush method for packet accumulated.
     */
    virtual void flush() = 0;

};

class FinalSender : public MessageSender
{
    public:

        /**
         * Destructor.
         */
        virtual ~FinalSender(){};

        /**
         *  Reimplementation of method send.
         */
        virtual void send(const PacketContainer& packet_container) = 0;

        /**
         *  Added flush method for packet accumulated.
         */
        virtual void flush() = 0;

    protected:

        /**
         * Constructor.
         */
        FinalSender(RecabsPacketHeader header):
            _header(header)
        {};

        /* Header attribute */
        const RecabsPacketHeader _header;

};

class ChainableSender: public MessageSender
{
    public: 

        /**
         *  Destructor
         */
    	virtual ~ChainableSender();

        /**
         *  Reimplementation of method send.
         */
        virtual void send(const PacketContainer& packet_container) = 0;

        /**
         *  Added flush method for packet accumulated.
         */
        virtual void flush() = 0;

    protected:

        /**
         *  Constructor
         */
    	ChainableSender(MessageSender* next):
            _nextSender(next)
        {};
        
        /**
         *  Atribute
         */
    	MessageSender* const _nextSender;
};

class InmediatelySender : public FinalSender
{
    public: 

        /**
         * Constructor.
         */
        InmediatelySender(RecabsPacketHeader header):
            FinalSender(header),
            _real_sender( create_real_sender() )
        {};
        
        /**
         * Destructor.
         */
        virtual ~InmediatelySender();

        /**
         * Reimplementation of method send.
         * Should be implemented by the layer below.
         */
        virtual void send(const PacketContainer& packet_container)
        {
            OutputMessage out;
            out << _header << packet_container;
            _real_sender->send(out);
        };

        /**
         *  Added flush method for packet accumulated.
         */
        virtual void flush(){};

    protected:

        /* Real sender attribute. */
        RealSender* const _real_sender;

};

}

#endif

