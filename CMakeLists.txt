cmake_minimum_required(VERSION 3.7)
project(CASISCO)

#SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/casisco.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

add_subdirectory(src)
add_subdirectory(test)

add_compile_options(
    -std=c++14
    -fdiagnostics-color=auto
    -g
    -ffunction-sections
    -fdata-sections
    -fPIC
    -Wsign-compare
    -Wreturn-type
    -Wmaybe-uninitialized
    -Wunused-variable
    -Wall
    -Wpedantic
)

