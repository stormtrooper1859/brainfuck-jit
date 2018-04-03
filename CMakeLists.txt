cmake_minimum_required(VERSION 3.8)
project(brainfuck_jit C)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O2 -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
set(CMAKE_C_STANDARD 99)

add_executable(brainfuck_jit src/main.c src/compiled_blocks.h)
