# $Id: CMakeLists.txt 2011-07-30 02:28:56Z diazdiego86 $

cmake_minimum_required( VERSION 2.6 )

project( comb_eng )

add_subdirectory ( src )

option( apps "Compile sample applications too." OFF )

if ( apps )
    find_file(COMBENG_H combeng/combeng.h /usr/local/include)
    if ( COMBENG_H )
        message ( STATUS "Compiling sample applications as well." )
        add_subdirectory( apps/clothes-changer )
   #     add_subdirectory( apps/RNAFoldingFE )
    else ( COMBENG_H )
        message ( STATUS "Cannot compile sample applications - You must install CombEng first: fud.googlecode.com" )
    endif ( COMBENG_H )
endif ( apps )
