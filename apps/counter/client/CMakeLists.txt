# $Id:$

find_package( Boost 1.37 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

if ( MILI )
    set ( client_srcs counter_client.cpp  counter_processor.cpp )

    add_executable( counter-client ${client_srcs} )

    target_link_libraries( counter-client fud_client )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )
