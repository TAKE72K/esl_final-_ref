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
set vendor  imperas.ovpworld.org
set library module
set name    Hetero_ARMv8-A-FMv1_Cortex-M3    
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text \
"This module implements a system containing two sub-systems \ 
1) ARM FMv1 Cortex-A53MPx5 running Linux, and \
2) Cortex-M3 running FreeRTOS. \
The two sub-systems are connected by a shared memory."
iadddocumentation -name Limitations -text "None"
iadddocumentation -name Reference   -text "ARM DUI 0677C and www.freertos.org"


#
# ARM FMv1
#
ihwaddmodule -instancename ARMv8-A-FMv1 -vendor arm.ovpworld.org -library module -type ARMv8-A-FMv1 -version 1.0

#
# ARM Cortex-M3 (FreeRTOS)
#
ihwaddmodule -instancename ArmCortexMFreeRTOS -vendor imperas.ovpworld.org -library module -type ArmCortexMFreeRTOS -version 1.0

# shared bus
# Shared Address Space
# 0x000000 - 0x0000fffe Memory
# 0x00fffe - 0x0000ffff Temperature Sensor

ihwaddbus  -instancename sharedBus -addresswidth 32
# connect sub-modules to shared bus
ihwconnect -instancename ARMv8-A-FMv1       -busport pBusP -bus sharedBus
ihwconnect -instancename ArmCortexMFreeRTOS -busport pBusP -bus sharedBus

#
# Shared Memory
#
ihwaddmemory -instancename sharedMemory -type ram
ihwconnect   -instancename sharedMemory -busslaveport sp1 -bus sharedBus -loaddress 0x00000000 -hiaddress 0x0000fffb
