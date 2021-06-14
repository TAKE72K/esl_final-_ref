#!/bin/bash
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.OR1K-O3-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 4     \
    "$@" \
    -argv 300000

