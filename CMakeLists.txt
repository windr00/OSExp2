cmake_minimum_required(VERSION 3.5)
project(OSExp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c TypeDefines.h Producer.c Producer.h Consumer.c Consumer.h)
add_executable(OSExp2 ${SOURCE_FILES})