riscv_RV32IM_FreeRTOS

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show the FreeRTOS operating system can be used on the
OVP RISC-V processor model.

The simulation executables were compiled using 
MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# FreeRTOS Operating System
###############################################################################
This demo is executing a version of FreeRTOS ported to the RISC-V processor.

The source used is available to download from github

    https://github.com/RISCV-on-Microsemi-FPGA/FreeRTOS.git

Clone the github repository or download and extract the zip file FreeRTOS-master.zip

Once extracted the FreeRTOS source can be found in the directory

    FreeRTOS-master/FreeRTOS_on_Mi-V_Processor/miv-rv32im-freertos-port-test

This can be built using the riscv cross compiler GCC riscv64-unknown-elf-gcc
which must be available on the PATH. This can be installed into a release using
one of the OVP RISC-V toolchain packages, for example riscv.toolchain

The source and pre-compiled elf file are provided in the FreeRTOS directory.

-- re-compilation

The FreeRTOS example application can be re-compiled in the FreeRTOS directory 
using the BUILD.sh script in a Linux shell or in an MSYS shell on Windows.

> cd FreeRTOS
> ./BUILD.sh

This will create an elf file miv-rv32im-freertos-port-test.elf in the directory 
FreeRTOS/Debug

###############################################################################
# Running the simulation
###############################################################################
The simulation is executed from one of the following directories:
  harness    : this executes the C API version of the virtual platform
  harnessTLM : this executes a SystemC TLM version of the virtual platform

Launch the simulation platform by double clicking 'RUN_FreeRTOS.bat' in a Windows
explorer or execute the script 'RUN_FreeRTOS.sh' in a Linux shell or Windows MSYS
shell.

The simulation will start and a UART Console will be launched. 

The UART Console will print messages from the FreeRTOS kernel and tasks.

The simulation will continue indefinitely but can be terminated by closing the
UART console.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Module and TLM Platform
###############################################################################

Platform ----------------------------------------------------------------------

The platform instantiates a RISC-V model (OVP riscv model configured 
as variant RVB32I with extensions M and SU) and peripheral models providing
UART and interrupt controller.

###############################################################################
# Re-Building Platform
###############################################################################
         
In order to rebuild, a full product install must have been carried out. This may
be the OVP 'OVPsim' package or either of the Imperas Professional Tools M*SDK 
or M*DEV 'Imperas' packages.
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installers are Imperas_SDK.<major version>.<minor version>.<OS>.exe
and Imperas_DEV.<major version>.<minor version>.<OS>.exe

Module ----------------------------------------------------------------------

The module contains the hardware definition and is found in the 'module' 
directory in this demo.
This is a copy of the module definition that is contained in the VLNV library 
at VLNV microsemi.ovpworld.org/module/ex1/1.0

Building of the module is carried out using the standard Makefile provided in 
either a Linux or an MSYS/MinGW shell.

For Example to re-build the module, the following can be used

> make -C module NOVLNV=1
or
> cd module
> make NOVLNV=1

TLM Platform  ----------------------------------------------------------------

The TLM platform includes the module definition of the hardware definition and
also the standard command line parser to generate an executable. It is found
in the 'harnessTLM' directory in this demo.

Building of the TLM platform is carried out using the standard Makefile provided
in either a Linux or an MSYS/MinGW shell.

For Example to re-build the TLM platform, the following can be used

> make -C harnessTLM NOVLNV=1
or
> cd harnessTLM
> make NOVLNV=1
