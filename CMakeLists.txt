cmake_minimum_required(VERSION 3.10)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
if (WIN32)
	include_directories(irrlicht)
	include_directories(SFML)
endif()
add_subdirectory(srcs)