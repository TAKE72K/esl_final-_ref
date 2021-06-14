#!/bin/bash
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2LE-O2-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant ISA \
    --numprocessors 4     \
    --parameter endian=little    \
    "$@" \
    -argv 1000000

