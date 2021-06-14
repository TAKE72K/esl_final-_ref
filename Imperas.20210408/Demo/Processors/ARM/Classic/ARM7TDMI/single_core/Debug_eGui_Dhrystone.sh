#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM7TDMI-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM7TDMI \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


