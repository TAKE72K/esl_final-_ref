#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.CS_NIOS2-O1-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
    --numprocessors 2 --hishare 0x100fffff --loshare 0x00000000   \
    --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   \
    "$@"


