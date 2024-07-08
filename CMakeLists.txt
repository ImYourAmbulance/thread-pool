cmake_minimum_required(VERSION 3.15 FATAL_ERROR) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(thread_pool_proj)

add_compile_definitions(READ_FROM_FILE)

add_executable(test_executable src/main.cpp)

add_library(thread_pool_lib src/thread_pool.h 
                            src/thread_pool.cpp)

target_link_libraries(test_executable thread_pool_lib)
