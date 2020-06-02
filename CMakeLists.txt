cmake_minimum_required(VERSION 3.10.0)
project(diplom-realizations)

add_executable(mtf src/mtf/main.cpp)
target_include_directories(mtf PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
