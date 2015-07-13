cmake_minimum_required(VERSION 3.2)
project(sksebot)

setProperty(sksebot, CXX_STANDARD, 14)#draft will be replaced by working code
setProperty(sksebot, CXX_STANDARD_LIBARY_REQUIRED, ON)

set( SOURCE_FILES
    BaseAuRegClass.cpp
    BaseAuRegClass.h
    Main.cpp )

#libs(boost)
set(Boost_USE_STATIC_LIBS, OFF)
set(Boost_USE_MULTITHREADED, ON)
set(Boost_USE_STATIC_RUNTIME, OFF)

find_package( Boost 1.58.0 COMPONENTS regex)#newest version

if(BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
    add_executable(sksebot ${SOURCE_FILES})
    target_link_libaries(sksebot ${BOOST_LIBARIES})
else()
    message("boost not found ver: 1.58.0 \n currently hardcoded sorry chanage line 17 to fit newest version")
endif



