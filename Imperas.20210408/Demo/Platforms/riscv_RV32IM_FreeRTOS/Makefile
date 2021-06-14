#!/bin/sh

all:
	@echo "Build Module"
	$(MAKE) -C module      NOVLNV=1
	@echo "Build TLM Platform"
	$(MAKE) -C harnessTLM  NOVLNV=1
	@echo "Build FreeRTOS"
	@cd FreeRTOS;BUILD.sh

clean:
	@echo "Clean Module"
	$(MAKE) -C module      NOVLNV=1 clean
	@echo "Clean TLM Platform"
	$(MAKE) -C harnessTLM  NOVLNV=1 clean
	@echo "Clean FreeRTOS"
	@cd FreeRTOS;BUILD.sh clean
	