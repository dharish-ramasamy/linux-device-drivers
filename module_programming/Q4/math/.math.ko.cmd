savedcmd_math.ko := ld -r -m elf_x86_64 -z noexecstack --no-warn-rwx-segments --build-id=sha1  -T /home/desd/linux-6.17.9/scripts/module.lds -o math.ko math.o math.mod.o .module-common.o
