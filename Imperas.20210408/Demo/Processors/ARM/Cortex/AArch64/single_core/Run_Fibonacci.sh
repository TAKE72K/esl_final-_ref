#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.AARCH64-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 39

