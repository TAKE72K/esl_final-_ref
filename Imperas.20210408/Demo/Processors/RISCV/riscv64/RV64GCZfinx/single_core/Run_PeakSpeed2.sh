#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.RISCV64GC-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV64GCZfinx \
    --numprocessors 1 --addressbits 37    \
    --override iss/cpu0/verbose=1 --override iss/cpu0/mstatus_FS=1    \
    "$@" \
    -argv 500000000

