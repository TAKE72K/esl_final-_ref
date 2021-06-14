riscv_RV64GC_Virtio_Linux

###############################################################################
# Purpose of Demo
###############################################################################

This demo will show the RISC-V Linux operating system running on the OVP RISC-V 
processor model.

Pre-built versions of the Linux kernel files, used by this demo, can be found
in the Linux directory.

The platform modeled matches the memory map of the QEMU RISC-V VirtIO Board 
defined in riscv-qemu.

The simulation executables were compiled using 
MinGW/MSYS http://www.mingw.org under Windows, and GCC under Linux.

###############################################################################
# Running the simulation
###############################################################################

The simulation is executed from the following directory:
  harness    : this executes the C API version of the virtual platform

Launch the simulation platform by double clicking 'RUN_Virtio_Linux.bat' in a Windows
explorer or execute the script 'RUN_Virtio_Linux.sh' in a Linux shell or Windows MSYS
shell.

NOTE: If running in a Windows MSYS shell please ensure PATH expansion is disabled, see 
Installation and Getting Started Guide, section "Environment -> Stop PATH Expansion"

The simulation will start and a UART Console will be launched.

The UART Console will print messages from the kernel.

Note the use of wallclockfactor to limit the execution speed of the simulation. This 
is required so that the timeout does not fail when logging in. 

-- Login --
At the login prompt you may login with
  username: root
  password: busybear

-- Running installed benchmarks --
There are a number of pre-compiled benchmarks included on the ram disk. These
can be found in the benchmarks directory
root@ucbvax:/# cd /benchmarks/rv64

Find all the available benchmarks
root@ucbvax:/# ls *.exe

Execute one of the benchmarks, for example Linpack
root@ucbvax:/# ./linpack.exe


The simulation will continue indefinitely but can be terminated by closing the
UART console.

Statistics will be printed upon completion of the simulation.

###############################################################################
# Configuring the ethernet interface in the simulated Linux
###############################################################################

The following commands may be executed in the simulated Linux to configure the 
ethernet interface:

root@ucbvax:/# ifconfig eth0 10.0.2.15 up
root@ucbvax:/# route add default gw 10.0.2.2

This can then be tested using the command:

root@ucbvax:/# wget example.com/index.html

This will download the file index.html onto the local ramdisk.

###############################################################################
# Configuring the Ethernet interface for host access using TCP/UDP over sockets
###############################################################################

The redir parameter on the Ethernet peripheral is used to open a socket between
the host and simulated Linux kernel that supports TCP/UDP packet transfers.

Start the simulation with a socket enabled

$ RUN_Virtio_Linux.sh --override virtio/VND0/redir=tcp:54322:10.0.2.15:54320

This opens port 54322 on the host and 54320 within the virtual Linux kernel

Configure the interface (as above)

root@ucbvax:/# ifconfig eth0 10.0.2.15 up
root@ucbvax:/# route add default gw 10.0.2.2

and then start a program, such as netcat (nc), to listen on the open port 54320

root@ucbvax:/# nc -l -p 54320

On the host machine use a program such as telnet to connect to the open port

$ telnet localhost 54322

You may now type into telnet and the characters should be output by nc in the
Linux Kernel.

# Multiserver Client/Server Application Example
An example application is provided as source in the directory multiserver and 
also as a compiled RISC-V binary image on the busybear-linux disk image.
This can be used to transfer test packets over the Ethernet interface, as 
shown below:

root@ucbvax:/# cd /multiserver
root@ucbvax:/# ./multiserver.riscv.exe s 54320
Server
Server listening on 0.0.0.0:54320
Host: 0.0.0.0, Port: 54320  waiting for client to connect

This has opened port 54320 and is waiting for a connection to be made

On the host machine compile the multiserver.c application using a host GCC
$ cd Linux/multiserver
$ make multiserver

Start the multiserver application as a client to talk to the port on the 
virtual platform

$ ./multiserver c 54322
Client
Client starting
Client connected to fd:3  127.0.0.1:54322
    client 127.0.0.1 sending [127.0.0.1:0]
    client response message received
    127.0.0.1 received [Answer to [127.0.0.1:0]]
    client 127.0.0.1 sending [127.0.0.1:1]
    client response message received

This makes the connection to the port and starts sending test packets and 
reporting that responses are received.

At the same time the server will report a connection made, reporting packets
received and sending responses.

connection accepted on fd 4
    read 11 bytes  [127.0.0.1:0]
    sent 23 bytes  [Answer to [127.0.0.1:0]]
    read 11 bytes  [127.0.0.1:1]
    sent 23 bytes  [Answer to [127.0.0.1:1]]

NOTE: This example application, as written, does not allow the server to be
started on the Host machine. This is because it expects to open the port but 
the simulation has already opened the port. You will get the error shown below
if attempted

$ ./multiserver s 54322
Server
Failed to bind server socket on 54322 : Address already in use

###############################################################################
# RISC-V Linux Operating System - downloading and re-building
###############################################################################

NOTE: A suitable riscv toolchain is required and must be present on the PATH

The files may be obtained and re-built (on Linux host) using the following 
resources:

-- busybear.bin --
git clone https://github.com/michaeljclark/busybear-linux.git
pushd busybear-linux
  make
popd

-- vmlinux --
git clone https://github.com/riscv/riscv-linux.git
pushd riscv-linux
  git checkout riscv-linux-4.14
  cp ../busybear-linux/conf/linux.config .config
  make ARCH=riscv olddefconfig
  make ARCH=riscv CONFIG_DEBUG_INFO=y vmlinux 
popd

-- bbl --
git clone https://github.com/riscv/riscv-pk.git
pushd riscv-pk
  mkdir build
  pushd build
    ../configure \
        --enable-logo \
        --host=riscv64-unknown-elf \
        --with-payload=../../riscv-linux/vmlinux
    #
    # MANUALLY EDIT MAKEFILE AND CHANGE -O2 to -g -O0 in CFLAGS
    #
    make
  popd
popd

###############################################################################
# Re-Building Virtual Platform
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
at VLNV location riscv.ovpworld.org/module/virtio/1.0

Re-building the module is carried out using the standard Makefile in either a Linux
or an MSYS/MinGW on Windows shell.

For Example to re-build the module, the following can be used

$ make -C module NOVLNV=1
or
$ cd module
$ make NOVLNV=1

###############################################################################
# Accessing the disk image from a Linux host
###############################################################################

The demo includes a disk image that is mounted by the simulated Linux. You may 
access and modify this image from a Linux system as follows (note - this does
not work on an NFS disk - do this in a directory located on a local disk):

$ cd Linux
$ mkdir busybear-linux
$ sudo mount -o loop busybear-linux.bin busybear-linux

The busybear-linux directory is now the image file system which you can examine
and modify (note - you will need to have root permissions on your host to modify
files on the image owned by root).

When finished do:

$ sudo umount busybear-linux
$ rm busybear-linux

##   
