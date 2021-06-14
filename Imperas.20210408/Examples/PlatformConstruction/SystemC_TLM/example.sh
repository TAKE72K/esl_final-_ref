#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

# build TLM Archive locally
make -C platform_cpp IMPERAS_TLM_SUPPORT_ARCHIVE=$(pwd)/tlmSupport/tlm.a

# re-build OP C++ library
# if re-building OP C++ Library, add IMPERAS_OP_CPP_LIBRARY to make command line and add to LD_LIBRARY_PATH
#                             IMPERAS_OP_CPP_LIBRARY=$(pwd)/opLib/libOP++.${IMPERAS_SHRSUF}
# LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(pwd)/opLib


# set this variable to trace TLM transactions
# export IMPERAS_TLM_CPU_TRACE=0

platform_cpp/platform.${IMPERAS_ARCH}.exe -program application/int.${CROSS}.elf $@
if [ $? -ne 0 ]; then
  echo "*** NOTE ***"
  echo "Please ensure that the Platform CPP file, the TLM Archive and the OP CPP Library are all built with the same version of Compiler/Linker as used for SystemC library"
fi
