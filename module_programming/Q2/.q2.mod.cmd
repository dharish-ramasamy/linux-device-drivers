savedcmd_q2.mod := printf '%s\n'   q2.o | awk '!x[$$0]++ { print("./"$$0) }' > q2.mod
