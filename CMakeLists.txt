cmake_minimum_required(VERSION 3.10.0)

project(HelowWorld VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)
find_package(nlohmann_json REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_ROOT src)
set(INC_DIR include)

# Добавляем поиск GTest
#find_package(GTest REQUIRED)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
# Список исходных файлов
set(SOURCES
    main.cpp    
    ${SOURCE_ROOT}/MouseHandler.cpp
    ${SOURCE_ROOT}/HotkeyHandler.cpp
    ${SOURCE_ROOT}/InputProcessor.cpp
    ${SOURCE_ROOT}/SDL3EventGenerator.cpp
    ${SOURCE_ROOT}/ConfigManager.cpp
    ${SOURCE_ROOT}/InputStateManager.cpp
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