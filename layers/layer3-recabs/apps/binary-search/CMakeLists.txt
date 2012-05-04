# $Id: CMakeLists.txt 569 2011-06-11 14:58:40Z marjobe $

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )

add_definitions( -DMILI_NAMESPACE )

set( sources_client bs_deserializer.cpp 
                    l4_client_bs.cpp)

set( sources_server l4_server_bs.cpp )

set( sources_common binary_search.cpp )

if ( MILI )
    if ( GETOPT )
        if (distribution STREQUAL "fud")
            set( main_server main_fud_server.cpp)
            set( main_client main_fud_client.cpp)

            add_executable( bs_client ${sources_client} ${sources_common} ${main_client} )
            add_executable( bs_server ${sources_server} ${sources_common} ${main_server} )

            target_link_libraries( bs_client recabs_client ${GETOPT} )
            target_link_libraries( bs_server recabs_server)
        endif ()
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif ( GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )

