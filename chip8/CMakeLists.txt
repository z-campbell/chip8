cmake_minimum_required(VERSION 3.8)
project(chip8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework SDL2") # compiler version and compiler flags.
set(SOURCE_FILES
        chip8.c
        chip8.h
        chip_emu.c opcodes.c opcodes.h chip_emu.h)

add_executable(chip8 ${SOURCE_FILES})