cmake_minimum_required(VERSION 3.10)
project(Sulfate VERSION 0.0.1)

enable_language(ASM_NASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# 查找 NASM 程序
find_program(NASM_EXECUTABLE NAMES nasm)
if(NOT NASM_EXECUTABLE)
  message(FATAL_ERROR "NASM assembler not found!")
endif()

# 将找到的 NASM 路径赋给 CMAKE_ASM_NASM_COMPILER
set(CMAKE_ASM_NASM_COMPILER ${NASM_EXECUTABLE})
message(STATUS "Using NASM: ${CMAKE_ASM_NASM_COMPILER}")

subdirs(boot)
subdirs(kernel)
