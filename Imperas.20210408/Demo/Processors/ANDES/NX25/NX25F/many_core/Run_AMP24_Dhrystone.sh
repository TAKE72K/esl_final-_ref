#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64-O0-g.elf \
    --processorvendor andes.ovpworld.org --processorname riscv --variant NX25F \
    --numprocessors 24 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 800000

