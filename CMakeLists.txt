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

# 配置 bootloader 相关的路径
set(BOOT_DIR ${CMAKE_SOURCE_DIR}/boot)
set(BOOT_ASM_FILES
    ${BOOT_DIR}/boot.asm
    ${BOOT_DIR}/loader.asm
)

# 定义生成 boot.bin 和 loader.bin 的目标
foreach(asm_file ${BOOT_ASM_FILES})
    # 获取不带扩展名的文件名
    get_filename_component(fname ${asm_file} NAME_WE)
    set(bin_file ${CMAKE_BINARY_DIR}/${fname}.bin)

    
    add_custom_command(
        OUTPUT ${bin_file}
        COMMAND ${NASM_EXECUTABLE} ${asm_file} -o ${bin_file} -I${BOOT_DIR}
        DEPENDS ${asm_file} boot/fat12.inc
        COMMENT "Assembling ${asm_file} to ${bin_file}"
    )
    
    list(APPEND BIN_FILES ${bin_file})
endforeach()

add_custom_target(bootloader ALL DEPENDS ${BIN_FILES})