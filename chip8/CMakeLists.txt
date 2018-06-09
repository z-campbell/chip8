cmake_minimum_required(VERSION 3.8)
project(chip8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework SDL2") # compiler version and compiler flags.
set(SOURCE_FILES
        chip8.c
        chip8.h
        graphics8.c
        graphics8.h
        main.c opcodes.c opcodes.h opcode_functions.c opcode_functions.h)

add_executable(chip8 ${SOURCE_FILES})