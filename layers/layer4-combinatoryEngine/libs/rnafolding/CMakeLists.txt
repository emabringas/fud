# $Id: CMakeLists.txt 2011-03-22 18:42:09Z diazdiego86 $

cmake_minimum_required( VERSION 2.6 )

project( lib_rnafolding CXX )

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

            if ( CMAKE_BUILD_TYPE MATCHES Debug )
                message ( STATUS "Compiling with debbug support." )
                add_definitions( -ggdb3 )
                endif ( CMAKE_BUILD_TYPE MATCHES Debug )

                include_directories( . include src )

                set ( lib_srcs     src/RNABackendProxy.cpp
                      src/RNAFold.cpp
                      src/SecStructure.cpp
                      src/RNABackendsFactory.cpp
                    )

                set ( rnafolding_header rnafolding.h )

                set ( rnafolding_private_headers    include/IFold.h
                      include/RNAFold.h
                      include/RNABackendsConfig.h
                      include/RNABackendProxy.h
                      include/rna_backends_exceptions.h
                      include/rna_backends_types.h
                      include/RNABackendsFactory.h
                    )

                install ( FILES  ${rnafolding_header} DESTINATION include/rnafolding )
                install ( FILES  ${rnafolding_private_headers}  DESTINATION include/rnafolding/.private )

                add_library ( rnafolding SHARED ${lib_srcs} )

                set ( CMAKE_INSTALL_PREFIX /usr/local )

                install ( TARGETS rnafolding LIBRARY DESTINATION lib )
