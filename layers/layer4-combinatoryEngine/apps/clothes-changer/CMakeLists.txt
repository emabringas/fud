# $Id: CMakeLists.txt 372 2011-01-12 16:58:16Z diazdiego86 $

set( sources_client clothes_application_client_imp.cpp )

set( sources_server clothes_application_server_imp.cpp )

set( sources_common clothes_node.cpp
                    tables.cpp
   )

set( main_client main_client.cpp)
set( main_server main_server.cpp)

add_executable( main_clothes_client ${sources_client} ${sources_common} ${main_client} )
add_executable( main_clothes_server ${sources_server} ${sources_common} ${main_server} )

find_library ( LIB_RECABS
    NAMES
        recabs_client recabs_server

        /usr/local/lib
             )
if ( LIB_RECABS )
    set ( RECABS_CLIENT recabs_client )
    set ( RECABS_SERVER recabs_server )
else ( LIB_RECABS )
    message ( FATAL_ERROR "Install RecAbs: fud.googlecode.com" )
endif ( LIB_RECABS )


find_library ( LIB_GETOPT 
               getopt_pp
               /usr/lib
               REQUIRED
             )
if ( LIB_GETOPT )
    set ( GETOPT_LIBRARY getopt_pp )
else ( LIB_GETOPT )
    message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
endif ( LIB_GETOPT )


target_link_libraries( main_clothes_client ${RECABS_CLIENT} ${GETOPT_LIBRARY})
target_link_libraries( main_clothes_server ${RECABS_SERVER} )
