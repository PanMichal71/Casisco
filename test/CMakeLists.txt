add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include) 
include_directories(${gtest_SOURCE_DIR}) 
message(${gtest_SOURCE_DIR}/include) 
message(${gtest_SOURCE_DIR}) 
include_directories(${gmock_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}) 
message(${gmock_SOURCE_DIR}/include) 
message(${gmock_SOURCE_DIR})

include(Sources.cmake)

add_executable(tests.out main.cpp ${TESTS_SRC})
target_link_libraries(tests.out gtest gmock )
