# 配置 bootloader 相关的路径

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

# 注册将 boot.bin 写入 boot.img 的 POST_BUILD 命令
register_boot_image_post_build("dd if=${CMAKE_BINARY_DIR}/boot.bin of=${BOOT_IMAGE} bs=512 count=1 conv=notrunc")

# 注册将 loader.bin 拷贝到 boot.img 的 POST_BUILD 命令
register_boot_image_post_build("mcopy -o -i ${BOOT_IMAGE} ${CMAKE_BINARY_DIR}/loader.bin ::/")