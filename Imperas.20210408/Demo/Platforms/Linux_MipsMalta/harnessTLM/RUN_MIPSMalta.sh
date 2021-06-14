#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

platform.${IMPERAS_ARCH}.exe \
        \
        --verbose --output imperas.log \
        \
        --variant 34Kc \
        \
        --objfilenoentry ../Linux/vmlinux \
        --override MipsMalta.Core_Board_SDRAM_promInit/kernel=../Linux/vmlinux.nocal   \
        --override MipsMalta.Core_Board_SDRAM_promInit/initrd=../Linux/initrd.gz \
        --override MipsMalta.Core_Board_SDRAM_promInit/command="console=tty0" \
        \
        --override MipsMalta.uartTTY0/console=1 \
        \
        --override MipsMalta.maltaFpga/stoponsoftreset=1 \
        "$@"
        