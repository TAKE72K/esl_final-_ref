microblaze_single_tlm2

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show how to make use of the TLM2.0 wrapper layers provided by 
OVP to enable the use of high performance OVP processor and peripheral models
in a SystemC TLM2.0 platform environment.
A platform is constructed containing a single MICROBLAZE processor instance, and a 
memory map with separate program memory and stack memory.

This platform can then be used to execute pre-compiled applications; the 
following may be available (actual applications available are demo dependent)
  - dhrystone.MICROBLAZE.elf
  - linpack.MICROBLAZE.elf
  - fibonacci.MICROBLAZE.elf
  - peakSpeed2.MICROBLAZE.elf
  
After each application has executed, a simulation summary will be printed,
indicating the number of instructions executed, and the performance of the
simulation in terms of Millions of simulated Instructions executed Per
Second (MIPS)

The simulation harness microblaze_single_tlm2.<OS>.exe was compiled 
using MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation
###############################################################################

# 1.  from a Microsoft window manager or Linux shell

Launch the platform with a pre-compiled application; in Windows by double 
clicking one of the batch files (.bat) or in Linux by executing one of the shell 
scripts (.sh)

The scripts will be available dependent upon the applications available:
    RUN_dhrystone.bat|sh, 
    RUN_linpack.bat|sh, 
    RUN_fibonacci.bat|sh or 
    RUN_peakSpeed2.bat|sh 

  
The simulation will run and print statistics upon completion

# 2.from the command line

If running a DOS command window, or a mingw / cygwin shell, simply change
directory to the demo directory, then type the name of the executable
giving the name of a compiled application as an argument, e.g.

cmd > microblaze_single_tlm2.<OS>.exe --program linpack.MICROBLAZE.elf

The simulation will run and print statistics upon completion

###############################################################################
# 3. Interpreting results
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
# 4. Re-Building
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or the Imperas Professional Tools M*SDK 'Imperas' 
package. 
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installer is Imperas.<major version>.<minor version>.<OS>.exe


The simulation platform microblaze_single_tlm2.<OS>.exe was compiled using MinGW/MSYS 
under Windows, and GCC under Linux.

The compilation can be performed using the following command line

>make -f IMPERAS_HOME/ImperasLib/buildutils/Makefile.TLM.platform \
         SRC=microblaze_single_tlm2.cpp

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


###############################################################################
# 5. SystemC platform does not support Control-C termination
###############################################################################
The SystemC platform does not allow the simulation to be terminated by the use 
of Control-C. 
The simulation can be terminated by, either:
1. On a Windows host, closing the shell
2. On a Linux host, background the job and then terminate.  
