# This Makefile can be used to recreate the application program
# Used as both client and server by this example.

#
# Build for host
#
CC=gcc

FLAGSM  = -lm -static -EL

ifeq ($(WINDOWS32),1)
FLAGS += -lwsock32
endif

multiserver: multiserver.c Makefile
	${CC} -Wall -ggdb -o $@ $< $(FLAGS)

#
# Build for RISC-V
#
# RISC-V Linux GNU Cross Compiler
CCR=riscv64-unknown-linux-gnu-gcc

multiserver.riscv.exe: multiserver.c Makefile
	${CCR} -Wall -g -O0 -o $@ $< 

clean:
	rm -f multiserver multiserver.riscv.exe
	
