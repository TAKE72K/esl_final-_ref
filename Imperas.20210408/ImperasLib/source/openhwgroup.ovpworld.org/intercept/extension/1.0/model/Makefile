IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/riscv.ovpworld.org/processor/riscv/1.0/model

# TODO: Remove after extensionconfig.h dependency resolved
CFLAGS+=-I$(IMPERAS_HOME)/ImperasLib/source/openhwgroup.ovpworld.org/processor/riscv/1.0/model
CFLAGS+=-I.

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host
