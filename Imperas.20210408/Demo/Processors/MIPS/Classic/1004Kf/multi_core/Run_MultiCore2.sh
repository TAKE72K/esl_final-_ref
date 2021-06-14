#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.IMG_MIPS32R2LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant 1004Kf \
    --numprocessors 2 --loshare 0x0002dd08 --hishare 0x0002dd0f   \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    "$@"


