#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.V850-O3-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2 \
    --numprocessors 1     \
    "$@" \
    -argv 39

