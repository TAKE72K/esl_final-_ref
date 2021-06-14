#!/bin/bash
# Run_Fibonacci.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.ARC600-O3-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --numprocessors 1     \
    --parameter opt-rf16=0    \
    "$@" \
    -argv 39

