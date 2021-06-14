#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




powerpc32_single_tlm2.${IMPERAS_ARCH}.exe --program peakSpeed2.POWERPC32.elf  "$@"
