#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.RISCV64-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV64IMC \
    --numprocessors 1 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 39

