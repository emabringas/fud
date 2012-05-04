# $Id: CMakeLists.txt 242 2010-08-13 16:31:21Z billybiset $

include_directories ( server client )

set ( server_file "server/async_io_clients_manager.cpp" PARENT_SCOPE)

set ( client_file "client/async_io_distribution.cpp" PARENT_SCOPE)
