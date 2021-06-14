#!/bin/bash
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM9E-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM966E \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 6000000
