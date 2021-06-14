Linux_ArmIntegratorCP

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show how to execute linux running on an ARM Cortex-A9UP on the 
ARM Integrator platform

The Platform contains

    Core Module
       ARM Cortex-A9UP Core (Also able to execute ARM926EJ-S)
       Interrupt Controller
       UART
       128M Bytes RAM (bridged to separate area)
    Base Board
       LCD Controller (not included in TLM version)
       Mouse/Keyboard Interfaces
       Flash Memory

The platform is used to execute a pre-compiled version of Linux that can be 
interacted with using a virtualized model of the LCD and keyboard interfaces.


The simulation harness exe was compiled using MinGW/MSYS http://www.mingw.org
under Windows, and GCC under Linux.

###############################################################################
# Running the simulation harness using a script provided
###############################################################################
The simulation is executed from one of the following directories:
  harness    : this executes the C API version of the virtual platform
  harnessTLM : this executes a SystemC TLM version of the virtual platform

Go to the required directory e.g. cd harness

Simply launch the executable using one of the scripts provided, for example
'RUN_ARMIntegratorCP.sh', in the harness or harnessTLM directories.

The simulation will now run and Linux will boot to a login prompt. 
to log in, type the username 'root', no password is required
There appears to be a Linux bug which occasionally causes the VGA text
to be skewed across the screen, without the correct CR/LF, if this occurs
simply log out, and log in again.
It is now possible to interact with Linux running on the ARM processor of the 
virtual platform. 

To finish the simulation, simply close the VGA window.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Running Installed 'Penguin Population' application
###############################################################################

An application 'Penguin Population' provided to demonstrate frame buffer 
performance on Linux is available installed on the ram disk image.
 
This can be started by typing 'df_andi' on the simulated Linux command line.
It can be terminated and return to the command line by pressing Escape.

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
# Compiling User Programs, and adding to disk image - Linux
###############################################################################
Firstly download the ARM linux toolchain from CodeSourcery
http://www.codesourcery.com/sgpp/lite/arm/portal/release858 or a later release

Install this toolchain on your disk

Build benchmark applications in the following manner
% make -C benchmarks TOOLDIR=<pathToCompilerInstallation> all

This will create several executables, now we want to add this to our ramdisk
Extract Ramdisk to file system
% unpackImage.sh fs.img fs

Copy benchmarks into filesystem
% cp -r benchmarks fs

Package filesystem back into a ramdisk
% packImage.sh fs fs.img

Rerun the simulator, this time there will be a top level directory called
'benchmarks', which contains the applications built in the previous steps
these can now be executed in the simulated Linux


###############################################################################
# Compiling User Programs, and adding to disk image - Windows (MSYS/Mingw)
###############################################################################
Firstly download an ARM Linux toolchain

Install this toolchain on your disk

You will also need a windows version of cpio, this can be found here
http://sourceforge.net/projects/gnuwin32/files/cpio/cpio-2.6-2.exe/download
Install cpio, and ensure it appears on your path in the MSYS shell

Build benchmark applications in the following manner
% make -C benchmarks all

Unfortunately under windows we cannot unpack the image to a filesystem
because windows does not understand symbolic links, which are present on the 
simulated disk, So under Windows we will simply append the files onto the existing
image
% appendImage.sh benchmarks fs.img newfs.img
% mv newfs.img fs.img

Re run the simulator, this time there will be a top level directory called
'benchmarks', which contains the applications build in the previous steps
these can now be executed in the simulated Linux

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
at VLNV arm.ovpworld.org/module/ArmIntegratorCP/1.0

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

###############################################################################
# Command Line Execution Options
###############################################################################

Additional command line options may be used when running the platform. These may
be added or provided on the command line to the .bat or .sh scripts provided.

'--wallclock'  to limit the maximum performance to 3x 'wallclock' time, this may be 
               required if running an application that includes a timeout 
               e.g. a login with password
            
'--variant'    to modify the processor type modeled. If this is modified from the 
               default ARM Cortex-A9UP the operation of the platform may change.
               NOTE: this is not possible for the TLM Platform, this is built 
                     into the platform definition.

###############################################################################
# Selecting ARM926EJ-S
###############################################################################
The default processor variant is the Cortex-A9 but also available is a Linux
kernel that has been built for the simpler ARM926EJ-S.

To use the ARM926EJ-S please add the following line to select the required 
ARM926 variant

 '--variant ARM926EJ-S'
 
and modify the entry
 
  'zImage-CA9'

to select the alternate kernel to load into memory using 

  'zImage-ARM926'
 
###############################################################################
# Overriding Component Configuration Parameters
###############################################################################
when a component is instanced in the module hardware definition it may be 
provided some default configuration parameters. These may be discovered and then
modified from the command line

'--showoverrides'   command line argument to show all available component 
                    parameters, the default value and an override example.

Example output may be 
  --override ArmIntegratorCP/arm1/variant=Cortex-A9UP (Enumeration) (default=ARMv4T) Selects variant (either a generic ISA or a specific model)
  --override ArmIntegratorCP/lcd/noGraphics=F (Boolean) (default=F) Disable the graphics output

and can then be applied to the simulation, for example to disable the graphics
start the simulation with
 > RUN_ARMIntegratorCP.sh --override ArmIntegratorCP/lcd/noGraphics=T
 