savedcmd_add.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T /usr/src/linux-headers-6.14.0-33-generic/scripts/module.lds -o add.ko add.o add.mod.o .module-common.o
