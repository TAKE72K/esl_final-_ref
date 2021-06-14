#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.NANOMIPS32R6LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant I7200 \
    --numprocessors 1     \
    "$@" \
    -argv 100000000

