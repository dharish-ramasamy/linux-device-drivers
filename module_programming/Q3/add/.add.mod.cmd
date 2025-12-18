savedcmd_add.mod := printf '%s\n'   add.o | awk '!x[$$0]++ { print("./"$$0) }' > add.mod
