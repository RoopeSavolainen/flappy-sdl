cmake_minimum_required(VERSION 3.20)
project(FlappyBird VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(FlappyBird
    src/main.cpp
    src/Game.cpp
    src/Bird.cpp
    src/Pipe.cpp
    src/Renderer.cpp
)

target_include_directories(FlappyBird PRIVATE src)
target_link_libraries(FlappyBird PRIVATE SDL2::SDL2 SDL2::SDL2main)

add_custom_command(TARGET FlappyBird POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:FlappyBird>/assets
)
