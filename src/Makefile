#
# OMNeT++/OMNEST Makefile for omletkurs
#
# This file was generated with the command:
#  opp_makemake -f --deep
#

# Name of target to be created (-o option)
TARGET = omletkurs$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I. -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/AdmissionControlModule.o \
    $O/BaseGenerator.o \
    $O/FQ.o \
    $O/FrontDrop.o \
    $O/LeakyBucket.o \
    $O/Mmpp.o \
    $O/OmNomNom.o \
    $O/OnOffGenerator.o \
    $O/Poisson.o \
    $O/RED.o \
    $O/RoundRobin.o \
    $O/RoundRobin2.o \
    $O/TailDrop.o \
    $O/TokenBucket.o \
    $O/WFQ.o \
    $O/Worker.o \
    $O/WRED.o \
    $O/WRoundRobin.o \
    $O/Wykladniczy.o \
    $O/jobDone_m.o \
    $O/packet_m.o

# Message files
MSGFILES = \
    jobDone.msg \
    packet.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f omletkurs omletkurs.exe libomletkurs.so libomletkurs.a libomletkurs.dll libomletkurs.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/AdmissionControlModule.o: AdmissionControlModule.cc \
	AdmissionControlModule.h \
	jobDone_m.h \
	packet_m.h
$O/BaseGenerator.o: BaseGenerator.cc \
	BaseGenerator.h \
	packet_m.h
$O/FQ.o: FQ.cc \
	FQ.h \
	packet_m.h
$O/FrontDrop.o: FrontDrop.cc \
	AdmissionControlModule.h \
	FrontDrop.h \
	jobDone_m.h \
	packet_m.h
$O/LeakyBucket.o: LeakyBucket.cc \
	LeakyBucket.h
$O/Mmpp.o: Mmpp.cc \
	BaseGenerator.h \
	Mmpp.h \
	packet_m.h
$O/OmNomNom.o: OmNomNom.cc \
	OmNomNom.h
$O/OnOffGenerator.o: OnOffGenerator.cc \
	BaseGenerator.h \
	OnOffGenerator.h \
	packet_m.h
$O/Poisson.o: Poisson.cc \
	BaseGenerator.h \
	Poisson.h \
	packet_m.h
$O/RED.o: RED.cc \
	AdmissionControlModule.h \
	RED.h \
	jobDone_m.h \
	packet_m.h
$O/RoundRobin.o: RoundRobin.cc \
	RoundRobin.h \
	packet_m.h
$O/RoundRobin2.o: RoundRobin2.cc \
	RoundRobin2.h \
	packet_m.h
$O/TailDrop.o: TailDrop.cc \
	AdmissionControlModule.h \
	TailDrop.h \
	jobDone_m.h \
	packet_m.h
$O/TokenBucket.o: TokenBucket.cc \
	TokenBucket.h
$O/WFQ.o: WFQ.cc \
	WFQ.h \
	packet_m.h
$O/WRED.o: WRED.cc \
	AdmissionControlModule.h \
	WRED.h \
	jobDone_m.h \
	packet_m.h
$O/WRoundRobin.o: WRoundRobin.cc \
	WRoundRobin.h \
	packet_m.h
$O/Worker.o: Worker.cc \
	Worker.h \
	jobDone_m.h \
	packet_m.h
$O/Wykladniczy.o: Wykladniczy.cc \
	BaseGenerator.h \
	Wykladniczy.h \
	packet_m.h
$O/jobDone_m.o: jobDone_m.cc \
	jobDone_m.h
$O/packet_m.o: packet_m.cc \
	packet_m.h

