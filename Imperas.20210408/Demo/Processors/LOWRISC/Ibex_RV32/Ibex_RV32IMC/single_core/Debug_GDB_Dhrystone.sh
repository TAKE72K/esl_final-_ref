#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor lowrisc.ovpworld.org --processorname riscv --variant Ibex_RV32IMC \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


