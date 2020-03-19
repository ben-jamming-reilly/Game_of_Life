cmake_minimum_required(VERSION 3.0)

project(SDL_GameOfLife)

set(SDL2_DIR "C:/libsdl/lib/cmake/SDL2")
#this points to cmake for the compiler
include_directories("C:/libsdl/include/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp game_of_life.cpp display.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})