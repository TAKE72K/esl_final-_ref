#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.IMG_MIPS32R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant P5600 \
    --numprocessors 1 --addressbits 37    \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 10

