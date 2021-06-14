#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.AARCH64-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A53MPx1 \
    --numprocessors 2 --hishare 0x800FFFFF --loshare 0x80000000   \
    --parameter endian=little    \
    "$@"


