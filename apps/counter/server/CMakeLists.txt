# $Id:$
  
find_package( Boost 1.37 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

set ( BOINC_LIBS ${SCHED} ${MYSQL_CLIENT} ${BOINC_CRYPT} )

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message ( STATUS "Compiling with debbug support." )
    add_definitions( -ggdb3 )
endif (CMAKE_BUILD_TYPE MATCHES Debug)

if ( MILI )


    set ( server_srcs counter.cpp counter_main.cpp  number_database.cpp )

    add_executable( counter ${server_srcs} )

    target_link_libraries( counter fud_server ${BOINC_LIBS} )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )
