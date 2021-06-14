#
# Build the C++ Library shim
#

IMPERAS_HOME := $(shell getpath.exe "$(IMPERAS_HOME)")
ifndef IMPERAS_HOME
    IMPERAS_ERROR := $(error "IMPERAS_HOME not defined")
endif
include $(IMPERAS_HOME)/bin/Makefile.include

############################# INPUT PARAMETERS ################################

ifeq ($(VERBOSE),1)
  V=
else
  V=@
endif

########################### END INPUT PARAMETERS ##############################

OPCPPSRC  = $(wildcard *.cpp)
LIBNAME  ?= libOP++
LIB       = $(LIBNAME).$(IMPERAS_SHRSUF)

ifeq ($(IMPERAS_UNAME),Linux)
CXXCFLAGS += -rdynamic -fno-aggressive-loop-optimizations \
             -fwrapv -fno-strict-overflow
CXXLDFLAGS += -Wl,--no-undefined
endif

ifeq ($(IMPERAS_UNAME),Windows)
CXXCFLAGS += -fwrapv -fno-strict-overflow 
# Not supported on some compilers
# -fno-aggressive-loop-optimizations 
CXXLDFLAGS += -static-libgcc \
              -Wl,--disable-auto-image-base \
              -Wl,-Bsymbolic
endif

#
# Build location for intermediate files
#
BUILDROOT = Build
OBJD      = $(BUILDROOT)/$(IMPERAS_ARCH)/usr

DEP = $(sort $(patsubst %.cpp, $(OBJD)/%.d, $(OPCPPSRC)))
OBJ = $(sort $(patsubst %.cpp, $(OBJD)/%.o, $(OPCPPSRC)))

all: $(LIB)
	@    echo "# Created C++ Support Library $(LIB)"

#
# include all the dependancy requirements
#
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),realclean)
    $(foreach dep,$(DEP),$(eval -include $(dep)))
endif
endif

#
# Build rules
#
$(LIB): $(OBJ)
	@    echo "# OP C++ Linking $@"
	$(V) $(HOST_GXX) -o $@ --shared $^ $(SIM_LDFLAGS) $(CXXLDFLAGS)
ifeq ($(IMPERAS_UNAME),Windows)
endif

$(OBJD)/%.o: %.cpp
	@    echo "# OP C++ Compiling $@"
	$(V) mkdir -p $(@D)
	$(V) $(HOST_GXX) -c -o $@ $< $(SIM_CFLAGS) $(SIM_CXXFLAGS) $(CXXCFLAGS)

$(OBJD)/%.d: %.cpp
	@    echo "# OP C++ Depending $@"
	$(V) mkdir -p $(@D)
	$(V) $(HOST_GXX) -MM $< $(SIM_CFLAGS) $(CFLAGS) -MT $(@D)/$*.o -MF $@

clean:
	- rm -f $(LIB) $(OBJ) $(DEP)
ifeq ($(IMPERAS_UNAME),Windows)
	- rm -f $(LIBNAME).def $(LIBNAME).a
endif
realclean: clean
	- rm -rf $(BUILDROOT)
