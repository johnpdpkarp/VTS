###############################################################################
#
#     FILENAME:   Makefile (ExampleSMPlugin for gmake)
#
#     DESCRIPTION:
#
#     This Makefile is used by gmake to build the vts ExampleSMPlugin plugin
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

LIBPATH = ExampleSMPlugin/library
LIBDIR = $(VTSPROJDIR)

#------------------------------------------------------------------------------
all : $(LIBDIR)/ExampleSMPlugin.so 

#------------------------------------------------------------------------------
$(LIBDIR)/ExampleSMPlugin.so : $(OBJDIR)/ExampleSMPlugin.o $(OBJDIR)/ExampleSensorModel.o
	$(CXX)  $(CXXFLAGS2)   $(OBJDIR)/ExampleSMPlugin.o \
        $(OBJDIR)/ExampleSensorModel.o \
	-o $(LIBDIR)/ExampleSMPlugin.so 

#------------------------------------------------------------------------------
$(OBJDIR)/ExampleSMPlugin.o : ExampleSMPlugin.cpp \
	Makefile_SunOS \
	ExampleSensorModel.h \
	ExampleSMPlugin.h \
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
        $(CSMINCDIR)/LinearDecayCorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) ExampleSMPlugin.cpp \
               -o $(OBJDIR)/ExampleSMPlugin.o

#------------------------------------------------------------------------------
$(OBJDIR)/ExampleSensorModel.o : ExampleSensorModel.cpp \
	Makefile_SunOS \
	ExampleSensorModel.h \
	$(CSMINCDIR)/Model.h \
	$(VTSINCDIR)/VTSMisc.h \
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
        $(CSMINCDIR)/LinearDecayCorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) ExampleSensorModel.cpp \
	-o $(OBJDIR)/ExampleSensorModel.o

#------------------------------------------------------------------------------
clean :
	-rm -f $(OBJDIR)/*.o vts $(LIBDIR)/*.so $(VTSPROJDIR)/ExampleSMPlugin.so *~
	-rm -rf SunWS_cache

