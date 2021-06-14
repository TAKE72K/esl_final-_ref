#!/bin/bash
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_00 \
    --numprocessors 4     \
    --parameter endian=big    \
    "$@" \
    -argv 300000

