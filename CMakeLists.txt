cmake_minimum_required(VERSION 3.10.0)
project(HelowWorld VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} 
        main.cpp
        HotkeyManager.h
        HotkeyManager.cpp
    )

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        fmt::fmt
        sdl::sdl    
    )

