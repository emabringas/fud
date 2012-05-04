find_package( Boost 1.35 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )

if ( MILI )
    if ( GETOPT )
        set ( client_srcs counter_processor.cpp counter_client.cpp )
        add_executable( file-size-client ${client_srcs} )

        target_link_libraries( file-size-client  fud_client ${GETOPT} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} )
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif (GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )
