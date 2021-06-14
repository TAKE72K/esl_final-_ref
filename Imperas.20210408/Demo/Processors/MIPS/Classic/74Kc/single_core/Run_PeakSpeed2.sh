#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.IMG_MIPS32R2LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant 74Kc \
    --numprocessors 1     \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 100000000

