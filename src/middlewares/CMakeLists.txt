# $Id: CMakeLists.txt 242 2010-08-13 16:31:21Z billybiset $

if ( NOT DEFINED middleware )
    set ( middleware "asio" ) # Default
    message ( STATUS "Using default middleware: asio")
endif ()

add_subdirectory( ${middleware} )

set ( middleware_server "${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${server_file}" PARENT_SCOPE)

set ( middleware_client "${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${client_file}" PARENT_SCOPE)