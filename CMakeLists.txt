cmake_minimum_required(VERSION 3.2)
project(sksebot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    BaseAuRegClass.cpp
    BaseAuRegClass.h
    Main.cpp
    TestFile.h)

add_executable(sksebot ${SOURCE_FILES})