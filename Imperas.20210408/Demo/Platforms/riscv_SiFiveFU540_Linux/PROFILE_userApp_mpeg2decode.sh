#!/bin/bash

BBL=Linux/bbl
VMLINUX=Linux/vmlinux
DTB=Linux/FU540.dtb
DRIVE=mpeg2decode/mpeg2decode.img

# Check Installation supports this demo
checkinstall.exe -group vap -p install.pkg --nobanner || exit

PLATFORM=${IMPERAS_VLNV}/imperas.ovpworld.org/platform/SiFiveFU540/1.0/platform.${IMPERAS_ARCH}.exe

${PLATFORM} --bblelf ${BBL} --dtb ${DTB} --diskimage ${DRIVE} \
    \
    --verbose \
    --excludem RISCV_IHPMU \
    --output FU540.log \
    \
    --enabletools \
    --extlib SiFiveFU540/U54=linux64OsHelper \
    --override SiFiveFU540/U54/enableSMPTools=1 \
    --symbolfile ${VMLINUX} \
    --mpdconsole \
    --batch mpeg2decode/functionprofile.batch \
    \
    --wallclockfactor 10 \
    \
    "$@"

    
egui.exe -open SiFiveFU540_U54_hart1.iprof
