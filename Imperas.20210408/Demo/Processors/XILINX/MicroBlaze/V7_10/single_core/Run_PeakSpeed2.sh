#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2_microblaze/peakSpeed2_microblaze.MICROBLAZE-O0-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 300000000

