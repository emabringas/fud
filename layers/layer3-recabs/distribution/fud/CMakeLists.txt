INCLUDE(${CMAKE_SOURCE_DIR}/distribution/fud/FindFud.cmake)

include_directories ( server client )

set ( client_processor     "client/fud_rprocessor.cpp" PARENT_SCOPE )
set ( client_result_sender "client/fud_result_sender.cpp" PARENT_SCOPE )

set ( distribution_client_library ${LIBFUD_CLIENT_LIBRARY} PARENT_SCOPE)

set ( server_manager        "server/fud_rmanager.cpp" PARENT_SCOPE )

set ( distribution_library ${LIBFUD_LIBRARY} PARENT_SCOPE)


