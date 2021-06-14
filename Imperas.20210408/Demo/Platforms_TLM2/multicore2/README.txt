multicore2_mips32_tlm2

###############################################################################
# Platform
###############################################################################
This platform will show how to make use of the TLM2.0 wrapper layers provided by 
OVP to enable the use of high performance OVP processor and peripheral models
in a SystemC TLM2.0 platform environment.
A platform containing two multicore2 processor instances, and a memory map that 
provides both shared and local memory.
All memory is shared except for a region of local memory used for the processor 
stack and heap, this cannot be shared.


###############################################################################
# Re-Building
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or the Imperas Professional Tools M*SDK 'Imperas' 
package. 
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installer is Imperas.<major version>.<minor version>.<OS>.exe


The simulation platform multicore2_mips32_tlm2.<OS>.exe was compiled using MinGW 
under Windows, and GCC under Linux.

The compilation can be performed using the following command line

>make -f IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform \
         SRC=multicore2_mips32_tlm2.cpp

The common Makefiles include environment information for the location of the 
SYSTEMC installation.

These must be correctly modified for your installation

    For example:

    # MINGW WINDOWS Configuration
    
    # Set this to your System C installation
    SYSTEMC  = C:\SystemC\Windows\systemc-2.3.0
    
    # Linux Configuration
    
    # Set this to your SystemC installation
    SYSTEMC  = /home/SystemC/Linux/systemc-2.3.0

###############################################################################
# SystemC platform does not support Control-C termination
###############################################################################
The SystemC platform does not allow the simulation to be terminated by the use 
of Control-C. 
The simulation can be terminated by, either:
1. On a Windows host, closing the shell
2. On a Linux host, background the job and then terminate.  
