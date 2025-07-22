cmake_minimum_required(VERSION 3.10.0)

project(HelowWorld VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_ROOT src)
set(INC_DIR include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Список исходных файлов для библиотеки
set(LIB_SOURCES
    ${SOURCE_ROOT}/MouseHandler.cpp
    ${SOURCE_ROOT}/HotkeyHandler.cpp
    ${SOURCE_ROOT}/InputProcessor.cpp
    ${SOURCE_ROOT}/ConfigManager.cpp
    ${SOURCE_ROOT}/InputStateManager.cpp
)

# Создание статической библиотеки с основной логикой
add_library(InputSystemLib STATIC ${LIB_SOURCES})
target_include_directories(InputSystemLib PUBLIC ${INC_DIR})
target_link_libraries(InputSystemLib PUBLIC fmt::fmt nlohmann_json::nlohmann_json)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_ROOT}/SDL3EventGenerator.cpp)

# Настройка включения директорий
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SOURCE_ROOT}
    ${INC_DIR}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    InputSystemLib
    SDL3::SDL3
)

# Секция для тестов
enable_testing()
add_subdirectory(tests)
# Опции для отладки
add_compile_options(
    "$<$<CONFIG:Debug>:-g;-O0;-Wall;-Wextra;-fsanitize=address,undefined>"
    "$<$<CONFIG:Release>:-O3>"
)




#option(BUILD_TESTING "Build tests" OFF)
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")