riscv_Andex_N25_FreeRTOS

###############################################################################
# Purpose of Demo
###############################################################################
This demo will show the FreeRTOS operating system can be executed on the OVP
RISC-V processor model.

A pre-built version of the FreeRTOS example files, used by this demo, can be
found in the freertos-V5 directory. This was generated using the Andes BSP.

The simulation executables were compiled using 
MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation
###############################################################################

Scripts are provided to run the FreeRTOS demo using the N25 (32-bit) or the 
NX25 (64-bit) processor configurations.

  RUN_N25_FreeRTOS.sh(.bat)
  RUN_NX25_FreeRTOS.sh(.bat)

The simulation will start and a UART Console will be launched. The UART Console
will print messages from the FreeRTOS Demo application.

The simulation will continue indefinitely but can be terminated by closing the
UART console.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Rebuilding the FreeRTOS demo applications
###############################################################################

The Andes Board Support Package v5.0.1 was used to provide the example FreeRTOS
demo application.

The virtual platform uses the definition for the AE350
http://www.andestech.com/en/products-solutions/andeshape-platforms/ae350-axi-based-platform-pre-integrated-with-n25f-nx25f-a25-ax25/

The Cross Compiler used was provided with the BSP and is selected by adding the 
following directory to the PATH

 <PATH TO INSTALL>/BSPv501/x86/toolchains/nds64le-elf-mculib-v5/bin
  
To build for the FreeRTOS demo for the N25 (RISC-V 32-bit processor) the following
command line was used:

$ make COMPILER=riscv32 DEBUG=1 PLAT=AE350 USE_CACHE=1

To build for the FreeRTOS demo for the NX25 (RISC-V 64-bit processor) the following
command line was used:

$ make COMPILER=riscv64 DEBUG=1 PLAT=AE350 USE_CACHE=1


##