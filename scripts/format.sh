#!/bin/bash
find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
echo "Formatted all C files"
