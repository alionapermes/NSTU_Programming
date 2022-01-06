CC=g++
FLAGS=-std=c++20 -g
SRC=main.cpp
EXEC=lab
BUILD_DIR=build

all: clean
	mkdir $(BUILD_DIR)
	$(CC) $(SRC) -o $(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)
