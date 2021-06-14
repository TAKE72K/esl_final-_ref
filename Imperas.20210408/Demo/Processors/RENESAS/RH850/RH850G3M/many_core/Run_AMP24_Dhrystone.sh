#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RH850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rh850 --variant RH850G3M \
    --numprocessors 24     \
    "$@" \
    -argv 500000

