cmake_minimum_required (VERSION 2.6)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
#message(${CMAKE_CXX_FLAGS})
#CXX=g++
project(main)
set(CMAKE_CXX_FLAGS                "-Wall -std=c++11")
add_executable(main main.cc text_query.cc text_query.h)
