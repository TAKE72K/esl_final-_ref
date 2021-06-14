#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M7F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M7F \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


