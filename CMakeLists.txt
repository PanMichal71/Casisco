cmake_minimum_required(VERSION 3.7)
project(CASISCO)
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
