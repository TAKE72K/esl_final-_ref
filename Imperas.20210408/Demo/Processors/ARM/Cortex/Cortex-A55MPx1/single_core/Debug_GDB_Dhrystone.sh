#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.AARCH64-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A55MPx1 \
    --numprocessors 1     \
    --parameter endian=little    \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


