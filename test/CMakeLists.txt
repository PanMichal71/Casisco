add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include) 
include_directories(${gtest_SOURCE_DIR})  
include_directories(${gmock_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}) 

include_directories(${gprc_SOURCE_DIR}/include)

include(Sources.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tests.out main.cpp ${TESTS_SRC})
target_link_libraries(tests.out gtest gmock CASISCO)
