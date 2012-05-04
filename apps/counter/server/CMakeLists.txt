find_package( Boost 1.37 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )

# find_library( FUD fud REQUIRED )

if ( MILI )
    if ( GETOPT )
        set ( server_srcs counter.cpp counter_main.cpp  number_database.cpp )

        add_executable( counter ${server_srcs} )

        target_link_libraries( counter fud ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${GETOPT} )
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif (GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )