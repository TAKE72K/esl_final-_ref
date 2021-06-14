#!/bin/bash
# Run_AMP4_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64-O0-g.elf \
    --processorvendor sifive.ovpworld.org --processorname riscv --variant U74 \
    --numprocessors 4 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 4000000

