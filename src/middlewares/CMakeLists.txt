# $Id: CMakeLists.txt 400 2011-01-25 00:19:10Z marjobe $

if ( NOT DEFINED middleware )
    set ( middleware "ana" ) # Default
    message ( STATUS "Using default middleware: ${middleware}")
endif ()

add_subdirectory( ${middleware} )

set ( middleware_server "${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${server_file}" PARENT_SCOPE)

set ( middleware_client "${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${client_file}" PARENT_SCOPE)

# This var is used to include the header files of the middleware to target
set ( MIDDLEWARE_HEADERS ${MIDDLEWARE_HEADERS} PARENT_SCOPE)

# This var is used to link the middleware's libs with fud
set ( MIDDLEWARE_LIBS ${MIDDLEWARE_LIBS} PARENT_SCOPE )
