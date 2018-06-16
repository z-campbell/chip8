cmake_minimum_required(VERSION 3.8)
project(chip8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        chip8.c
        chip8.h
        chip_emu.c opcodes.c opcodes.h chip_emu.h)

add_executable(chip8 ${SOURCE_FILES})
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework SDL2 -framework SDL2_Mixer") # compiler version and compiler flags.