#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack_microblaze/linpack_microblaze.MICROBLAZE-O0-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_20 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 8

