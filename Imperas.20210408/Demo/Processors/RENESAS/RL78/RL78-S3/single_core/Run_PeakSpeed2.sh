#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed1_rl78/peakSpeed1_rl78.RL78-O1-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rl78 --variant RL78-S3 \
    --numprocessors 1     \
    "$@"


