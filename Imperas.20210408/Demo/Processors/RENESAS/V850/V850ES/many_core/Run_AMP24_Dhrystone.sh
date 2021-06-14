#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.V850-O3-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850ES \
    --numprocessors 24     \
    "$@" \
    -argv 800000

