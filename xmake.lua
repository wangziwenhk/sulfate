set_project("sulfate")

add_rules("mode.debug", "mode.release")
add_requires("llvm")

set_arch("x86_64")
set_optimize("fastest")

set_policy("run.autobuild", true)
set_policy("check.auto_ignore_flags", false)

add_cxflags("-target x86_64-freestanding")
add_ldflags("-target x86_64-freestanding")

add_cxflags("-mno-80387", "-mno-mmx", "-mno-sse", "-mno-sse2", "-msoft-float","-nostdinc")
add_cxflags("-mcmodel=kernel")
add_ldflags("-static","-nostdlib")

add_cxflags("-mno-red-zone", "-fno-exceptions", "-fno-rtti","-m64")

target("kernel")
    set_kind("binary")
    set_languages("c++20")
    set_toolchains("llvm")

    set_default(false)

    add_files("src/**.cpp")
    add_includedirs("include")

    add_ldflags("-T " .. os.scriptdir() .. "/assets/linker.ld", "-e kmain")

target("iso")
    set_kind("phony")
    add_deps("kernel")
    set_default(true)

    on_build(function (target)
        import("core.project.project")

        local iso_dir = "$(buildir)/iso"
        os.cp("assets/limine/*", iso_dir .. "/limine/")

        local target = project.target("kernel")
        os.cp(target:targetfile(), iso_dir .. "/kernel.elf")

        local iso_file = "$(buildir)/sulfate.iso"
        os.run("xorriso -as mkisofs -efi-boot-part --efi-boot-image --protective-msdos-label " ..
                "-no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus "..
                "-R -r -J -apm-block-size 2048 "..
                "--efi-boot limine/limine-uefi-cd.bin "..
                "%s -o %s", iso_dir, iso_file)
        print("ISO image created at: %s", iso_file)
    end)

    on_run(function (target)
        import("core.project.config")

        local flags = {
            "-M", "q35",
            "-cpu", "qemu64,+x2apic",
            "-smp", "4",
            "-drive", "if=pflash,format=raw,file=assets/ovmf-code.fd",
            "-cdrom", config.buildir() .. "/sulfate.iso"
        }

        os.runv("qemu-system-x86_64", flags)
    end)
