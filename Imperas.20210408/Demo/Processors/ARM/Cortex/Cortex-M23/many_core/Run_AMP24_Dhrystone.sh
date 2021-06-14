#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M1-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M23 \
    --numprocessors 24     \
    --parameter UAL=1 --parameter endian=little   \
    "$@" \
    -argv 500000

