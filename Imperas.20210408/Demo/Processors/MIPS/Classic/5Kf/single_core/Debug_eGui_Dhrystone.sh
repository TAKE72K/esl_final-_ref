#!/bin/bash
# Debug_eGui_Dhrystone.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS64R2-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips64_r1r5 --variant 5Kf \
    --numprocessors 1     \
    --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org  \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


