riscv_SiFive_coreip-s51-arty

###############################################################################
# Purpose of Demo
###############################################################################

This demo will show the RISC-V executing examples from and compiled with SiFive
Freedom E SDK for the coreip-s51-arty FPGA board definition.

The simulation executables were compiled using 
MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation
###############################################################################

The scripts RUN_arty.sh(.bat) will list the example elf files provided and allow
one to be selected to execute on the virtual platform.

The coreip-s51-arty includes the 'teststatus' device that, when written, will
terminate the simulation and based upon the value written report the test status.

The 'local-interrupt' example takes input from switches. The switches can be
realized using visualization. An HTML page is loaded into a browser by the GPIO
peripheral device when it as attached to the open port, typically using the
address http://localhost:8000
Note: Although the hardware platform uses RGB LEDs, the virtual platform 
visualization is created with three separate LEDs (all use a red LED) from the 
standard library. 

###############################################################################
# Example Applications
###############################################################################

The example applications are provided by the SiFive Freedom E SDK which is also 
used to compile them targeting the coreip-s51-arty on AE350 board. This is 
available from https://github.com/sifive/freedom-e-sdk

The following are provided by SiFive as simple tests to run on the hardware.

   dhrystone            : Dhrystone benchmark
   empty                : skeleton test application
   example-itim         : test ITIM
   example-pmp          : test PMP (Register only model)
   example-spi          : test SPI (Register only model)
   hello                : prints 'Hello World"' on the UART
   local-interrupt      : test local interrupt, attach visualization to interact
                          and generate local interrupts
   return-fail          : executes and reports test pass
   return-pass          : executes and reports test fail
   sifive-welcome       : prints welcome screen on the UART
   software-interrupt   : test software interrupt generation
   timer-interrupt      : test timer interrupt generation

The source, at the time of compilation, is provided in separate source directories
under the examples directory.

The 'teststatus' peripheral, that is part of the virtual platform, is an address 
space to which the application programs write a value at completion indicating 
test pass/fail. The peripheral model prints the test status and then terminates the
simulation.

##