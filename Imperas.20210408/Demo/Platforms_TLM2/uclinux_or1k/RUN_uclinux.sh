#!/bin/bash

# Check Installation supports this demo
checkinstall.exe -p install.pkg --nobanner || exit


uclinux_or1k_tlm2.${IMPERAS_ARCH}.exe
