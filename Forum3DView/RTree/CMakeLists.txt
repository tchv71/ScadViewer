cmake_minimum_required(VERSION 2.8.11)

include_directories(
    .
)

file(GLOB CXX_SRCS
    *.cpp
	*.h
)

add_library(RTree ${CXX_SRCS})