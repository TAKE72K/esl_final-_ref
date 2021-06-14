#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --numprocessors 1     \
    --parameter opt-rf16=0    \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


