#!/bin/bash
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O1-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F \
    --numprocessors 4     \
    --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   \
    --parallel  \
    "$@" \
    -argv 4000000

