#include "client_proxy.hpp"

ClientID ClientProxy::_last_id = 0;

ClientProxy::ClientProxy(ClientType type) :
    _id(++_last_id),
    _type(type)
{
}

ClientProxy::~ClientProxy()
{
}
