cmake_minimum_required(VERSION 3.3)

project(sksebot)

set( SOURCE_FILES BaseAuRegClass.cpp BaseAuRegClass.h Main.cpp )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package( Boost 1.58.0 COMPONENTS regex)

if(BOOST_FOUND)
	include_directories(${BOOST_INCLUDE_DIRS})
	add_executable(sksebot ${SOURCE_FILES})
	
	set_property(TARGET sksebot PROPERTY CXX_STANDARD 14)
	set_property(TARGET sksebot PROPERTY CXX_STANDARD_LIBARY_REQUIRED ON)
	
	target_link_libraries(sksebot ${BOOST_LIBARIES})
endif()