#!/bin/bash
# Run_QL_AMP4_Dhrystone.sh
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group run --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64GC-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV64GCK \
    --numprocessors 4 --addressbits 37    \
    --override iss/cpu0/verbose=1 --override iss/cpu0/mstatus_FS=1    \
    --parallel  \
    "$@" \
    -argv 4000000

