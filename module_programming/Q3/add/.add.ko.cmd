savedcmd_add.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T /home/desd/linux-6.17.9/scripts/module.lds -o add.ko add.o add.mod.o .module-common.o
