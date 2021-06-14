#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M1-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M1 \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little   \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


