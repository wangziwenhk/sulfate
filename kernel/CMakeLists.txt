set(KERNEL_DIR ${CMAKE_SOURCE_DIR}/kernel)

add_custom_command(
    OUTPUT head.s
    COMMAND ${CMAKE_C_COMPILER} -E head.S > head.s
    DEPENDS head.S
)

add_custom_command(
    OUTPUT head.o
    COMMAND as --64 -o head.o head.s
    DEPENDS head.s
    COMMENT "Assembling head.s to head.o"
)

add_custom_target(build_kernel_head ALL DEPENDS head.o)

add_library(main_obj OBJECT main.c)
target_compile_options(main_obj PRIVATE -mcmodel=large -fno-builtin -m64)

add_custom_command(
        OUTPUT system
        COMMAND ld -b elf64-x86-64 -o system head.o $<TARGET_OBJECTS:main_obj> -T ${KERNEL_DIR}/Kernel.lds
        DEPENDS head.o main_obj
        COMMENT "Linking head.o and main.o to create system"
)

# 将 system 转换为 kernel.bin
add_custom_command(
        OUTPUT kernel.bin
        COMMAND objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary system kernel.bin
        DEPENDS system
        COMMENT "Converting system to kernel.bin"
)

# 定义默认目标
add_custom_target(build_kernel ALL DEPENDS kernel.bin)