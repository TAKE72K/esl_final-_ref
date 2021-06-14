#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.AARCH32-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch32 \
    --numprocessors 2 --hishare 0x801fffff --loshare 0x80008000   \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@"


