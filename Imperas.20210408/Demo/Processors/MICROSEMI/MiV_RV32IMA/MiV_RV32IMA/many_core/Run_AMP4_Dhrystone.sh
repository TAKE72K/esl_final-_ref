#!/bin/bash
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor microsemi.ovpworld.org --processorname riscv --variant MiV_RV32IMA \
    --numprocessors 4     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 3000000

