riscv_SiFiveFU540_Linux

###############################################################################
# Demo Platform
###############################################################################
This demo will show how to execute SMP Linux running on a RISC-V processor on  
the SiFive FU540 virtual platform and also how to use tools to profile a user
application running on the Linux Kernel.

The platform is used to execute a pre-compiled version of linux that can be 
interacted with using a virtualized model of a UART interface.

The simulation platform 
was compiled using MinGW/MSYS http://www.mingw.org under Windows, and 
GCC under Linux.

IMPORTANT if using MSYS2
The MSYS environment expands the script kernel command line setting "/dev/vda" to 
"C:/msys64/dev/vda" which causes a boot failure. 
 
To stop this expansion, you need to set the following in your MSYS2 shell
 
export MSYS2_ARG_CONV_EXCL="*"

###############################################################################
# Running the simulation harness using a script provided
###############################################################################
The simulation is executed using one of the script files, for example 
'RUN_SiFiveFU540.sh', in the demo directory.

NOTE: The processor does not model the rdtime CSR, this is reported on each access
to remove these warnings the message type RISCV_IHPMU is excluded.

The simulation will start up (it may wait at the prompt in the interactive shell,
if it does use the 'isimulate' command to run the simulation).

The simulation will boot Linux to a shell prompt. To login use:
   Username: root
   Password: sifive 

NOTE: The scripts use --wallclockfactor to slow down the simulation to a maximum 
      execution compared to real time. This is required to allow the login at the 
      prompt without the Linux kernel timing out between providing the username
      and password if the simulator was permitted to run at its full speed.

It is now possible to interact with Linux running on the RISC-V processor of the 
virtual platform. The kernel boots with an initramfs as the root file system, 
so any changes you make will be lost when the simulation terminates.

To finish the simulation, simply close the terminal connected to a UART.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Linux kernel and Berkeley Boot Loader (bbl) info
###############################################################################
The Linux kernel and bbl provided are the same as supplied by SiFive with their
HiFive Freedom Unleashed board and were built using the source available here: 
    https://github.com/sifive/freedom-u-sdk/commit/62ae153449574c6d9a9f83510e735ef632a3ef8b

The only change to the standard build procedure was to add CONFIG_DEBUG_INFO=y 
to the kernel make command line and "-g -Og" to the CFLAGS on the bbl make
command line so that the elf files include debug information. Note that the 
kernel and initramfs are embedded in the bbl executable. 

We have provided the bbl and vmlinux elf files as part of this demo. The bbl elf
file is loaded by the simulator, so the bbl.bin image that is derived from the
bbl elf file and which is loaded onto an SD card for the HiFive Unleashed board  
is not used by the simulator.

The vmlinux elf file is also provided as a separate file, to be used when 
debugging the Linux kernel. It is important to make sure that the vmlinux
and bbl elf files are both from the same build so the debug info matches the
kernel image embedded in the bbl.

NOTE: There is inter-core interaction in stop_machine.c:175 multi_cpu_stop() 
      that waits for all processors to reach the same state. This causes
      apparent slow simulation without the reduction in quantum size to 0.00005
      which is set in the platform source (imperas.ovpworld.org/platform/SiFiveFU540/1.0)

###############################################################################
# Running provided benchmarks inside the simulated Linux
###############################################################################

This demo includes a disk image containing a set of cross compiled benchmark 
programs, benchmarks.img. This is loaded into the DRIVE. To run these benchmarks,
first mount the image in the simulated Linux with the command:

   mount /dev/vda /mnt
   
The benchmarks can now be found in /mnt/benchmarks/rv64. There are several shell
scripts in that directory to run various combinations of the benchmarks. 

###############################################################################
# Adding custom instructions to the RISCV processor
###############################################################################

The demo includes a extensions to the instruction set of the RISCV processor. 
The extension instructions are added without modification to the verified base
RISCV model by using an intercept library.

The intercept library is found in the directory interceptlib. To demonstrate 
the use of the extension instructions a program has been created in two forms, 
the first uses a C algorithm to implement the behavior and the second uses 
assembler to include the custom instruction. The applications are available in
the provided disk image.
To run the programs, first mount the image in the simulated Linux with the
command:

   mount /dev/vda /mnt
   
The programs can now be found in /mnt/custom. The programs are:
  custom_c   : implements the C algorithm
  custom_asm : uses the custom processor instruction.
  
The program custom_c will always execute but the program custom_asm will cause 
an exception when executed without the custom instruction included in the
processor, for example executing without the custom instruction will create:

# ./custom_asm.exe
 Running ASM Algorithm Implementation
 [  131.162900] custom_asm.exe[147]: unhandled signal 4 code 0x1 at 0x0000000000010402 in custom_asm.exe[10000+68000]
 [  131.162900] CPU: 4 PID: 147 Comm: custom_asm.exe Tainted: G        W        ...
 ...

To include the custom instruction set the variable CUSTOM=1 before starting the 
simulation.

###############################################################################
# User Application Function profile
###############################################################################

This section demonstrates how to create profile information for a user application
running under a Linux Kernel.

A pre-compiled mpeg2decode application is provided in the mpeg2decode directory. 
This is also loaded into a disk image file, mpeg2decode.img, that can be loaded
into the DRIVE.

Start the simulation using PROFILE_userApp_mpeg2decode which will execute a batch
file containing the set of commands to setup the profiling tool 

    ::ostrace -tasks
    ::userloadsymbols -hostfilename mpeg2decode/mpeg2decode.exe
    ::isetmessagepoint -message "load_elf_binary*mpeg2decode.exe"
    ::isimulate
    ::functionprofile -proc U54_hart1 -on -sampleinterval 1
    ::isetmessagepoint -message "do_exit*.exe"
    ::isimulate

 
To run the mpeg2decode user application
First mount the image in the simulated Linux with the command:

   mount /dev/vda /mnt
   
The application can now be found in /mnt/mpeg2decode 

   cd /mnt/mpeg2decode
   
and should be executed using the command line

   ./mpeg2decode.exe -b test.mpg -o0 fonte%d

The simulation will terminate after the application has completed.

The profiling information generated can be viewed using eGui, this will be opened
from the script using

    egui.exe -open FU540_U54_hart1.mpeg2decode.iprof

The profile for the USER code execution of the mpeg2decode application will be 
within the 'iProf FunctionProfiling View' (usually found minimized in the 
bottom right corner). Expand this tab to view all the processes in a 
hierarchical list. In the list you will find entries such as
  Platform: SiFiveFU540
    Processor: SiFiveFU540/U54_hart1
      Process: 0_swapper/2
      Process: 0_swapper/3
      ...
      Process: 142_./mpeg2decode.exe_KERNEL 
      Process: 142_./mpeg2decode.exe_USER 
      ...

When you expand the entry Process: 142_./mpeg2decode.exe_USER you will be 
provided with the profile information for the execution of the mpeg2decode
user application.

###############################################################################
# Interpreting Simulation results
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

