#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

platform.${IMPERAS_ARCH}.exe \
       \
       --output imperas.log --verbose \
       \
       --override ArmIntegratorCP.smartLoader/kernel=../Linux/zImage-CA9 \
       --override ArmIntegratorCP.smartLoader/initrd=../Linux/fs.img \
       \
       --override ArmIntegratorCP.uart1/console=1 \
       --override ArmIntegratorCP.lcd/noGraphics=1 \
       \
       "$@"
