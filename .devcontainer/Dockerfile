FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# update system and install build tools
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-tidy \
    cmake \
    make \
    gdb \
    valgrind \
    git \
    && rm -rf /var/lib/apt/lists/*

# create working directory inside container
WORKDIR /app

# copy project files into container
COPY . .

# create build directory
RUN cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

CMD ["/bin/bash"]
