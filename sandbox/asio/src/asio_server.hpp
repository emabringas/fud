/**
 * \file  asio_server.hpp
 * \brief Definition of AsioServer class.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * Contents:       Header file providing class AsioServer.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#ifndef ASIO_SERVER_HPP
#define ASIO_SERVER_HPP

#include <list>

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "common.hpp"
#include "client_proxy.hpp"

using boost::asio::ip::tcp;

/**
 * The communication part of the server. Uses the boost
 * libraries asynchronous input/output library, or <b>asio</b>.
 *
 * Check the library's <a href="www.boost.org/doc/libs/release/libs/asio/"> homepage </a>.
 */
class AsioServer
{
    public:
        /**
         * Standard constructor.
         *
         * @param port : The port to be used. Should be in the allowed range.
         */
        AsioServer(const Port port);

        void send_one(ClientID, const std::string& message);

        void send_all(const std::string& message);

        ~AsioServer(){};
    private:
        /**
         * A concrete ClientProxy using this distributing middleware.
         *
         * \sa ClientProxy
         */
        class AsioClientProxy : public ClientProxy
        {
            public:
                /**
                 * Standard constructor.
                 *
                 * @param io_service : The boost::asio::io_service object used in
                 *                     the communication.
                 */
                AsioClientProxy(boost::asio::io_service& io_service);

                virtual ~AsioClientProxy() {};

                /** The socket used for communication. */
                tcp::socket& socket();
            private:
                virtual void process(const Message& message);

                void handle_response(ResponseCode code);

                /* Asynchronous handlers*/
                void handle_send   (const boost::system::error_code& ec);
                void handle_receive(const boost::system::error_code& ec);

                void destroy();

                tcp::socket  _socket;

                char      _code_buf[RESPONSE_HEADER_LENGTH];
        };

        /* Asynchronous handler, calls itself recursively */
        void handle_accept (const boost::system::error_code& ec,AsioClientProxy* client);

        void register_client(ClientProxy* client);

        /* To register clients */
        static void run_acceptor_thread(AsioServer* obj);

        void run_and_die();

        void _async_accept();

        /* attr.*/
        boost::asio::io_service  _io_service;
        tcp::acceptor            _acceptor;
        std::list<ClientProxy*>  _client_proxies;
};

#endif
