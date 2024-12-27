

set( SOURCES
	src/main.cpp
        src/gameboy.cpp
	src/cpu/cpu.cpp
        src/cartridge.cpp
	src/cpu/opcodes.cpp
	src/cpu/cb_opcodes.cpp
        src/cpu/cpu_misc.cpp
        src/ppu/ppu.cpp
        src/ppu/ppu_scanline.cpp
        src/ppu/ppu_debug.cpp
        src/ppu/ppu_objects.cpp
	src/bus.cpp
	src/joypad.cpp
	src/timers.cpp
	src/utils/utils.cpp
)
add_executable(GB_EMU ${SOURCES})
include_directories(inc)

target_compile_definitions(GB_EMU PUBLIC DEBUG_CPU) 