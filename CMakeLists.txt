cmake_minimum_required(VERSION 3.10.0)

project(HelowWorld VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)
find_package(nlohmann_json REQUIRED)

set(SOURCE_ROOT src)
set(INC_DIR include)

# Список исходных файлов
set(SOURCES
    main.cpp
    ${SOURCE_ROOT}/HotkeyManager.cpp
    ${INC_DIR}/HotkeyManager.h    
    ${SOURCE_ROOT}/ConfigManager.cpp     
    ${INC_DIR}/ConfigManager.h    
    ${INC_DIR}/InputTypes.h
    ${INC_DIR}/InputSystem.h
    ${SOURCE_ROOT}/SDLInputSystem.cpp     
    ${INC_DIR}/SDLInputSystem.h    
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
        SDL3::SDL3
        nlohmann_json::nlohmann_json    
    )

# Опции для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()

#option(BUILD_TESTING "Build tests" OFF)
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")