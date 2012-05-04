# $Id: CMakeLists.txt 351 2010-11-03 02:57:16Z emab73 $

cmake_minimum_required( VERSION 2.6 )

project( recabs CXX )

add_definitions ( -Wall -Wextra -pedantic -ansi )

option( weff "Compile with warnings violations of the Effective C++ book." OFF )
if ( weff )
    message ( STATUS "Compiling with warnings violations of the Effective C++ book." )
    add_definitions (-Weffc++)
endif ( weff )

find_file ( MILI mili/mili.h )
add_definitions( -DMILI_NAMESPACE )

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message ( STATUS "Compiling with debbug support." )
    add_definitions( -ggdb3 )
endif (CMAKE_BUILD_TYPE MATCHES Debug)

include_directories( . common client server distribution/prototype/client distribution/prototype/server)

option( dist "Compile with distribution." prototype )
set ( distribution ${dist} )

add_subdirectory( distribution )

set ( client_srcs   client/distributable_recursive_processor.cpp 
                    client/result_sender.cpp
                    client/by_size_result_sender.cpp)
set ( server_srcs   server/recursion_manager.cpp )

add_library( recabs_client SHARED ${client_srcs} ${distribution_client} )
add_library( recabs_server SHARED ${server_srcs} ${distribution_server} )

option( apps "Compile sample applications too." OFF )

if ( apps )
    message ( STATUS "Compiling sample applications as well." )
    add_subdirectory( apps/binary-search )
endif ( apps )

set ( CMAKE_INSTALL_PREFIX /usr/local )

install ( TARGETS recabs_client LIBRARY DESTINATION lib )
install ( TARGETS recabs_server LIBRARY DESTINATION lib )

set ( recabs_header recabs.h )

set ( recabs_private_headers    common/common.h
                                common/serializable_recursive_functor.h
                                common/recursive_functor.h
                                client/deserializer_functor.h
                                client/distributable_recursive_processor.h
                                client/recursive_processor.h
                                server/recursion_manager.h
                                server/l4_server_app.h
                                distribution/prototype/client/prototype_rp.h
                                distribution/prototype/server/prototype_rm.h
    )

install ( FILES  ${recabs_header}           DESTINATION include/recabs )
install ( FILES  ${recabs_private_headers}  DESTINATION include/recabs/.private )


