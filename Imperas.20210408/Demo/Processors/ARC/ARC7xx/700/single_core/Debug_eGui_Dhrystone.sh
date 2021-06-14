#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARC700-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
    --numprocessors 1     \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


