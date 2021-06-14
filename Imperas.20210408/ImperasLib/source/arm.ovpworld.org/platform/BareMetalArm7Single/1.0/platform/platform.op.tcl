#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#
# NAME : BareMetalArm7Single

ihwnew -name BareMetalArm7Single  \
                -vendor arm.ovpworld.org  \
                -library platform  \
                -version 1.0 \
                -purpose baremetal -releasestatus ovp \
                -verbose -stoponctrlc

iadddocumentation  \
                -name Description  \
                -text "Bare Metal Platform for an ARM7 Processor.
    The bare metal platform instantiates a single ARM7 processor instance. 
    The processor operates using little endian data ordering.
    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.
    The platform can be passed any application compiled to an ARM elf format.
    ./platform.exe application.elf"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain."

iadddocumentation  \
    -name Reference  \
    -text "None, BareMetal platform definition"

# Use command line parser
ihwaddclp -allargs

############################ processor ############################

  ihwaddprocessor  \
                -instancename cpu1  \
                -type arm \
                -endian little \
                -vendor arm.ovpworld.org  \
                -semihostname armNewlib \
                -semihostvendor arm.ovpworld.org

    ihwsetparameter  \
                -handle cpu1  \
                -name variant  \
                -value ARM7TDMI \
                -type enum

    ihwsetparameter  \
                -handle cpu1  \
                -name compatibility  \
                -value gdb \
                -type enum

    ihwsetparameter  \
                -handle cpu1  \
                -name UAL  \
                -value 1 \
                -type bool

  ihwaddbus -instancename bus1  \
                -addresswidth 32

############################## memory #############################

  ihwaddmemory -instancename memory  \
                -type ram


########################### connections ###########################

    ihwconnect -instancename cpu1  \
                -busmasterport INSTRUCTION  \
                -bus bus1

    ihwconnect -instancename cpu1  \
                -busmasterport DATA  \
                -bus bus1

    ihwconnect -instancename memory  \
                -busslaveport sp1  \
                -bus bus1  \
                -loaddress 0x00000000  \
                -hiaddress 0xffffffff

