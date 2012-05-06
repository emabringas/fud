find_package( Boost 1.35 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )

add_definitions( -DMILI_NAMESPACE )

if ( MILI )
    if ( GETOPT )
        set ( server_srcs counter.cpp counter_main.cpp )

        add_executable( file-size-counter ${server_srcs} )

        target_link_libraries( file-size-counter fud ${GETOPT} ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} )
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif (GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )