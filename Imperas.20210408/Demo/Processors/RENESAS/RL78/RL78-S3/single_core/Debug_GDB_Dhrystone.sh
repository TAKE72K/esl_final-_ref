#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_rl78/dhrystone_rl78.RL78-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rl78 --variant RL78-S3 \
    --numprocessors 1     \
    --gdbconsole --gdbinit dhrystone_rl78.gdb \
    "$@"


