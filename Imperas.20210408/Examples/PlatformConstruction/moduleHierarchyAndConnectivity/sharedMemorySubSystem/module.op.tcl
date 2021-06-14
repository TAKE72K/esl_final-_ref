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

# module.op.tcl

ihwnew -name sharedMemorySubSystem

# add memory
ihwaddmemory -instancename ram -type ram

# add bus
ihwaddbus -instancename bus   -addresswidth "32"

# add connections to bus
ihwconnect -instancename ram -bus bus  \
           -busslaveport  "sp" -loaddress "0x00000000" -hiaddress "0x00000fff"

# create and name the module's external bus port
ihwaddbusport -instancename busPort

# connect the external bus ports to the bus
ihwconnect -busport busPort -bus bus
