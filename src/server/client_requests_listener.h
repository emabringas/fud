#ifndef CLIENT_REQUESTS_H
#define CLIENT_REQUESTS_H


namespace fud
{
    
    struct ClientRequestsListener
    {
       /**
         * Reserves all free clients requested by client_id and then informs to client_id the 
         * total Clients that the server is abble to give him.
         *
         * @param[in] client_id the client id that require free clients
         * @param[in] clients_requested the number of clients that a client request.
         *
         */
        virtual void reserve_free_clients(ClientID client_id, fud_uint clients_requested) = 0;

    };
    
#endif
}
