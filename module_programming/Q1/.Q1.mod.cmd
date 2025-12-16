savedcmd_Q1.mod := printf '%s\n'   Q1.o | awk '!x[$$0]++ { print("./"$$0) }' > Q1.mod
