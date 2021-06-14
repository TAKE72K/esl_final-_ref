#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.AARCH64-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 200

