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

ihwnew -name cpuSystem

#
# The System
#

# Local bus
ihwaddbus -instancename busLocal -addresswidth 32

ihwaddprocessor -instancename cpu1 \
                -vendor ovpworld.org -library processor -type or1k -version 1.0 \
                -variant generic \
                -semihostname or1kNewlib
ihwconnect -bus busLocal -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus busLocal -instancename cpu1 -busmasterport DATA

# mapped bus
ihwaddbus -instancename busMapped   -addresswidth 32

ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus busMapped -instancename ram1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0xffffffff

#
# We will use a static bridge to map the complete address range between the two busses in this module 
#
ihwaddbridge -instancename br1
ihwconnect -bus busLocal   -busslaveport  ps -instancename br1 -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect -bus busMapped  -busmasterport pm -instancename br1 -loaddress 0x00000000 -hiaddress 0xffffffff
