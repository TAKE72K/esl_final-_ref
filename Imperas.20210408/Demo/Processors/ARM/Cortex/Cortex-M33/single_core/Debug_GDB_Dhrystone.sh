#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M33 \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little   \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


