find_package( Boost 1.37 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )


if ( MILI )
    if ( GETOPT )
        set ( server_srcs counter_client.cpp  counter_processor.cpp )

        add_executable( counter-client ${server_srcs} )

        target_link_libraries( counter-client fud_client ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${GETOPT} )
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif (GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )