#!/bin/bash

BBL=Linux/bbl
VMLINUX=Linux/vmlinux
DTB=Linux/FU540.dtb
DRIVE=Linux/benchmarks.img

# User applications
APPEXECUST=custom/custom_asm.exe
APPEXE=custom/custom_c.exe

if [ "$TRACE" = "1" ]; then
    TRACEARGS="--trace --tracechange --traceshowicount"
    CHECK=
fi

if [ "$VAP" = "1" ]; then
    VAPARGS="--enabletools --extlib SiFiveFU540/U54=linux64OsHelper --override SiFiveFU540/U54/enableSMPTools=1 --symbolfile ${VMLINUX}"
    CHECK="-group vap"
fi

if [ "$DEBUGAPP" = "1" ]; then
    DEBUGARGS="--batch app.idebug.mpd --mpdegui"
    CHECK="-group debug"
fi

if [ "$DEBUG" = "1" ]; then
    DEBUGARGS="--symbolfile ${VMLINUX} --batch vmlinux.idebug.mpd --mpdegui"
    CHECK="-group debug"
fi

if [ "$CUSTOM" = "1" ]; then
    CUSTOMARGS="--extlib SiFiveFU540/U54/custom=modelAttrs@interceptlib/model.${IMPERAS_ARCH}.${IMPERAS_SHRSUF}"
    CHECK="-group custom"
fi

# Check Installation supports this demo
checkinstall.exe ${CHECK} -p install.pkg --nobanner || exit

PLATFORM=${IMPERAS_VLNV}/imperas.ovpworld.org/platform/SiFiveFU540/1.0/platform.${IMPERAS_ARCH}.exe

${PLATFORM} --bblelf ${BBL} --dtb ${DTB} --diskimage ${DRIVE} \
    \
    --verbose \
    --excludem RISCV_IHPMU \
    --output FU540.log \
    \
    --wallclockfactor 10 \
    \
    ${TRACEARGS} \
    ${VAPARGS} \
    ${DEBUGARGS} \
    ${CUSTOMARGS} \
    \
    "$@"
