# $Id: CMakeLists.txt 455 2011-03-19 14:39:19Z marjobe $

if ( NOT distribution STREQUAL "fud" )
    message ( FATAL_ERROR "Couldn't locate a ${distribution} implementation.")
else ()
    message ( STATUS "Using ${distribution} distribution implementation")
endif ()

add_subdirectory( ${distribution} )

set ( distribution_client   "${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${client_processor}"
                            "${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${client_result_sender}"
                            PARENT_SCOPE )
set ( distribution_client_library ${distribution_client_library} PARENT_SCOPE)

set ( distribution_server "${CMAKE_CURRENT_SOURCE_DIR}/${distribution}/${server_manager}" PARENT_SCOPE )
set ( distribution_library ${distribution_library} PARENT_SCOPE)
