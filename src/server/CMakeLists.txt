protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

include(Sources.cmake)

add_custom_target(
    AddVirtualKeyword
    COMMAND ${PYTHON_EXECUTABLE} ${PY_PATH}/AddVirtualToRequests.py ${PROTOS_DIR} ${PROTO_SRC_DIR}
    COMMENT "Adding virtual keywords in grpc generated services"
    DEPENDS ${PROTOS} ${PROTO_SRCS} ${GRPC_SRCS}
    VERBATIM
)

add_library(CASISCO ${SOURCES} ${PROTO_SRCS} ${GRPC_SRCS})
add_dependencies(CASISCO AddVirtualKeyword)

add_executable(server_cli.out main.cpp)
target_link_libraries(server_cli.out CASISCO)

target_link_libraries(CASISCO gRPC::grpc++_reflection  protobuf::libprotobuf common)
