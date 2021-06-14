#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M4F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M4F \
    --numprocessors 24     \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@" \
    -argv 500000

