add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include) 
include_directories(${gtest_SOURCE_DIR}) 
message(${gtest_SOURCE_DIR}/include) 
message(${gtest_SOURCE_DIR}) 
include_directories(${gmock_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}) 
message(${gmock_SOURCE_DIR}/include) 
message(${gmock_SOURCE_DIR})

include_directories(${gprc_SOURCE_DIR}/include)

include(Sources.cmake)

add_custom_target(
    AddVirtualKeyword
    COMMAND ${PYTHON_EXECUTABLE} ${PY_PATH}/AddVirtualToRequests.py ${PROTOS_DIR} ${PROTO_SRC_DIR}
    COMMENT "Adding virtual keywords in grpc generated services"
    DEPENDS ${PROTOS}
    VERBATIM
)

add_executable(tests.out main.cpp ${TESTS_SRC})
add_dependencies(tests.out AddVirtualKeyword)
target_link_libraries(tests.out gtest gmock CASISCO)
