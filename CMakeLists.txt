cmake_minimum_required(VERSION 3.21) 

# Project name  and version 
project(GB_EMU VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STADARD_REQUIRED True)

set( SOURCES
	src/main.cpp
	src/cpu.cpp
)
add_executable(GB_EMU ${SOURCES})
include_directories(inc)

