# $Id: CMakeLists.txt 372 2011-01-06 22:36:19Z diazdiego86 $

add_definitions ( -Wall -Wextra -pedantic -ansi -g -O0) #-march=core2 -mtune=generic -O2 -pipe -pthread)

option( weff "Compile with warnings violations of the Effective C++ book." OFF )
if ( weff )
    message ( STATUS "Compiling with warnings violations of the Effective C++ book." )
    add_definitions (-Weffc++)
endif ( weff )

find_file ( MILI mili/mili.h )
if ( NOT  MILI )
    message ( FATAL_ERROR "You must install MiLi: mili.googlecode.com" )
endif ( NOT  MILI )

find_file (RECABS recabs/recabs.h )
if ( NOT RECABS )
    message ( FATAL_ERROR "You must install RecAbs: fud.googlecode.com" )
endif ( NOT RECABS )

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message ( STATUS "Compiling with debbug support." )
    add_definitions( -ggdb3 )
endif (CMAKE_BUILD_TYPE MATCHES Debug)

include_directories( . client common combination_policies server )

#option( apps "Compile sample applications too." OFF )

set ( CMAKE_INSTALL_PREFIX /usr/local )

#if ( apps )
#    find_file(COMBENG_H combeng/combeng.h /usr/local/include)
#    if ( COMBENG_H )
#        message ( STATUS "Compiling sample applications as well." )
#        add_subdirectory( apps/clothes-changer )
#        add_subdirectory( apps/RNAFoldingFE )
#    else ( COMBENG_H )
#        message ( STATUS "Cannot compile sample applications - You must install CombEng first: fud.googlecode.com" )
#    endif ( COMBENG_H )
#endif ( apps )

set ( combeng_header combeng.h )

set ( combeng_private_client_headers    client/l5_application_client.h )
set ( combeng_private_common_headers 
                                            common/l4_node.h
                                            common/prune_policy.h
                                            common/combination_policy.h
                                            common/combination_observer.h
                                            common/state_set.h
    )
    
set ( combeng_private_libplugin_headers                                            
                                            combination_policies/composed_combination_policy_parallel.h
                                            combination_policies/composed_combination_policy_sequencial.h
                                            combination_policies/list_combination_policy.h
                                            combination_policies/newtonian_combination_policy.h
                                            combination_policies/combination_policy_predicate.h
                                            combination_policies/observer_aux.h
    )
    
set ( combeng_private_server_headers    server/l5_application_server.h )

install ( FILES  ${combeng_header}                         DESTINATION include/combeng )
install ( FILES  ${combeng_private_client_headers}       DESTINATION include/combeng/.private/client )
install ( FILES  ${combeng_private_common_headers}       DESTINATION include/combeng/.private/common )
install ( FILES  ${combeng_private_libplugin_headers}    DESTINATION include/combeng/.private/libplugin )
install ( FILES  ${combeng_private_server_headers}       DESTINATION include/combeng/.private/server )
