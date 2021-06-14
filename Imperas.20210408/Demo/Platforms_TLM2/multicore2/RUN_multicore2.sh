#!/bin/bash

# Check Installation supports this demo
checkinstall.exe  -p install.pkg   --nobanner || exit



multicore2_mips32_tlm2.${IMPERAS_ARCH}.exe --program top.cpu1=multicore2_reader.IMG_MIPS32R2LE.elf --program top.cpu2=multicore2_writer.IMG_MIPS32R2LE.elf  "$@"

