savedcmd_avg.mod := printf '%s\n'   avg.o | awk '!x[$$0]++ { print("./"$$0) }' > avg.mod
