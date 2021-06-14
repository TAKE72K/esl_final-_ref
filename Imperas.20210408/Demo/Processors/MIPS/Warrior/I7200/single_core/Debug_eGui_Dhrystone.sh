#!/bin/bash
# Debug_eGui_Dhrystone.sh
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group debug --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.NANOMIPS32R6LE-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant I7200 \
    --numprocessors 1     \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


