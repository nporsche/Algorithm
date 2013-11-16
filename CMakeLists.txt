cmake_minimum_required(VERSION 2.8)

PROJECT(Algorithm)

ADD_SUBDIRECTORY(src)

MESSAGE(STATUS "this is" ${Algorithm_SOURCE_DIR})


SET(CMAKE_C_COMPILER g++)
