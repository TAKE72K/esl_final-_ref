#!/bin/bash
# Debug_eGui_Dhrystone.sh
# Check Installation supports this demo
if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/checkinstall.exe --group debug --noruntime -p install.pkg --nobanner || exit
fi
${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_MIPS32R2-O0-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant P5600 \
    --numprocessors 1 --addressbits 37    \
    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"


