#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_20 \
    --numprocessors 1     \
    --parameter endian=big    \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


