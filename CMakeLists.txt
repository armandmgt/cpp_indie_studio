cmake_minimum_required(VERSION 3.10)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(srcs)