#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




arm_aarch64_single_tlm2.${IMPERAS_ARCH}.exe --program peakSpeed2.AARCH64.elf  "$@"
