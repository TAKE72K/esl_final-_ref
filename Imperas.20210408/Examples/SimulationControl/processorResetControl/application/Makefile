ifndef IMPERAS_HOME
  IMPERAS_ERROR := $(error "IMPERAS_HOME not defined, please setup Imperas/OVP environment")
endif
IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
include $(IMPERAS_HOME)/bin/Makefile.include

CROSS?=OR1K
OPTIMISATION?=-O0 -g 

-include $(IMPERAS_HOME)/lib/$(IMPERAS_ARCH)/CrossCompiler/$(CROSS).makefile.include
ifeq ($($(CROSS)_CC),)
    IMPERAS_ERROR := $(error "Please install the $(CROSS) toolchain")
endif

SRC = $(sort $(wildcard *.c))
EXE = $(patsubst %.c,%.$(CROSS).elf,$(SRC))

all: $(EXE)

%.$(CROSS).o: %.c
	$(V) echo "Compiling Application $@"
	$(V) $($(CROSS)_CC)  -c  $(IMPERAS_CFLAGS) -D$(CROSS)  -o $@  $^ $(OPTIMISATION)

%.$(CROSS).elf: %.$(CROSS).o 
	$(V) echo "Linking Application $@"
	$(V) $($(CROSS)_LINK) -o $@  $^  $(IMPERAS_LDFLAGS)
	$(V) $($(CROSS)_OBJDUMP) -S $@  > $(basename $@).od

clean:
	- rm -f *.$(CROSS).elf *.$(CROSS).o *.$(CROSS).od
