#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.IMG_MIPS32R2-O3-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant proAptiv \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 39

