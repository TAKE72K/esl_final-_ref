#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




arc_single_tlm2.${IMPERAS_ARCH}.exe --program fibonacci.ARC700.elf  "$@"
