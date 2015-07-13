cmake_minimum_required(VERSION 3.2)
project(sksebot)

setProperty(sksebot, CXX_STANDARD_LIBARY, 14)#draft will be replaced by working code
setProperty(sksebot, CXX_STANDARD_LIBARY_REQUIERMENT, ON)

set( SOURCE_FILES
    BaseAuRegClass.cpp
    BaseAuRegClass.h
    Main.cpp )

add_executable(sksebot ${SOURCE_FILES})
