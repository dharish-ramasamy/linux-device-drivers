savedcmd_math.mod := printf '%s\n'   math.o | awk '!x[$$0]++ { print("./"$$0) }' > math.mod
