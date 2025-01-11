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
        DEPENDS ${asm_file} ${BOOT_DIR}/fat12.inc
        COMMENT "Assembling ${asm_file} to ${bin_file}"
    )
    
    list(APPEND BIN_FILES ${bin_file})
endforeach()

# 编译 bootloader
add_custom_target(build_bootloader ALL DEPENDS ${BIN_FILES})

# 创建 boot.img
set(BOOT_IMAGE ${CMAKE_BINARY_DIR}/boot.img)

add_custom_command(
    OUTPUT ${BOOT_IMAGE}
    COMMAND ${CMAKE_COMMAND} -E echo "Creating 1.44MB floppy image..."
    COMMAND dd if=/dev/zero of=${BOOT_IMAGE} bs=512 count=2880
    DEPENDS ${BOOT_DIR}/boot.asm ${BOOT_DIR}/loader.asm
    COMMENT "Generating boot.img using dd"
    VERBATIM
)

add_custom_target(create_boot_image ALL
    DEPENDS ${BOOT_IMAGE}
)

add_custom_command(
    TARGET create_boot_image POST_BUILD
    COMMAND dd if=${CMAKE_BINARY_DIR}/boot.bin of=${BOOT_IMAGE} bs=512 count=1 conv=notrunc
    COMMENT "Writing bootloader to floppy.img"
)
