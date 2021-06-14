#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit




v850_single_tlm2.${IMPERAS_ARCH}.exe --program dhrystone.V850.elf  "$@"

