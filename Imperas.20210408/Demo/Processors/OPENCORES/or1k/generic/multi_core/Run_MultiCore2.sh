#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.OR1K-O1-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 2 --hishare 0xefffffff --loshare 0x00000000   \
    "$@"


