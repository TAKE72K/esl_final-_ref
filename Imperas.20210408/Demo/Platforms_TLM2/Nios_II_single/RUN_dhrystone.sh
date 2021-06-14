#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




Nios_II_single_tlm2.${IMPERAS_ARCH}.exe --program dhrystone.CS_NIOS2.elf  "$@"

