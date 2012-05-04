# $Id: CMakeLists.txt 356 2010-11-04 13:38:16Z emab73 $

find_file ( MILI mili/mili.h )

add_definitions( -DMILI_NAMESPACE )

set( sources_client bs_deserializer.cpp 
                    l4_client_bs.cpp)

set( sources_server l4_server_bs.cpp )

set( sources_common binary_search.cpp )

if ( MILI )
    if (distribution STREQUAL "fud")
        set( main_server main_fud_server.cpp)
        set( main_client main_fud_client.cpp)

        add_executable( bs_client ${sources_client} ${sources_common} ${main_client} )
        add_executable( bs_server ${sources_server} ${sources_common} ${main_server} )

        target_link_libraries( bs_client recabs_client)
        target_link_libraries( bs_server recabs_server)

    else (distribution STREQUAL "prototype")

        set( main main_prototype.cpp)

        add_executable( bs_prototype ${sources_server} ${sources_client} ${sources_common} ${main} )
    
        target_link_libraries( bs_prototype recabs_server recabs_client )

    endif ()

else ( MILI )

    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )

endif ( MILI )

