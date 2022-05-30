set(SRC main.cpp)
set(BIN test)

add_executable(${BIN} ${SRC})
target_link_libraries(${BIN} ${CONAN_LIBS})

