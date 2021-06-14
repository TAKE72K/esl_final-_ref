#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant P5600 \
    --numprocessors 24 --addressbits 37    \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@" \
    -argv 500000

