find_package( Boost 1.35 REQUIRED COMPONENTS thread system)

find_file ( MILI mili/mili.h )

find_library( GETOPT getopt_pp REQUIRED )

if ( MILI )
    if ( GETOPT )
        set ( server_srcs client_proxy.cpp asio_server.cpp )
        add_executable( server server.cpp ${server_srcs} )

        target_link_libraries( server  ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${GETOPT} )

        set ( client_srcs  asio_client.cpp )
        add_executable( client client.cpp ${client_srcs} )

        target_link_libraries( client ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${GETOPT} )

        add_executable( server-client server_client.cpp asio_server_client.cpp asio_server.cpp asio_client.cpp client_proxy.cpp )

        target_link_libraries( server-client ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${GETOPT} )
    else ( GETOPT )
        message ( FATAL_ERROR "Install GetOpt_pp: getoptpp.googlecode.com" )
    endif (GETOPT )
else ( MILI )
    message ( FATAL_ERROR "Install MiLi: mili.googlecode.com" )
endif ( MILI )