#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.OR1K-O3-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 24     \
    "$@" \
    -argv 800000

