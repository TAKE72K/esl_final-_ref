#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.IMG_MIPS32R2-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant interAptiv \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 500000000

