#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.AARCH64-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A75MPx1 \
    --numprocessors 1     \
    --parameter endian=little    \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


