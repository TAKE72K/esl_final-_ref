#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci_microblaze/fibonacci_microblaze.MICROBLAZE-O3-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_00 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 39

