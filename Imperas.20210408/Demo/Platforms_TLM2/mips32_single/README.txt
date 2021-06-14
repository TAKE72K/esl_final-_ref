mips32_single_tlm2

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show how to construct a platform containing a single mips32
processor instance, and a memory map ranging from #00000000 to #FFFFFFFF.
This platform can then be used to execute pre-compiled applications; the 
following may be available (actual applications available are demo dependent)
  - dhrystone.IMG_MIPS32R2LE.elf
  - linpack.IMG_MIPS32R2LE.elf
  - fibonacci.IMG_MIPS32R2LE.elf
  - peakSpeed2.IMG_MIPS32R2LE.elf
  
After each application has executed, a simulation summary will be printed,
indicating the number of instructions executed, and the performance of the
simulation in terms of Millions of simulated Instructions executed Per
Second (MIPS)

The simulation harness mips32_single_tlm2.<OS>.exe was compiled 
using MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation
###############################################################################

# 1. from a Microsoft window manager or Linux shell

Launch the platform with a pre-compiled application; in Windows by double 
clicking one of the batch files (.bat) or in Linux by executing one of the shell 
scripts (.sh)

The scripts will be available dependent upon the applications available:
    RUN_dhrystone.bat|sh, 
    RUN_linpack.bat|sh, 
    RUN_fibonacci.bat|sh or 
    RUN_peakSpeed2.bat|sh 

  
The simulation will run and print statistics upon completion

# 2. from the command line

If running a DOS command window, or a mingw / cygwin shell, simply change
directory to the demo directory, then type the name of the executable
giving the name of a compiled application as an argument, e.g.

cmd > mips32_single_tlm2.<OS>.exe --program fibonacci.IMG_MIPS32R2LE.elf

The simulation will run and print statistics upon completion

###############################################################################
# Interpreting results
###############################################################################
At the end of simulation, a number of statistics will be printed.
Amongst the statistical information which is reported, are the number
of 'Simulated instructions' and the 'Simulated MIPS'.
The 'Simulated instructions' will vary depending upon the application being
executed, this count indicates the number of simulated processor
instructions for the processors in the platform.
The 'Simulated MIPS' will be a measure of the number of 'Simulated
instructions' over the host elapsed time.
The simulation must run for around 1 second of simulated time in order to print 
simulated MIPS statistics

###############################################################################
# Re-Building
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or the Imperas Professional Tools M*SDK 'Imperas' 
package. 
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installer is Imperas.<major version>.<minor version>.<OS>.exe

A processor cross compiler toolchain package must be installed to allow the 
applications to be rebuilt. This may be available from OVP as the package 
mips32.toolchain.<major version>.<minor version>.<OS>.exe or an external 
toolchain to support IMG_MIPS32R2LE. Please check the requirements.


A Makefile is supplied that will perform the rebuilding of the platform 
executable, mips32_single_tlm2.<OS>.exe, and the application ELF files, 
file.IMG_MIPS32R2LE.elf.

Application
--------------------------------------------------------------------------------
The applications were built using a Cross Compiler toolchain, that may be 
available from the OVPworld website, which includes a <CROSS>.makefile.include
that is used to setup an basic build environment for that toolchain. This can 
be modified to use alternative compiler flags.

Platform
--------------------------------------------------------------------------------
The simulation platform mips32_single_tlm2.<OS>.exe was compiled using MSYS/MinGW 
under Windows, and GCC under Linux.

The compilation can be performed using the following command lines

Windows
This requires an MSYS environment setup
>make -f %IMPERAS_HOME%/ImperasLib/buildutils/Makefile.platform ^
          SRC=mips32_single_tlm2.c ^
          NOVLNV=1
    
Linux

>make -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.platform \
         SRC=mips32_single_tlm2.c \
         NOVLNV=1

