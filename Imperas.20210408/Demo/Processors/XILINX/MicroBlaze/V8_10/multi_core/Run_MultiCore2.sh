#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2_microblaze/multicore2_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_10 \
    --numprocessors 2 --hishare 0x000fffff --loshare 0x00000000   \
    --parameter endian=big    \
    "$@"


