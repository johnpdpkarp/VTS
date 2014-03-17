##############################################################################
#
#     FILENAME:   Makefile for CSMPlugin
#
#     DESCRIPTION:
#
#     This Makefile is used by gmake to build 
#     libCSMPlugin.so on Solaris using the gcc or SUN compilers.
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
   CSHAREDFLAGS = -shared
   LDLIBS =     -ldl
endif

ifeq ($(GCC), Linux)
   CXX = g++ -m32
   UN_GCC = _gcc
   CXXFLAGS1 = -c -g -fPIC
   CXXFLAGS2 = -shared -g 
   CSHAREDFLAGS = -shared
   LDLIBS = -ldl
   SONAME = -Wl,-soname,
endif

VTSPROJDIR = ..

CSMINCDIR = $(VTSPROJDIR)/CSM_include
OBJDIR = $(VTSPROJDIR)/CSM/object$(UN_GCC)

#------------------------------------------------------------------------------
all : $(VTSPROJDIR)/libCSMPlugin.so 

##$(VTSPROJDIR)/libCSMFourParameterCorrelationModel.so 

$(VTSPROJDIR)/libCSMPlugin.so    : $(OBJDIR)/Plugin.o $(OBJDIR)/Version.o \
                $(OBJDIR)/GeometricModel.o $(OBJDIR)/RasterGM.o  \
                $(OBJDIR)/CorrelationModel.o $(OBJDIR)/Isd.o \
                $(OBJDIR)/FourParameterCorrelationModel.o \
                $(OBJDIR)/LinearDecayCorrelationModel.o Makefile

	$(CXX) $(CXXFLAGS2) $(OBJDIR)/Plugin.o $(OBJDIR)/Version.o \
                $(OBJDIR)/GeometricModel.o $(OBJDIR)/RasterGM.o \
                $(OBJDIR)/CorrelationModel.o $(OBJDIR)/Isd.o \
                $(OBJDIR)/FourParameterCorrelationModel.o \
                $(OBJDIR)/LinearDecayCorrelationModel.o \
	-o $(VTSPROJDIR)/libCSMPlugin.so $(SONAME)libCSMPlugin.so

$(VTSPROJDIR)/libCSMFourParameterCorrelationModel.so : $(OBJDIR)/FourParameterCorrelationModel.o Makefile
	$(CXX) $(CXXFLAGS2) $(OBJDIR)/FourParameterCorrelationModel.o \
	-o $(VTSPROJDIR)/libCSMFourParameterCorrelationModel.so \
	$(SONAME)libCSMFourParameterCorrelationModel.so
	#rm -f libCSMFourParameterCorrelationModel.so
	#ln -s $(VTSPROJDIR)/libCSMFourParameterCorrelationModel.so .

#------------------------------------------------------------------------
$(OBJDIR)/Plugin.o    : Plugin.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Plugin.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) Plugin.cpp \
                              -o $(OBJDIR)/Plugin.o

$(OBJDIR)/Version.o    : Version.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Version.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) Version.cpp \
                              -o $(OBJDIR)/Version.o

$(OBJDIR)/Isd.o    : Isd.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Isd.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) Isd.cpp \
                              -o $(OBJDIR)/Isd.o

$(OBJDIR)/GeometricModel.o    : GeometricModel.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/GeometricModel.h \
	$(CSMINCDIR)/Plugin.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) GeometricModel.cpp \
                              -o $(OBJDIR)/GeometricModel.o

$(OBJDIR)/RasterGM.o    : RasterGM.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/RasterGM.h \
	$(CSMINCDIR)/Plugin.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) RasterGM.cpp \
                              -o $(OBJDIR)/RasterGM.o

$(OBJDIR)/FourParameterCorrelationModel.o    : FourParameterCorrelationModel.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/FourParameterCorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) FourParameterCorrelationModel.cpp \
                              -o $(OBJDIR)/FourParameterCorrelationModel.o

$(OBJDIR)/LinearDecayCorrelationModel.o    : LinearDecayCorrelationModel.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/LinearDecayCorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) LinearDecayCorrelationModel.cpp \
                              -o $(OBJDIR)/LinearDecayCorrelationModel.o

$(OBJDIR)/CorrelationModel.o    : CorrelationModel.cpp Makefile \
	$(CSMINCDIR)/Error.h \
	$(CSMINCDIR)/Warning.h \
	$(CSMINCDIR)/csm.h \
	$(CSMINCDIR)/Plugin.h \
	$(CSMINCDIR)/CorrelationModel.h
	$(CXX) $(CXXFLAGS1) -I$(CSMINCDIR) CorrelationModel.cpp \
                              -o $(OBJDIR)/CorrelationModel.o

#------------------------------------------------------------------------------
clean :
	-rm -f $(OBJDIR)/*.o vts *.so $(VTSPROJDIR)/*.so *~
	-rm -rf SunWS_cache

