CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -g
INCLUDE = -I./include
SRC = src/main.c src/storage.c src/record.c src/error.c
OBJ = ${SRC:src/%.c=build/%.o}
TARGET = build/cask

all: $(TARGET)

build/cask: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf build

run: all
	./$(TARGET)

.PHONY: all clean run