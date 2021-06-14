#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.POWERPC32-O1-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
    --numprocessors 2 --hishare 0x100fffff --loshare 0x000fffff   \
    --parameter endian=big    \
    "$@"


