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

ihwnew -name netRepeater

ihwaddnet -instancename netIn
ihwaddnet -instancename netOut

# create and name the net ports

ihwaddnetport -instancename netInPort
ihwaddnetport -instancename netOutPort

# connect the net ports to nets

ihwconnect -netport netInPort  -net netIn
ihwconnect -netport netOutPort -net netOut
