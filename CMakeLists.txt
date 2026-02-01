cmake_minimum_required(VERSION 3.15)

project(cask)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES src/main.c src/storage.c src/error.c src/record.c src/helper.c)

add_executable(cask ${SOURCES})

target_compile_options(cask PRIVATE -Wall -Wextra -pedantic)