cmake_minimum_required(VERSION 3.7)
project(Roguelike)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS GameSystem.h Player.h Enemy.h Level.h)
set(SOURCE_FILES GameSystem.cpp Player.cpp Enemy.cpp Level.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-lncurses")
add_executable(Roguelike main.cpp ${SOURCE_FILES})