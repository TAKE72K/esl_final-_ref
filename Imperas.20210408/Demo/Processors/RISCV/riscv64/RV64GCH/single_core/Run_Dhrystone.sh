#!/bin/bash
# Run_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64GC-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV64GCH \
    --numprocessors 1 --addressbits 37    \
    --override iss/cpu0/verbose=1 --override iss/cpu0/mstatus_FS=1    \
    "$@" \
    -argv 4000000

