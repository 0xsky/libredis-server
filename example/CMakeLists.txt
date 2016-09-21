cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
        xRedisServer.cpp)

add_executable(server ${SOURCE_FILES})

include_directories("../src/")
link_directories("/usr/lib" "/usr/local/lib" "${PROJECT_BINARY_DIR}/src/")
target_link_libraries(server ${XREDIS_SERVER_EXTERNAL_LIBS} ${SYS_LIBS} "xredis_server")