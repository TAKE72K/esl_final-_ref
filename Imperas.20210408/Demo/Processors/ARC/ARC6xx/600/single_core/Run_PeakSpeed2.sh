#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARC600-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --numprocessors 1     \
    --parameter opt-rf16=0    \
    "$@" \
    -argv 500000000

