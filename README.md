# Cask
Cask (C-based Atomic Storage Kernel) is a minimal binary file–backed key–value store written in C.  
Designed to emphasize memory safety, deterministic data layout, and toolchain-driven development.

## Tech Stack and Technologies

### 1️⃣ Programming Language
- C (C11 standard)  
    - Chosen for: low-level memory management, pointers, structs, file I/O  

### 2️⃣ Compiler & Build
- GCC (GNU Compiler Collection)
    - Compiles C code to machine code
    - Provides strict warnings and standard compliance

- Make
    - Automates build process
    - Handles dependency tracking and compilation rules

### 3️⃣ Directory & Project Structure
- include/ → header files (.h) for modularity
- src/ → implementation files (.c)
- tests/ → test programs
- data/ → runtime binary store file
- build/ → compiled objects and final executable

### 4️⃣ Key Concepts/Technologies Applied
- Binary file I/O → persistent storage using fread / fwrite
- Structs & Memory Safety → fixed-size records, no undefined behavior
- Enums for error handling → robust API design
- Makefile + build automation → reproducible builds
- Debugging tools → gdb, valgrind

## Build
```bash
make
```

## Run
```bash
./build/cask
```
