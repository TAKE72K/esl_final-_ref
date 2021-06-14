#!/bin/bash
# Debug_GDB_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32_r1r5 --variant interAptiv \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"


