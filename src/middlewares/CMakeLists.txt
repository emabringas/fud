# $Id: CMakeLists.txt 615 2011-08-05 16:13:18Z lbesso $

add_subdirectory( ${middleware} )

set ( middleware_server ${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${server_file} PARENT_SCOPE)

set ( middleware_client ${CMAKE_CURRENT_SOURCE_DIR}/${middleware}/${client_file} PARENT_SCOPE)

# This var is used to include the header files of the middleware to target
set ( MIDDLEWARE_HEADERS ${MIDDLEWARE_HEADERS} PARENT_SCOPE)

# This var is used to link the middleware's libs with fud 
set ( MIDDLEWARE_SERVER_LIBS ${MIDDLEWARE_SERVER_LIBS} PARENT_SCOPE )
set ( MIDDLEWARE_CLIENT_LIBS ${MIDDLEWARE_CLIENT_LIBS} PARENT_SCOPE )

