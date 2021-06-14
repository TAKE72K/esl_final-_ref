
ifeq ($(GCCDIR),)
  IMPERAS_ERROR := $(error "You must define the GCCDIR variable")
endif
  
ROOT=$(GCCDIR)/bin/riscv64-unknown-linux-gnu
CC=$(ROOT)-gcc
OBJDUMP=$(ROOT)-objdump
STRIP=$(ROOT)-strip

OPTLVL?=0
CFLAGS =-g -O$(OPTLVL) -static 
LDFLAGS=-lm

# Compile each .c file in DIR
SRC     = $(wildcard *.c)
EXE     = $(notdir $(SRC:.c=.exe))
STRPEXE = $(notdir $(SRC:.c=.strp.exe))
OD      = $(notdir $(SRC:.c=.od))

all: $(EXE) $(STRPEXE)
objdump: $(OD)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.strp.exe: %.exe
	cp $< $@
	$(STRIP) $@

%.od: %.exe
	$(OBJDUMP) -d $< > $@

clean::
	rm -f $(EXE) $(STRPEXE) $(OD)
