cmake_minimum_required (VERSION 3.10)
project(WebServer)

set(CMAKE_CXX_COMPILER "g++")

link_libraries(pthread)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -lpthread -Wno-unused-parameter -O0 ")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -std=c++11 -lpthread -Wno-unused-parameter -O0") 


set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(./ DIR_SRCS)

add_executable(WebServer ${DIR_SRCS})
