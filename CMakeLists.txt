# $Id: CMakeLists.txt 220 2010-07-15 23:12:19Z billybiset $

cmake_minimum_required( VERSION 2.6 )

project( fud )

add_subdirectory( src )

option( apps "Compile sample applications too." OFF )

if ( apps )
    message ( STATUS "Compiling sample applications as well." )
    include_directories( src/common )
    add_subdirectory( apps )
endif ( apps )
