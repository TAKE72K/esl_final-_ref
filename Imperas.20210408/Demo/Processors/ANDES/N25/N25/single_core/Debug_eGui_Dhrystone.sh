#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor andes.ovpworld.org --processorname riscv --variant N25 \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


