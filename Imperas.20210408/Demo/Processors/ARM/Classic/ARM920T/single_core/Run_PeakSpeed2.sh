#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARM9T-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM920T \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 500000000

