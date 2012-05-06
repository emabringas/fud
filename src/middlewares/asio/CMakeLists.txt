# $Id: CMakeLists.txt 272 2010-08-29 19:12:40Z lbesso $

include_directories ( server client )

set ( server_file server/async_io_clients_manager.cpp PARENT_SCOPE)

set ( client_file client/async_io_distribution.cpp PARENT_SCOPE)
