###############################################################################
#
#     FILENAME:   Makefile for VTS
#
#     DESCRIPTION:
#
#     This Makefile is used by make to build the vts application and
#     supporting code on Linux, IRIX, or Solaris using the Sun or gcc compiler.
#
#     NOTES:
#
###############################################################################

ifeq ($(GCC),)
   CXX = CC
   LDLIBS = -ldl -lCstd
else
   CXX = g++ -m32
   UN_GCC = _gcc
   LDLIBS = -ldl 
   MKARGS = GCC=$(GCC)
endif
 
CXXFLAGS = -c -g -D_FILE_OFFSET_BITS=64
VTSPROJDIR = ..

CSMINCDIR = $(VTSPROJDIR)/CSM_include
CSMDIR = $(VTSPROJDIR)/CSM
CSMOBJDIR = $(VTSPROJDIR)/CSM/object$(UN_GCC)

VTSINCDIR = $(VTSPROJDIR)/VTS_include
VTSOBJDIR = $(VTSPROJDIR)/VTS/object$(UN_GCC)

BINPATH = VTS/binary$(UN_GCC)
VTSBINDIR = $(VTSPROJDIR)/$(BINPATH)
LNKBINDIR = ./$(BINPATH)

# The flags needed to compile all

# we need to link in the dll handling library


#------------------------------------------------------------------------------
all : $(VTSBINDIR)/vts
	(cd $(VTSPROJDIR); rm -f vts; ln -s $(LNKBINDIR)/vts .)
	echo "GCC $(GCC)"
# the main executable has to be linked with the -rdynamic flag
# so the plug in libraries can call inherited methods and
# access vtables in the main executable.

#------------------------------------------------------------------------------
# "copy" is the same as "all" except the actual executable is copied to the
#        top-level directory instead of generating a link.

copy : $(VTSBINDIR)/vts
	(cd $(VTSPROJDIR); rm -f vts; cp $(LNKBINDIR)/vts .)

#------------------------------------------------------------------------------
$(VTSBINDIR)/vts :   $(VTSOBJDIR)/vts.o \
	$(VTSOBJDIR)/compareParam.o \
	$(VTSOBJDIR)/recordLog.o \
	$(VTSOBJDIR)/SMManager.o \
	$(VTSOBJDIR)/tokenizer.o \
	$(VTSOBJDIR)/vts_isd.o \
	$(VTSOBJDIR)/vts_misc.o \
	$(VTSOBJDIR)/tinyxml.o       \
	$(VTSOBJDIR)/SensorModelThreadSafe.o       \
	$(CSMINCDIR)/FourParameterCorrelationModel.h \
	$(VTSPROJDIR)/libCSMPlugin.so
	
	$(CXX) -lpthread -g $(VTSOBJDIR)/vts.o \
		$(VTSOBJDIR)/vts_misc.o \
		$(VTSOBJDIR)/vts_isd.o \
		$(VTSOBJDIR)/SMManager.o \
		$(VTSOBJDIR)/compareParam.o \
		$(VTSOBJDIR)/recordLog.o \
		$(VTSOBJDIR)/tokenizer.o \
		$(VTSOBJDIR)/tinyxml.o       \
		$(VTSOBJDIR)/SensorModelThreadSafe.o       \
                -L$(VTSPROJDIR) -lCSMPlugin \
		-o $(VTSBINDIR)/vts  $(LDLIBS)

# -rdynamic

#------------------------------------------------------------------------------
$(VTSOBJDIR)/vts.o : vts.cpp \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/Model.h \
	$(CSMINCDIR)/Isd.h \
	$(CSMINCDIR)/NitfIsd.h \
	$(CSMINCDIR)/BytestreamIsd.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/RasterGM.h \
	$(CSMINCDIR)/Version.h \
	$(CSMINCDIR)/GeometricModel.h \
	$(CSMINCDIR)/FourParameterCorrelationModel.h \
	$(VTSINCDIR)/SMManager.h \
	$(VTSINCDIR)/VTSMisc.h \
	$(VTSINCDIR)/tinyxml.h \
	$(VTSINCDIR)/constants.h \
	$(VTSINCDIR)/tokenizer.h
	$(CXX) $(CXXFLAGS)  -I$(CSMINCDIR) -I$(VTSINCDIR) vts.cpp \
	-o $(VTSOBJDIR)/vts.o

$(VTSOBJDIR)/SMManager.o    : SMManager.cpp \
	$(VTSINCDIR)/SMManager.h \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) SMManager.cpp \
		-o $(VTSOBJDIR)/SMManager.o

#add .cpp and .cc files
$(VTSPROJDIR)/libCSMPlugin.so    : \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/Model.h \
	$(CSMINCDIR)/Isd.h \
	$(CSMINCDIR)/NitfIsd.h \
	$(CSMINCDIR)/BytestreamIsd.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/RasterGM.h \
	$(CSMINCDIR)/Version.h \
	$(CSMINCDIR)/GeometricModel.h \
	$(CSMINCDIR)/FourParameterCorrelationModel.h
	( cd $(CSMDIR);gmake $(MKARGS) )

$(VTSOBJDIR)/compareParam.o    : compareParam.cpp \
	$(CSMINCDIR)/csm.h \
	$(VTSINCDIR)/VTSMisc.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) compareParam.cpp \
		-o $(VTSOBJDIR)/compareParam.o

$(VTSOBJDIR)/recordLog.o    : recordLog.cpp \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/BytestreamIsd.h \
	$(CSMINCDIR)/NitfIsd.h \
	$(VTSINCDIR)/VTSMisc.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) recordLog.cpp \
		-o $(VTSOBJDIR)/recordLog.o

$(VTSOBJDIR)/vts_isd.o      : vts_isd.cpp \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/Isd.h \
	$(CSMINCDIR)/BytestreamIsd.h \
	$(CSMINCDIR)/NitfIsd.h \
	$(VTSINCDIR)/VTSMisc.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) vts_isd.cpp \
		-o $(VTSOBJDIR)/vts_isd.o

$(VTSOBJDIR)/vts_misc.o     : vts_misc.cpp \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/Isd.h \
	$(CSMINCDIR)/Plugin.h \
	$(VTSINCDIR)/VTSMisc.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) vts_misc.cpp \
		-o $(VTSOBJDIR)/vts_misc.o
$(VTSOBJDIR)/tokenizer.o        : tokenizer.cpp $(VTSINCDIR)/tokenizer.h 
	$(CXX) $(CXXFLAGS)  -I$(VTSINCDIR) tokenizer.cpp -o $(VTSOBJDIR)/tokenizer.o

$(VTSOBJDIR)/SensorModelThreadSafe.o      : SensorModelThreadSafe.cpp \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(VTSINCDIR)/VTSMisc.h \
	$(VTSINCDIR)/tinyxml.h
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) SensorModelThreadSafe.cpp \
	-o $(VTSOBJDIR)/SensorModelThreadSafe.o

$(VTSOBJDIR)/tinyxml.o    : tinyxml.cpp $(VTSINCDIR)/tinyxml.h 
	$(CXX) $(CXXFLAGS) -I$(CSMINCDIR) -I$(VTSINCDIR) tinyxml.cpp -o $(VTSOBJDIR)/tinyxml.o

#------------------------------------------------------------------------------
clean :
	@echo GCC - $(GCC)
	@echo CXX - $(CXX)
	-rm -f $(VTSOBJDIR)/*.o $(VTSBINDIR)/vts $(VTSPROJDIR)/vts  $(VTSPROJDIR)/*.so *~*.so *~
	-rm -rf SunWS_cache
