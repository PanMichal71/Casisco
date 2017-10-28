cmake_minimum_required(VERSION 2.8)
project(CASISCO)

add_compile_options(
    -std=c++14
    -fdiagnostics-color=auto
    -g
    -ffunction-sections
    -fdata-sections
    -fPIC
    -Wsign-compare
    -Wreturn-type
    -Wuninitialized
    -Wunused-variable
    -Wall
    -Wpedantic
    -Werror
)

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(PY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/py")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)

SET(PROTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)

set(PROTOS
    ${PROTOS_DIR}/casisco.proto
)


set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

include_directories(src/)

add_subdirectory(src)
add_subdirectory(test)


