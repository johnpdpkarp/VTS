###############################################################################
#
#     FILENAME:   Makefile (StubSMPlugin for gmake)
#
#     DESCRIPTION:
#
#     This Makefile is used by gmake to build the vts StubSMPlugin plugin
#     (shared object) on Solaris and Linux using the WorkShop/Forte CC and
#     the gcc compilers.
#
#     NOTES:
#
###############################################################################

   CXX = CC
   CXXFLAGS1 = -c -g -D_FILE_OFFSET_BITS=64
   CXXFLAGS2 = -G -PIC -g 
   LDLIBS =  -ldl -lCstd
   SONAME = -h
ifeq ($(GCC), gcc)
   CXX = g++
   UN_GCC = _gcc
   CXXFLAGS1 = -c -g -D_FILE_OFFSET_BITS=64
   CXXFLAGS2 = -G -fPIC -g 
   LDLIBS =     -ldl
endif
ifeq ($(GCC), Linux)
   CXX = g++
   UN_GCC = _gcc
   CXXFLAGS1 = -c -g
   #CXXFLAGS2 = -shared -Wl -g 
   CXXFLAGS2 = -shared -g 
   LDLIBS = -ldl
   SONAME = -Wl,-soname,
endif

VTSPROJDIR = ..

CSMINCDIR = $(VTSPROJDIR)/CSM_include
OBJDIR = $(VTSPROJDIR)/CSM/object$(UN_GCC)


VTSINCDIR = $(VTSPROJDIR)/VTS_include

LIBPATH = StubSMPlugin/library
LIBDIR = $(VTSPROJDIR)

#------------------------------------------------------------------------------
all : $(LIBDIR)/StubSMPlugin.so 

#------------------------------------------------------------------------------
$(LIBDIR)/StubSMPlugin.so : $(OBJDIR)/StubSMPlugin.o $(OBJDIR)/StubSensorModel.o
	$(CXX)  $(CXXFLAGS2)   $(OBJDIR)/StubSMPlugin.o \
        $(OBJDIR)/StubSensorModel.o \
	-o $(LIBDIR)/StubSMPlugin.so 

#------------------------------------------------------------------------------
$(OBJDIR)/StubSMPlugin.o : StubSMPlugin.cpp \
	Makefile_SunOS \
	StubSensorModel.h \
	StubSMPlugin.h \
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
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) StubSMPlugin.cpp \
             -o $(OBJDIR)/StubSMPlugin.o

#------------------------------------------------------------------------------
$(OBJDIR)/StubSensorModel.o : StubSensorModel.cpp \
	Makefile_SunOS \
	StubSensorModel.h \
	$(CSMINCDIR)/Model.h \
	$(VTSINCDIR)/VTSMisc.h \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
        $(CSMINCDIR)/Isd.h \
        $(CSMINCDIR)/NitfIsd.h \
        $(CSMINCDIR)/BytestreamIsd.h \
        $(CSMINCDIR)/csm.h \
        $(CSMINCDIR)/RasterGM.h \
        $(CSMINCDIR)/Version.h \
        $(CSMINCDIR)/GeometricModel.h \
        $(CSMINCDIR)/FourParameterCorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) StubSensorModel.cpp \
	-o $(OBJDIR)/StubSensorModel.o

#------------------------------------------------------------------------------
clean :
	-rm -f $(OBJDIR)/*.o vts $(LIBDIR)/*.so $(VTSPROJDIR)/StubSMPlugin*.so *~
	-rm -rf SunWS_cache

