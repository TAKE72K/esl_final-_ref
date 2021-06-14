#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM7TDMI-O1-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv6KZ \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


