# $Id: CMakeLists.txt 399 2011-01-24 23:50:04Z marjobe $

include_directories ( server client )

set ( server_file "server/ana_clients_manager.cpp" PARENT_SCOPE)

set ( client_file "client/ana_distribution.cpp" PARENT_SCOPE)

find_library ( ANA_LIB ana )

if ( ANA_LIB )
    message ( STATUS "Using ANA: ${ANA_LIB}" )
    set ( MIDDLEWARE_LIBS ${ANA_LIB} PARENT_SCOPE )
else ( ANA_LIB )
    message ( FATAL_ERROR "You must install Ana (library): ana-net.googlecode.com" )
endif ( ANA_LIB )
