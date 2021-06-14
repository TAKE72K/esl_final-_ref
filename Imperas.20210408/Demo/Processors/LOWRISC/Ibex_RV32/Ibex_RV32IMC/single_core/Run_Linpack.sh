#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.RISCV32-O0-g.elf \
    --processorvendor lowrisc.ovpworld.org --processorname riscv --variant Ibex_RV32IMC \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 11

