#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.V850-O0-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850 \
    --numprocessors 1     \
    "$@" \
    -argv 300000000

