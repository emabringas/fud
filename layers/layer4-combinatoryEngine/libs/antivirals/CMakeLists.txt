# $Id: CMakeLists.txt 372 2011-03-10 10:32:12Z diazdiego86 $

cmake_minimum_required( VERSION 2.6 )

project( lib_antivirals CXX )

add_definitions ( -Wall -Wextra -pedantic -ansi )

option( weff "Compile with warnings violations of the Effective C++ book." OFF )

if ( weff )
    message ( STATUS "Compiling with warnings violations of the Effective C++ book." )
    add_definitions (-Weffc++)
endif ( weff )

find_file ( MILI mili/mili.h )
if (NOT MILI )
    message ( FATAL_ERROR "You must install MiLi: mili.googlecode.com" )
endif (NOT MILI )

find_file ( BIOPP biopp/biopp.h )
if (NOT BIOPP )
    message ( FATAL_ERROR "You must install Biopp: biopp.googlecode.com" )
endif (NOT BIOPP )

find_file ( FXP fxp.h )
if (NOT FXP )
    message ( FATAL_ERROR "You must install fx-parser: fx-parser.googlecode.com" )
endif ( NOT FXP )

if ( CMAKE_BUILD_TYPE MATCHES Debug )
    message ( STATUS "Compiling with debbug support." )
    add_definitions( -ggdb3 )
endif ( CMAKE_BUILD_TYPE MATCHES Debug )

include_directories( . common_include framework )

set ( lib_srcs    framework/antiviral_imp.cpp
                   framework/antiviral_set.cpp
                   framework/data_base.cpp
                   framework/distance_matrix.cpp
                   framework/sequence.cpp

    )

set ( antivirals_header antivirals.h )

set ( antivirals_private_headers    common_include/aso_exception.h
                                        common_include/optimized_container.h
                                        framework/antiviral.h
                                        framework/antiviral_imp.h
                                        framework/antiviral_selector.h
                                        framework/antiviral_set.h
                                        framework/data_base.h
                                        framework/distance_matrix.h
                                        framework/sequence.h
    )

install ( FILES  ${antivirals_header} DESTINATION include/antivirals )
install ( FILES  ${antivirals_private_headers}  DESTINATION include/antivirals/.private )

add_library ( antivirals SHARED ${lib_srcs} )

set ( CMAKE_INSTALL_PREFIX /usr/local )

install ( TARGETS antivirals LIBRARY DESTINATION lib )

