/**
 * \file  client_proxy.h
 * \brief Definition of ClientProxy class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file providing class DistributableJob.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#include "common.hpp"

#ifndef CLIENT_PROXY_HPP
#define CLIENT_PROXY_HPP

enum ClientType
{
    Single,
    Server
};

/**
 * Server side proxy representing a connected client.
 */
class ClientProxy
{
    public:
        /** The method in charge of sending the JobUnit to the client. */
        virtual void process(const Message& message) = 0;

        /**
            * Get the ClientID of the current proxy.
            *
            * @returns The ID of the connected client.
            *
            * \sa ClientID
            */
        inline  ClientID get_id() const {return _id;}

        virtual ~ClientProxy();
    protected:
        /**
         * Default constructor, will increment the ids of ClientProxies while
         * assigning.
         */
        ClientProxy(ClientType type = Single);

    private:
        static ClientID    _last_id;
        ClientID           _id;
        ClientType         _type;
};

#endif