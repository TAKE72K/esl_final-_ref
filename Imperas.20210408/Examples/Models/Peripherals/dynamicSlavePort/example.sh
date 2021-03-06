#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=ARM7TDMI

# compile the design
make -C module     NOVLNV=1

# compile the peripheral (used in design)
make -C peripheral NOVLNV=1

# compile the app
make -C application CROSS=${CROSS}

# run the module
harness.exe \
         --modulefile module/model.${IMPERAS_SHRSUF} \
         --program application/application.${CROSS}.elf \
         $@
