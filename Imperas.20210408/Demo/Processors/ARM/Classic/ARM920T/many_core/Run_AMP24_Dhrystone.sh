#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM9T-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM920T \
    --numprocessors 24     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 500000

