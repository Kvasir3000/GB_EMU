cmake_minimum_required(VERSION 3.21) 

# Project name  and version 
project(GB_EMU VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STADARD_REQUIRED True)

set( SOURCES
	src/main.cpp
        src/gameboy.cpp
	src/cpu/cpu.cpp
        src/cartridge.cpp
	src/cpu/opcodes.cpp
	src/cpu/cb_opcodes.cpp
        src/cpu/cpu_misc.cpp
	src/bus.cpp
	src/timers.cpp
	src/utils/utils.cpp
)
add_executable(GB_EMU ${SOURCES})
include_directories(inc)

target_compile_definitions(GB_EMU PUBLIC DEBUG_CPU) 


