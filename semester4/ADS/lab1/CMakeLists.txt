cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 20)

set(EXEC test)
set(SRC test.cpp)

if (DEBUG)
    add_compile_options(-g3 -ggdb)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} ${GTEST_LIBRARIES} pthread)
