cmake_minimum_required(VERSION 2.8)
project(xredis_server)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmakes)
set(SOURCE_FILES
    src/sds.c
    src/sds.h
    src/sdsalloc.h
    src/xRedisServerLib.cpp
    src/xRedisServerLib.h)
find_package(LibEvent REQUIRED)
include_directories(
        ${LIBEVENT_INCLUDE_DIR}
)

add_subdirectory(example)

set (XREDIS_SERVER_EXTERNAL_LIBS
        ${LIBEVENT_LIBRARY}
        ${LIBEVENT_PTHREADS_LIBRARY}
        ${LIBEVENT_OPENSSL_LIBRARY}
        ${LIBEVENT_CORE_LIBRARY}
        "m"
        "dl"
        )

link_directories("/usr/lib" "/usr/local/lib")

add_library(xredis_server ${SOURCE_FILES})
target_link_libraries(xredis_server ${XREDIS_SERVER_EXTERNAL_LIBS})