# Cask
Cask (C-based Atomic Storage Kernel) is a minimal binary file–backed key–value storage engine written in C (C11).  
Designed to emphasize memory safety, deterministic data layout, low-level file I/O, and toolchain-driven development.

## 🚀 Features
- Custom binary file format
- Fixed-size record storage
- Manual byte-offset indexing
- Deterministic memory layout (no dynamic resizing)
- Header validation (magic number + versioning)
- Record operations:
    - Create record
    - Read record
    - Delete record
- Storage preallocation
- Error handling via enums
- Portable build system (CMake + Make)
- Static analysis with clang-tidy
- Containerized dev environment (Docker / Dev Container)

## Tech Stack and Technologies

### Programming Language
- C (C11)  

### Compiler
- GCC / Clang

### Build System
- CMake
- Make

### Testing
- CTest

### Static Analysis
- clang-tidy

### Key Concepts/Technologies Applied
- Binary file I/O → persistent storage using fread / fwrite
- Structs & Memory Safety → fixed-size records, no undefined behavior
- Enums for error handling → robust API design
- Build Automation with CMake → reproducible builds across platforms
- Unit testing and CI pipelines → quality assurance
- Debugging tools → gdb, valgrind

## Directory & Project Structure
- include/ → header files (.h)
- src/ → implementation files (.c)
- tests/ → test programs
- data/ → runtime binary store file
- build/ → compiled objects and final executable (ignored in git)

## Build Instructions
```bash
mkdir build
cd build  
cmake ..  
cmake --build .
make
```

## Run
```bash
./cask
```

## Docker / Dev Container
Build image:
```bash
make docker-build
```

Run container:
```bash
make docker-run
```

Inside container:
```bash
mkdir build
cd build
cmake ..
cmake --build .
make
```

## Testing
```bash
cd build
ctest
```

## Credits
Created by Louis Nguyen
