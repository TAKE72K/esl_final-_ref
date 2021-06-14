#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_M4F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M4F \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@" \
    -argv 300000000

