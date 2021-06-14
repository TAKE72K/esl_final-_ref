#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.AARCH64-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch64 \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 500000000

