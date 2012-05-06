# $Id: CMakeLists.txt 818 2011-12-06 14:52:54Z rulitox.s@gmail.com $

# Root directory of BOINC SOURCE
if ( NOT DEFINED boinc_source )
    set ( boinc_source "~/boinc"  )
endif ( NOT DEFINED boinc_source )
MESSAGE(STATUS  "Boinc source: '${boinc_source}'" )

# MYSQL Headers
if ( NOT DEFINED mysql_header )
    set (mysql_header /usr/include/mysql/ /usr/local/include/mysql/ )
    find_path( MYSQL mysql.h ${mysql_header})
else ()
    find_path ( MYSQL mysql_header )
endif (  NOT DEFINED mysql_header )

if ( NOT MYSQL )
    MESSAGE(FATAL_ERROR "The Mysql Header File Not Found in '${mysql_header}'" )
endif ( NOT MYSQL )
MESSAGE(STATUS  "MySQL Headers: '${MYSQL}'" )

find_library( PTHREAD pthread REQUIRED )
if (NOT PTHREAD)
    MESSAGE(FATAL_ERROR "Could not find pthread library" )
endif (NOT PTHREAD)

find_library( SSL ssl REQUIRED )
if (NOT SSL)
    MESSAGE(FATAL_ERROR "Could not find ssl library" )
endif (NOT SSL)

# Find BOINC libraries
SET (CMAKE_FIND_LIBRARY_SUFFIXES .a)

find_library( BOINC boinc REQUIRED )
if (NOT BOINC)
    MESSAGE(FATAL_ERROR "Could not find boinc library" )
endif (NOT BOINC)

find_library( BOINC_API boinc_api REQUIRED )
if (NOT BOINC_API)
    MESSAGE(FATAL_ERROR "Could not find boinc_api library" )
endif (NOT BOINC_API)

find_library(SCHED NAMES sched REQUIRED )
if (NOT SCHED)
    MESSAGE(FATAL_ERROR "Could not find sched library" )
endif (NOT SCHED)

find_library( BOINC_CRYPT boinc_crypt REQUIRED )
if (NOT BOINC_CRYPT)
MESSAGE(FATAL_ERROR "Could not find boinc_crypt library" )
endif (NOT BOINC_CRYPT)

find_library ( MYSQL_CLIENT mysqlclient REQUIRED )
if (NOT MYSQL_CLIENT)
    MESSAGE(FATAL_ERROR "Could not find mysql library" )
endif (NOT MYSQL_CLIENT)

set ( server_file 	server/boinc_clients_manager.cpp PARENT_SCOPE)

set ( client_file 	client/boinc_distribution.cpp PARENT_SCOPE)

set ( MIDDLEWARE_HEADERS	${boinc_source}
                            ${boinc_source}/api 
                            ${boinc_source}/lib 
                            ${boinc_source}/tools
                            ${boinc_source}/db 
                            ${boinc_source}/sched
                            ${MYSQL}
                            ${CMAKE_CURRENT_SOURCE_DIR}/common
    )

include_directories( ${MIDDLEWARE_HEADERS} )

add_library ( validate_util STATIC ${boinc_source}/sched/validate_util.cpp )

set ( MIDDLEWARE_HEADERS ${MIDDLEWARE_HEADERS} PARENT_SCOPE )

set ( MIDDLEWARE_SERVER_LIBS ${BOINC_API} ${SCHED} ${BOINC} ${BOINC_CRYPT} ${MYSQL_CLIENT} ${PTHREAD} validate_util ${SSL} PARENT_SCOPE )

set ( MIDDLEWARE_CLIENT_LIBS ${BOINC_API} ${BOINC} ${BOINC_CRYPT} ${PTHREAD} ${SSL} PARENT_SCOPE )

