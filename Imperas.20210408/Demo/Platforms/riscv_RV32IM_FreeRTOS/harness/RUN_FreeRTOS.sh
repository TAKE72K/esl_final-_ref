#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit

FREERTOS_ELF=../FreeRTOS/Debug/miv-rv32im-freertos-port-test.elf
MODULE=RiscvRV32FreeRTOS

harness.exe \
  --modulefile ../module/model.${IMPERAS_ARCH}.${IMPERAS_SHRSUF} \
  \
  --program  ${MODULE}/cpu0=${FREERTOS_ELF} \
  --override ${MODULE}/uart0/console=T \
  --override ${MODULE}/uart0/finishOnDisconnect=T \
  --override ${MODULE}/uart0/outfile=uart0.log \
  \
  --verbose --output imperas.log \
  "$@"
