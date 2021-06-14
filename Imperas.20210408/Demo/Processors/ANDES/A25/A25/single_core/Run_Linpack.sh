#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.RISCV32-O0-g.elf \
    --processorvendor andes.ovpworld.org --processorname riscv --variant A25 \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 11

