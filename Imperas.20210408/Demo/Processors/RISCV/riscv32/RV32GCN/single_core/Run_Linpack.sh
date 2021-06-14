#!/bin/bash
# Run_Linpack.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.RISCV32GC-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV32GCN \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1 --override iss/cpu0/mstatus_FS=1    \
    "$@" \
    -argv 11

