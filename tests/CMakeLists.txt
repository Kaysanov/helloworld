cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Google Test
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ../include)

# Добавляем исходные файлы
add_executable(Tests
    test_input_state_manager.cpp
    test_hotkey_handler.cpp
    test_mouse_handler.cpp
    test_input_processor.cpp
)

# Связываем с библиотеками Google Test и pthread
target_link_libraries(Tests
    InputSystemLib # Наша библиотека с логикой
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
