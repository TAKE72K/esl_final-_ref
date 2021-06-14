#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




arm_single_tlm2.${IMPERAS_ARCH}.exe --program fibonacci.ARM_CORTEX_A.elf  "$@"
