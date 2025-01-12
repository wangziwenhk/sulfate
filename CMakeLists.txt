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

set(BOOT_DIR ${CMAKE_SOURCE_DIR}/boot)
set(BOOT_IMAGE ${CMAKE_BINARY_DIR}/boot.img)

# 初始化一个全局属性来存储所有 POST_BUILD 命令
set_property(GLOBAL PROPERTY BOOT_IMAGE_POST_BUILD_COMMANDS "")

# 定义一个函数，子目录可以调用此函数来注册 POST_BUILD 命令
function(register_boot_image_post_build COMMAND)
  get_property(existing_commands GLOBAL PROPERTY BOOT_IMAGE_POST_BUILD_COMMANDS)
  list(APPEND existing_commands "${COMMAND}")
  set_property(GLOBAL PROPERTY BOOT_IMAGE_POST_BUILD_COMMANDS "${existing_commands}")
endfunction()

# 创建 boot.img
add_custom_command(
        OUTPUT ${BOOT_IMAGE}
        COMMAND ${CMAKE_COMMAND} -E echo "Creating 1.44MB floppy image..."
        COMMAND dd if=/dev/zero of=${BOOT_IMAGE} bs=512 count=2880
        DEPENDS ${BOOT_DIR}/boot.asm ${BOOT_DIR}/loader.asm
        COMMENT "Generating boot.img using dd"
        VERBATIM
)


add_custom_target(
        build_all ALL
        DEPENDS build_kernel build_bootloader
)

add_custom_target(create_boot_image ALL
        DEPENDS build_all
)

add_subdirectory(boot)
add_subdirectory(kernel)

get_property(commands GLOBAL PROPERTY BOOT_IMAGE_POST_BUILD_COMMANDS)

# 为 create_boot_image 目标添加 POST_BUILD 命令
foreach(cmd IN LISTS commands)
  add_custom_command(
          TARGET create_boot_image POST_BUILD
          COMMAND sh -c ${cmd}
  )
endforeach()