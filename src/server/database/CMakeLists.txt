include(Sources.cmake)
add_library(CASISCO_DATABASE ${DATABASE_SOURCES})
target_link_libraries(CASISCO_DATABASE leveldb pthread boost_system boost_filesystem)
