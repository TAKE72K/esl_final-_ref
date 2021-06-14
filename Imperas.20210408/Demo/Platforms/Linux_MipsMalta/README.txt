Linux_MipsMalta

###############################################################################
# Demo Platform
###############################################################################
This demo will show how to execute linux running on a MIPS32 processor on the 
Mips Malta virtual platform

The platform is used to execute a pre-compiled version of linux that can be 
interacted with using a virtualized model of a VGA interface, keyboard and 
mouse interfaces.

The simulation platform 
was compiled using MinGW/MSYS http://www.mingw.org under Windows, and 
GCC under Linux.

###############################################################################
# Running the simulation harness using a script provided
###############################################################################
The simulation is executed from one of the following directories:
  harness    : this executes the C API version of the virtual platform
  harnessTLM : this executes a SystemC TLM version of the virtual platform

Go to the required directory e.g. cd harness

Simply launch the executable using one of the script files, for example 
'RUN_MIPSMalta.sh', in either the harness or harnessTLM directories.

The simulation will start up (it may wait at the prompt in the interactive shell,
if it does use the 'isimulate' command to run the simulation). 

The simulation will boot Linux to a shell prompt. 

It is now possible to interact with Linux running on the MIPS32 processor of the 
virtual platform. 

To finish the simulation, simply close the VGA display (if used) or close the 
terminal connected to a UART (if used).

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
# Other Features of the Mips Malta Platform
###############################################################################

The Mips Malta platform supports connection to a virtualized ethernet connection
i.e. this allows interaction with an real ethernet link. This can be used with 
an alternative initrd ramdisk to download and install the full Debian linux 
installation.

The Mips Malta platform supports a TFTP connection to allow the easy transfer of 
files to and from the host file system.

For full information on these and other uses for the Mips Malta virtual platform
please visit http://www.ovpworld.org/library/wikka.php?wakka=Mips32MaltaLinux from 
which the document "OVP_MIPS_Linux_Platform_User_Guide.pdf" may be obtained.


###############################################################################
# Re-Building Module and TLM Platform
###############################################################################

In order to rebuild a full product install must have been carried out. This may
be the OVP 'OVPsim' package or either of the Imperas Professional Tools M*SDK 
or M*DEV 'Imperas' packages.
The 'OVPsim' installer is OVPsim.<major version>.<minor version>.<OS>.exe
The 'Imperas' installers are Imperas_SDK.<major version>.<minor version>.<OS>.exe
and Imperas_DEV.<major version>.<minor version>.<OS>.exe

Module ----------------------------------------------------------------------

The module contains the hardware definition and is found in the 'module' 
directory in this demo.
This is a copy of the module definition that is contained in the VLNV library 
at VLNV arm.ovpworld.org/module/ArmVersatileExpress-CA9/1.0

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
