#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




or1k_single_tlm2.${IMPERAS_ARCH}.exe --program peakSpeed2.OR1K.elf  "$@"
