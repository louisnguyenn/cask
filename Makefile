CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g
INCLUDE = -Iinclude
SRC = src/main.c src/storage.c src/record.c src/error.c
OBJ = ${SRC:src/%.c=build/%.o}

all: build/cask

build/cask: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o build/cask

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf build

run: all
	./build/cask

.PHONY: all clean run