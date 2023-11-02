cmake_minimum_required(VERSION 3.5)

project(min_spanning_tree)

set(CMAKE_CXX_STANDART 20)

set(HEADER_FILES
	include/2_heap.h
	include/Graph.h
	include/Timer.h
	include/UnionFind.h)

set(SOURCE_FILES
	main.cpp
	src/2_heap.cpp
	src/Graph.cpp
	src/Timer.cpp)

include_directories(include)

add_executable(min_spanning_tree ${SOURCE_FILES})

source_group("Header Files" FILES ${HEADER_SILES})