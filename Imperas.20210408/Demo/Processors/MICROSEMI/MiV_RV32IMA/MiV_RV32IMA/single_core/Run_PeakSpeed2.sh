#!/bin/bash
# Run_PeakSpeed2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.RISCV32-O0-g.elf \
    --processorvendor microsemi.ovpworld.org --processorname riscv --variant MiV_RV32IMA \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 500000000

