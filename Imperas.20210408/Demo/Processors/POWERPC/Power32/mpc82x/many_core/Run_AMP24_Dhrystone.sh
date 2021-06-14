#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x \
    --numprocessors 24     \
    --parameter endian=big    \
    "$@" \
    -argv 500000

