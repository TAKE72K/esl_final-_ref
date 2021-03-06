#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.IMG_MIPS64R2-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64_r1r5 --variant 5Kc \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 39

