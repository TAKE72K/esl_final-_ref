#!/bin/bash
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O3-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
    --numprocessors 1     \
    --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   \
    "$@" \
    -argv 6000000

