#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.RISCV32-O0-g.elf \
    --processorvendor openhwgroup.ovpworld.org --processorname riscv --variant CV32E40P \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@"


