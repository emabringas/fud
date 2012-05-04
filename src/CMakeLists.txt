# $Id: CMakeLists.txt 573 2011-06-13 20:01:53Z emab73 $

find_file ( MILI mili/mili.h )

add_definitions ( -DMILI_NAMESPACE -Wall -Wextra -pedantic -ansi )

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

    # Include the headers used for the middleware to the target
    include_directories( ${MIDDLEWARE_HEADERS} )

    add_library( fud SHARED ${middleware_server} ${server_srcs} ${common_srcs} )

    target_link_libraries( fud ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${MIDDLEWARE_LIBS} )

    set ( client_srcs client/client_processor.cpp
                      client/processors_manager.cpp
                      client/distribution_client.cpp
                      client/interactive_helper.cpp
                      client/sender.cpp              )

    add_library( fud_client SHARED ${middleware_client} ${client_srcs} ${common_srcs} )

    target_link_libraries( fud_client ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${MIDDLEWARE_LIBS} )

else ( MILI )
    message ( FATAL_ERROR "You must install MiLi: mili.googlecode.com" )
endif ( MILI )


if ( ResendPendingJobs )
    message ( STATUS "Resend pending jobs units to free clients." )
    add_definitions ( -DRESEND_PENDING_JOBS )
else ( ResendPendingJobs )
    message ( STATUS "Avoid resend pending jobs units to free clients." )
endif ( ResendPendingJobs )

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
                          client/distribution_client.h 
                          client/interactive_helper.h
                          client/sender.h)

install ( FILES  ${fud_headers}         DESTINATION include/fud )
install ( FILES  ${fud_private_headers} DESTINATION include/fud )
