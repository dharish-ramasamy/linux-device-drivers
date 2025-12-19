savedcmd_calculate.mod := printf '%s\n'   calculate.o | awk '!x[$$0]++ { print("./"$$0) }' > calculate.mod
