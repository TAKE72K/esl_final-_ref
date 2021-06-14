#!/bin/bash
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M7F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M7F \
    --numprocessors 4     \
    --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    --parallel  \
    "$@" \
    -argv 4000000

