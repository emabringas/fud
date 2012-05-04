# $Id: CMakeLists.txt 242 2010-08-13 16:31:21Z billybiset $

cmake_minimum_required( VERSION 2.6 )

project( fud )

add_subdirectory( src )

option( apps "Compile sample applications too." OFF )

if ( apps )
    message ( STATUS "Compiling sample applications as well." )
    include_directories( src/common )
    add_subdirectory( apps )
endif ( apps )
