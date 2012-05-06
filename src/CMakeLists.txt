# $Id: CMakeLists.txt 856 2011-12-13 23:02:50Z rulitox.s@gmail.com $

find_file ( MILI mili/mili.h )

add_definitions ( -DMILI_NAMESPACE )

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message ( STATUS "Compiling with debbug support." )
    add_definitions( -ggdb3 )
endif (CMAKE_BUILD_TYPE MATCHES Debug)

include_directories( common server client )

IF(CMAKE_COVER_ON MATCHES on)
    message ( STATUS "COVER ON")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -lgcov -fprofile-arcs -ftest-coverage")
endif(CMAKE_COVER_ON MATCHES on)

# Middleware selection
if ( NOT DEFINED middleware )
    set ( middleware "asio" ) # Default middleware asio
    message ( STATUS "Using default middleware: asio")
elseif ( middleware STREQUAL "asio" )
    message ( STATUS "Using middleware: asio")
elseif (middleware STREQUAL "boinc" )
    message ( STATUS "Using middleware: boinc")
    set ( BUILD_SHARED_LIBS OFF)
    set ( Boost_USE_STATIC_LIBS ON )
endif ( NOT DEFINED middleware )
add_subdirectory( middlewares )

if ( middleware_server STREQUAL "" )
    message ( FATAL_ERROR "Couldn't locate a middleware implementation.")
endif ( middleware_server STREQUAL "" )


find_package( Boost 1.42 REQUIRED COMPONENTS thread system )

if ( MILI )
    set ( common_srcs common/job_unit.cpp )
    set ( server_srcs server/distributable_job.cpp
                      server/job_manager.cpp
                      server/clients_manager.cpp
                      server/client_proxy.cpp
                      server/processing_history.cpp )

    add_library( fud_server SHARED ${middleware_server} ${server_srcs} ${common_srcs} )

    # Include the headers used for the middleware to the target
    include_directories( ${MIDDLEWARE_HEADERS} )
    
    target_link_libraries( fud_server -lgcov ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${MIDDLEWARE_SERVER_LIBS})

    set ( client_srcs client/processors_manager.cpp
                      client/client_processor.cpp   )

    if(middleware STREQUAL "boinc" ) # static library target for client
        add_library( fud_client STATIC ${middleware_client} ${client_srcs} ${common_srcs} )
    else(middleware STREQUAL "boinc" ) #  dynamic library target for client
        add_library( fud_client SHARED ${middleware_client} ${client_srcs} ${common_srcs} )
    endif(middleware STREQUAL "boinc" )
        
    
    target_link_libraries( fud_client -lgcov ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${MIDDLEWARE_CLIENT_LIBS} )

else ( MILI )
    message ( FATAL_ERROR "You must install MiLi: mili.googlecode.com" )
endif ( MILI )

set ( CMAKE_INSTALL_PREFIX /usr/local )

install ( TARGETS fud_server    LIBRARY DESTINATION lib )     
if(middleware STREQUAL "boinc" ) # static library target for client
    install ( TARGETS fud_client    LIBRARY ARCHIVE DESTINATION lib )
else(middleware STREQUAL "boinc" ) #  dynamic library target for client
    install ( TARGETS fud_client    LIBRARY DESTINATION lib )
endif(middleware STREQUAL "boinc" )


set ( fud_headers common/fud_server.h
                  common/fud_client.h)

set ( fud_private_headers common/distributable_job.h
                          common/job_unit.h
                          common/common.h
                          server/events.h
                          client/client_processor.h
                          client/distribution_client.h )

install ( FILES  fud.h                     DESTINATION include )
install ( FILES  ${fud_headers}          DESTINATION include/fud )
install ( FILES  ${fud_private_headers} DESTINATION include/fud/.private )
