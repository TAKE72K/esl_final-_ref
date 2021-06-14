#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




mips64_single_tlm2.${IMPERAS_ARCH}.exe --program dhrystone.IMG_MIPS64R2.elf  "$@"

