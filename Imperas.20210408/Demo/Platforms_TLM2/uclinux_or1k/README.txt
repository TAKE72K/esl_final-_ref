uclinux_or1k_tlm2

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show how to make use of the TLM2.0 wrapper layers provided by 
OVP to enable the use of high performance OVP processor and peripheral models
in a SystemC TLM2.0 platform environment.
The platform contains a single  processor instance, a uart peripheral, 
memory and an asynchronous interrupt between the peripheral and processor.
The platform memory map has two memory regions defined one below and one above 
the uart peripheral.
The platform is used to execute a pre-compiled version of ucLinux that can be 
interacted with using the native display and keyboard via the uart peripheral.

After the application has executed, a simulation summary will be printed,
indicating the number of instructions executed, and the performance of the
simulation in terms of Millions of simulated Instructions executed Per
Second (MIPS)

The simulation harness uclinux_or1k_tlm2.<OS>.exe was compiled 
using MinGW under Windows, and GCC under Linux.

###############################################################################
# Running the simulation harness from a script
###############################################################################
Simply launch the executable by double clicking 'RUN_uclinux.bat' or the 
program 'uclinux_or1k_tlm2.<OS>.exe' 

The simulation will now run and wait for a connection on a localhost port if 
the environment variable PORTNUM is set. If this was not set a console will 
automatically be started and a connection made.

The simulation will continue and ucLinux will boot to a command prompt. 
It is now possible to interact with ucLinux running on the  processor 
of the virtual platform. 

To complete the simulation type quit or exit at the console prompt.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Running the simulation harness from the command line
###############################################################################
If running a DOS command window, or a mingw / cygwin shell, simply change
directory to the demo directory, then type the name of the executable
at the shell prompt, e.g.
cmd > uclinux_or1k_tlm2.<OS>.exe

The simulation will now run and wait for a connection on a localhost port if 
the environment variable PORTNUM is set. If this was not set a console will 
automatically be started and a connection made.

The simulation will continue and ucLinux will boot to a command prompt. 
It is now possible to interact with ucLinux running on the  processor 
of the virtual platform. 

To complete the simulation type quit or exit at the console prompt.

Statistics will be printed upon completion of the simulation.

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
instructions' over the host elapsed time. Typically the 'Simulated MIPS' number
should be in the 100's of MIPS range.


###############################################################################
# Re-Building
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or the Imperas Professional Tools M*DEV 'Imperas_DEV'
or M*SDK 'Imperas_SDK' packages.

The installers are
  'OVPsim'            OVPsim.<major version>.<minor version>.<OS>.exe
  'Imperas_DEV'  Imperas_DEV.<major version>.<minor version>.<OS>.exe
  'Imperas_SDK'  Imperas_SDK.<major version>.<minor version>.<OS>.exe


The simulation platform uclinux_or1k_tlm2.<OS>.exe was compiled using MinGW/MSYS 
under Windows, and GCC under Linux.

The compilation can be performed using the following command line

>make -f IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform \
         SRC=uclinux_or1k_tlm2.cpp

The common Makefiles include environment information for the location of the 
SYSTEMC installation.

These must be correctly modified for your installation

    For example:

    # MinGW WINDOWS Configuration
    
    # Set this to your System C installation
    SYSTEMC  = C:\SystemC\Windows\systemc-2.3.0
    
    # Linux Configuration
    
    # Set this to your SystemC installation
    SYSTEMC  = /home/SystemC/Linux/systemc-2.3.0

