#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.ARM_CORTEX_A-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A9UP \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 39

