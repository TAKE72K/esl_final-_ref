#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

DRIVE=../Linux/busybear-linux/busybear.bin
BBL=../Linux/riscv-pk/build/bbl
DTB=../Linux/virtio.dtb
VMLINUX=../Linux/riscv-linux/vmlinux

harness.exe  \
    --modulefile ../module/model.${IMPERAS_ARCH}.${IMPERAS_SHRSUF} \
    \
    --objfilenoentry  ${BBL} \
    \
    --override virtio/smartLoader/dtb=${DTB} \
    --override virtio/smartLoader/command=\"root=/dev/vda ro console=ttyS0\" \
    \
    --output imperas-virtio.log \
    --verbose \
    \
    --override virtio/uartTTY0/console=T \
    --override virtio/uartTTY0/outfile=uartTTY0.log \
    --override virtio/uartTTY0/finishOnDisconnect=T \
    --override virtio/uartTTY0/xchars=160 \
    --override virtio/uartTTY0/ychars=48 \
    \
    --override virtio/VBD0/VB_DRIVE=${DRIVE} \
    --override virtio/VBD0/VB_DRIVE_DELTA=T \
    \
    --wallclockfactor 3 \
    "$@"
