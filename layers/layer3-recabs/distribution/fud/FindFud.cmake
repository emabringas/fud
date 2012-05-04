# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_path(LIBFUD_INCLUDE_DIR fud/fud.h fud/fud_client.h
          HINTS /usr/local/include
                /usr/include
           )

find_library(LIBFUD_LIBRARY NAMES fud
             HINTS 
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            )

find_library(LIBFUD_CLIENT_LIBRARY NAMES fud_client
             HINTS 
                    /usr/lib
                    /usr/lib64
                    /usr/local/lib
                    /usr/local/lib64
            )

set(LIBFUD_LIBRARIES ${LIBFUD_LIBRARY} ${LIBFUD_CLIENT_LIBRARY}  )
set(LIBFUD_INCLUDE_DIRS ${LIBFUD_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FUD DEFAULT_MSG
                                  LIBFUD_LIBRARY 
                                  LIBFUD_CLIENT_LIBRARY
                                  LIBFUD_INCLUDE_DIR )

mark_as_advanced(LIBFUD_LIBRARY LIBFUD_CLIENT_LIBRARY LIBFUD_INCLUDE_DIR)
