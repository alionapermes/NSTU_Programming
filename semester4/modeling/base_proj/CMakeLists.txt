cmake_minimum_required(VERSION 3.10)
project(lab)

if (DEBUG)
    add_compile_options(-g3 -ggdb)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC lab)
set(SRC main.cpp)

add_executable(${EXEC} ${SRC})

