#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




manycore24_arc_tlm2.${IMPERAS_ARCH}.exe --program peakSpeed2.ARC700.elf  "$@"
