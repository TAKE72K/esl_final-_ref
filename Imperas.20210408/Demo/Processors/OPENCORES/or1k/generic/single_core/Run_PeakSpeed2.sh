#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.OR1K-O0-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 1     \
    "$@" \
    -argv 300000000

