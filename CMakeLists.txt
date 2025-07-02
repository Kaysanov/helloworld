cmake_minimum_required(VERSION 3.10.0)
project(HelowWorld VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)

set(SOURCE_ROOT src)
set(INC_DIR include)

# Список исходных файлов
set(SOURCES
    main.cpp
    ${SOURCE_ROOT}/HotkeyManager.cpp
    ${INC_DIR}/HotkeyManager.h
    ${SOURCE_ROOT}/InputState.cpp
    ${INC_DIR}/InputState.h
    ${SOURCE_ROOT}/HotkeyRegistry.cpp
    ${INC_DIR}/HotkeyRegistry.h
    ${SOURCE_ROOT}/EventProcessor.cpp
    ${INC_DIR}/EventProcessor.h
    ${SOURCE_ROOT}/ModifierUtils.cpp
    ${INC_DIR}/ModifierUtils.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Настройка включения директорий
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_ROOT}
    ${INC_DIR}
)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        fmt::fmt
        sdl::sdl    
    )

# Опции для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()