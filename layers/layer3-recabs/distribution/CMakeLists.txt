# $Id: CMakeLists.txt 346 2010-10-31 23:59:35Z emab73 $

if ( NOT distribution STREQUAL "fud" AND NOT distribution STREQUAL "prototype")
    message ( FATAL_ERROR "Couldn't locate a ${distribution} implementation.")
else ()
    message ( STATUS "Using ${distribution} distribution implementation")
endif ()

add_subdirectory( ${distribution} )

set ( distribution_client   ${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${client_file}
                            ${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${client_comm}                          
                        PARENT_SCOPE)

set ( distribution_server "${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${server_file}" PARENT_SCOPE)

