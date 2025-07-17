cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Google Test
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ../include)

message(STATUS "GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")


# Добавляем исходные файлы
add_executable(Tests
    ../src/InputStateManager.cpp
    tests.cpp)

# Связываем с библиотеками Google Test и pthread
target_link_libraries(Tests
    fmt::fmt
    GTest::gtest
    GTest::gtest_main
    Threads::Threads
)

#add_test(NAME InputStateManagerTest COMMAND Tests)

include(GoogleTest)
gtest_discover_tests(Tests)
