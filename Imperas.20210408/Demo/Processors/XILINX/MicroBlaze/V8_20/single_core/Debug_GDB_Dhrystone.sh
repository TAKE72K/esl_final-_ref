#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_20 \
    --numprocessors 1     \
    --parameter endian=big    \
    --gdbconsole --gdbinit dhrystone_microblaze.gdb \
    "$@"


