cmake_minimum_required(VERSION 2.8)

PROJECT(Algorithm)

SET(CMAKE_CXX_COMPILER g++)

SET(CMAKE_CXX_FLAGS "-g -Wall")

ADD_SUBDIRECTORY(src)

MESSAGE(STATUS "this is" ${Algorithm_SOURCE_DIR})




