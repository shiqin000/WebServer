cmake_minimum_required (VERSION 3.10)

project(WebServer)

set(CMAKE_BUILD_TYPE "VERSION 0.1")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") 

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(./ DIR_SRCS)

add_executable(WebServer ${DIR_SRCS})
