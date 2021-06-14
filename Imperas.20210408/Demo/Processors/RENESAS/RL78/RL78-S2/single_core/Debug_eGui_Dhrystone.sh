#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_rl78/dhrystone_rl78.RL78-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rl78 --variant RL78-S2 \
    --numprocessors 1     \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


