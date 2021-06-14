#!/bin/bash

# Check Installation supports the base requirements for this example
checkinstall.exe -p install.pkg --nobanner || exit

APP=freertos-V5/Demo/V5/riscv64.Demo.elf

MODULE=AE350

harness.exe \
  \
  --modulevendor  andes.ovpworld.org \
  --modulelibrary module \
  --modulename    ${MODULE} \
  --moduleversion 1.0 \
  \
  --override AE350/cpu0/variant=NX25 \
  \
  --objfilenoentry  ${MODULE}/cpu0=${APP} \
  \
  --override AE350/UART2/outfile=uart.log \
  \
  --override AE350/cpu0/andesExtensions/micm_cfg=0x140 \
  --override AE350/cpu0/andesExtensions/mdcm_cfg=0x140 \
  \
  --verbose \
  --output imperas.log \
  "$@"
