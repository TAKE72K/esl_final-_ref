#!/bin/bash
# Run_AMP24_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64-O0-g.elf \
    --processorvendor sifive.ovpworld.org --processorname riscv --variant S21 \
    --numprocessors 24 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 800000

