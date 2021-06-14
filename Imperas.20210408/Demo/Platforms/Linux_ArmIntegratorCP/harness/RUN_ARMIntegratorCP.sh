#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

harness.exe \
       --modulefile ../module/model.${IMPERAS_ARCH}.${IMPERAS_SHRSUF} \
       \
       --output imperas.log --verbose \
       \
       --override ArmIntegratorCP/smartLoader/kernel=../Linux/zImage-CA9 \
       --override ArmIntegratorCP/smartLoader/initrd=../Linux/fs.img \
       \
       --override ArmIntegratorCP/uart1/console=1 \
       \
       "$@"
