#!/bin/bash
# Run_MultiCore2.sh

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_M4F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M4F \
    --numprocessors 2 --hishare 0x000fffff --loshare 0x0   \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@"


