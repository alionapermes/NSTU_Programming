cmake_minimum_required(VERSION 3.10)
project(coursework)

add_compile_options(-g3 -ggdb)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC test)
set(SRC test.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} ${GTEST_LIBRARIES} pthread)

