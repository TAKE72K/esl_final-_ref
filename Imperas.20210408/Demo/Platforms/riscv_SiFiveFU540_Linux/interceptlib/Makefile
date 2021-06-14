IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")

all: interceptlib

include $(IMPERAS_HOME)/ImperasLib/buildutils/Makefile.host

interceptlib: model.$(IMPERAS_ARCH).$(IMPERAS_SHRSUF)
model.$(IMPERAS_ARCH).$(IMPERAS_SHRSUF): model.$(IMPERAS_SHRSUF)
	cp $< $@

clean::
	rm -f model.$(IMPERAS_ARCH).$(IMPERAS_SHRSUF)
