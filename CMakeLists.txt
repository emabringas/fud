# $Id: CMakeLists.txt 573 2011-06-13 20:01:53Z emab73 $

cmake_minimum_required( VERSION 2.6 )

project( fud )

add_subdirectory( src )

option( apps "Compile sample applications too." OFF )

if ( apps )
    message ( STATUS "Compiling sample applications as well." )
    add_subdirectory( apps )
endif ( apps )


option( ResendPendingJobs "Resend pending jobs units to free clients." ON )



