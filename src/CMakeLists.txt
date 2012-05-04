# $Id: CMakeLists.txt 242 2010-08-13 16:31:21Z billybiset $

find_file ( MILI mili/mili.h )

add_definitions ( -DMILI_NAMESPACE )

include_directories( common server client )

add_subdirectory( middlewares )

if ( middleware_server STREQUAL "" )
    message ( FATAL_ERROR "Couldn't locate a middleware implementation.")
endif ()

find_package( Boost 1.35 REQUIRED COMPONENTS thread system )

if ( MILI )
    set ( common_srcs common/job_unit.cpp )

    set ( server_srcs server/distributable_job.cpp
                      server/job_manager.cpp
                      server/clients_manager.cpp
                      server/client_proxy.cpp
                      server/processing_history.cpp )

    add_library( fud SHARED ${middleware_server} ${server_srcs} ${common_srcs} )

    target_link_libraries( fud ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} )

    set ( client_srcs client/client_processor.cpp
                      client/processors_manager.cpp )

    add_library( fud_client SHARED ${middleware_client} ${client_srcs} ${common_srcs} )

    target_link_libraries( fud_client ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} )

else ( MILI )
    message ( FATAL_ERROR "You must install MiLi: mili.googlecode.com" )
endif ( MILI )

set ( CMAKE_INSTALL_PREFIX /usr/local )

install ( TARGETS fud        LIBRARY DESTINATION lib )
install ( TARGETS fud_client LIBRARY DESTINATION lib )

set ( fud_headers common/fud.h
                  common/fud_client.h)

set ( fud_private_headers common/distributable_job.h
                          common/job_unit.h
                          common/common.h
                          server/events.h
                          client/client_processor.h
                          client/distribution_client.h )

install ( FILES  ${fud_headers}         DESTINATION include/fud )
install ( FILES  ${fud_private_headers} DESTINATION include/fud/.private )
