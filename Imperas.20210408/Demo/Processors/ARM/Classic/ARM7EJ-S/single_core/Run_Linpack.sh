#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.ARM7TDMI-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM7EJ-S \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 11

