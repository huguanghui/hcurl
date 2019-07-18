cmake_minimum_required(VERSION 2.6)

project(hcurl C)

set(hcurl_major 1)
set(hcurl_minor 0)

set(C_FLAGS
-Wall
-rdynamic
)

string(REPLACE ";" " " CMAKE_C_FLAGS "${C_FLAGS}")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message(STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS})
message(STATUS "PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(sample)

