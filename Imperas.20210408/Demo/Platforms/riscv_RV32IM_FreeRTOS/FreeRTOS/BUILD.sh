#!/bin/bash

if [ -z $IMPERAS_HOME ] || [ ! -d $IMPERAS_HOME/bin/$IMPERAS_ARCH ]; then
  echo "IMPERAS_HOME not set of not valid. Please setup Imperas Environment"
else

    toolchain=$(riscv64-unknown-elf-gcc --version)
    declare -i rc=$?
    if [ $rc -ne 0 ]; then
        echo "Cannot find cross compiler riscv64-unknown-elf-gcc, please ensure Microsemi cross compiler is installed and added to PATH"
    else

        TARGET=$1
        shift
    
        if [ ! -z $TARGET ] && [ $TARGET != "clean" ] && [ $TARGET != "all" ]; then
            echo "Use no argument or 'clean' or 'all'"
        else
            pushd Debug
                make -f makefile $TARGET
                rc=$?
            popd
        fi
    fi
fi

exit $rc

