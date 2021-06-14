#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_M1-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M1 \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little   \
    "$@" \
    -argv 500000000

