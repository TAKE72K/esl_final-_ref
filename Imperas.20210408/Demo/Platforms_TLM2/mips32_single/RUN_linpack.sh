#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




mips32_single_tlm2.${IMPERAS_ARCH}.exe --program linpack.IMG_MIPS32R2LE.elf  "$@"

