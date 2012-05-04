# $Id: CMakeLists.txt 372 2011-01-12 16:58:16Z diazdiego86 $

set( sources_client rnaffe_application_client.cpp )

set( sources_server rnaffe_application_server.cpp )

set( sources_common rnaffe_node.cpp )

set( sources_prune rnaffe_prune_policy.h)

set( main_client main_client.cpp)
set( main_server main_server.cpp)


add_executable( rna_folding_free_energy_client ${sources_prune} ${sources_client} ${sources_common} ${main_client} )
add_executable( rna_folding_free_energy_server ${sources_prune} ${sources_server} ${sources_common} ${main_server} )

# finding out GETOPT
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

# finding out RECABS
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

# finding out ANTIVIRALS
find_library ( LIB_ANTIVIRALS antivirals /usr/local/lib )
if ( LIB_ANTIVIRALS )
    set ( ANTIVIRALS_LIBRARY antivirals )
else ( LIB_ANTIVIRALS )
    message ( FATAL_ERROR "Install Lib Antivirals: fud.googlecode.com" )
endif ( LIB_ANTIVIRALS )

#finding out RNAFOLDING
find_library ( LIB_RNAFOLDING rnafolding /usr/local/lib )
if ( LIB_RNAFOLDING )
    set (RNAFOLDING_LIBRARY rnafolding )
else (LIB_RNAFOLDING )
    message ( FATAL_ERROR "Install Lib RnaFolding: fud.googlecode.com" )
endif (LIB_RNAFOLDING )







set ( EXTRA_LIBS biopp fxp_expat )
target_link_libraries( rna_folding_free_energy_client ${RECABS_CLIENT} ${GETOPT_LIBRARY} ${ANTIVIRALS_LIBRARY} ${RNAFOLDING_LIBRARY} ${EXTRA_LIBS})
target_link_libraries( rna_folding_free_energy_server ${RECABS_SERVER} ${ANTIVIRALS_LIBRARY} ${RNAFOLDING_LIBRARY} ${EXTRA_LIBS})
