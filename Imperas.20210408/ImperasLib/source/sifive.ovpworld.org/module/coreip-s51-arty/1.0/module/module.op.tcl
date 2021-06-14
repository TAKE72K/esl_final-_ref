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

# Setup variables for platform info 
set vendor  sifive.ovpworld.org
set library module
set name    coreip-s51-arty
set version 1.0


# Number of global interrupts supported
set num_globalints 127

# Number of local interrupts supported
set num_localints   16

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "SiFive coreip-s51-arty module."

iadddocumentation -name Reference    -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."

iadddocumentation -name Limitations  -text "None"

# Create local bus
ihwaddbus  -instancename systemBus -addresswidth 40

# instance S51 Core Complex module
ihwaddmodule -instancename S51CC -vendor sifive.ovpworld.org -library module -type S51CC -version 1.0
ihwsetparameter  -handle   S51CC/S51   -name mips     -value 65       -type double
# when using CLINT the mtime/mtimecmp registers are external so disable
ihwsetparameter  -handle   S51CC/S51   -name time_undefined -value True -type bool
ihwsetparameter  -handle   S51CC/clint -name clockMHz -value 0.032768 -type double

# connect system bus
ihwconnect -instancename S51CC -busport systemPort -bus systemBus

# connect interrupt nets
for {set id 1} {$id < $num_globalints} {incr id} {
    ihwaddnet -instancename gi${id}
    ihwconnect -instancename S51CC -netport gi${id} -net gi${id}
}
# local interrupts used for Switch and Button
for {set id 0} {$id < $num_localints} {incr id} {
    ihwaddnet -instancename li${id}
    ihwconnect -instancename S51CC -netport li${id} -net li${id}
}

# FLASH memory 00_4000_0000:00_5fff_ffff
ihwaddmemory -instancename flash -type rom 
ihwconnect   -instancename flash -busslaveport sp1 -bus systemBus -loaddress 0x0040000000ULL -hiaddress 0x005fffffffULL

# memory 00_0000_4000:00_0000_4fff
# written in __metal_driver_sifive_test0_exit
ihwaddperipheral -instancename tstatus -vendor sifive.ovpworld.org -library peripheral -type teststatus -version 1.0 
ihwconnect       -instancename tstatus -busslaveport bport1 -bus systemBus -loaddress 0x00004000 -hiaddress 0x00004fff

# uart0 00_2000_0000:00_2000_001b
ihwaddperipheral -instancename uart -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type UART
ihwconnect       -instancename uart -bus systemBus -busslaveport bport1 -loaddress 0x0020000000ULL -hiaddress 0x002000001bULL 
ihwconnect       -instancename uart -net gi1 -netport intOut
ihwsetparameter  -handle       uart  -name finishOnDisconnect -value True -type bool
ihwsetparameter  -handle       uart  -name console            -value True -type bool

# gpio@0x20002000 for LEDs and buttons
ihwaddperipheral -instancename gpio -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type gpio
ihwconnect       -instancename gpio -bus systemBus -busslaveport bport1 -loaddress 0x0020002000ULL -hiaddress 0x0020002FFFULL 
# Connect GPIO port interrupts
for {set id 0} {$id < 16} {incr id} {
    # GPIO interrupts start at GI7
    set gin [expr ${id} + 7]
    ihwconnect -net gi${gin} -instancename gpio -netport intOut${id} 
}
# GPIO also creates switch and button local interrupts (simulation visualization connection)
ihwconnect -net li0 -instancename gpio -netport intSW0
ihwconnect -net li1 -instancename gpio -netport intSW1
ihwconnect -net li2 -instancename gpio -netport intSW2
ihwconnect -net li3 -instancename gpio -netport intSW3
ihwconnect -net li4 -instancename gpio -netport intBTN0
ihwconnect -net li5 -instancename gpio -netport intBTN1
ihwconnect -net li6 -instancename gpio -netport intBTN2
ihwconnect -net li7 -instancename gpio -netport intBTN3

# spi@0x20004000
ihwaddperipheral -instancename spi -vendor sifive.ovpworld.org -library peripheral -type spi -version 1.0 
ihwconnect       -instancename spi -bus systemBus -busslaveport bport1  -loaddress 0x20004000 -hiaddress 0x20004fff

# pwm@0x20005000
ihwaddperipheral -instancename pwm -vendor sifive.ovpworld.org -library peripheral -type pwm -version 1.0 
ihwconnect       -instancename pwm -bus systemBus -busslaveport bport1 -loaddress 0x20005000 -hiaddress 0x20005fff 
