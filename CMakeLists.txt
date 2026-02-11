cmake_minimum_required(VERSION 3.28)

project(cask)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES src/main.c src/storage.c src/error.c src/helper.c)

add_executable(cask ${SOURCES}) # create a target

target_compile_options(cask PRIVATE -Wall -Wextra -pedantic)

set(CMAKE_C_CLANG_TIDY "clang-tidy")

enable_testing()    # enable cmake

add_subdirectory(tests)
