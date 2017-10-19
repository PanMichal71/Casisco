protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

include(Sources.cmake)

add_library(CASISCO ${SOURCES} ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(CASISCO gRPC::grpc++_reflection  protobuf::libprotobuf)
