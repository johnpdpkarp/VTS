//#############################################################################
//
//    FILENAME:   StubSMPlugin.h
//
//    DESCRIPTION:
//
//    This file contains the definition for an example plugin's class derived
//    from class CSM::Plugin.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//    NOTES:
//    The static instance of the class is responsible for registering the class
//    with "the list" by invoking the appropriate base class constructor. It
//    does this by invoking its own private "int" constructor.
//
//#############################################################################
#ifndef __STUBSMPLUGIN_H
#define __STUBSMPLUGIN_H

#include <list>
#include "RasterGM.h"
#include "Plugin.h"
#include "Warning.h"
#include "Error.h"

using namespace csm;

#ifdef _WIN32
# ifdef STUB_LIBRARY
#  define STUB_EXPORT_API __declspec(dllexport)
# else
#  define STUB_EXPORT_API __declspec(dllimport)
# endif
#else
#  define STUB_EXPORT_API
#endif

namespace StubSensorPlugin  //----- create a namespace
{

class StubSMPlugin : public Plugin
{
public:

   //---
   // Constructors/Destructor
   //---

   virtual STUB_EXPORT_API ~StubSMPlugin() {}

   static const PluginList& getList();
   static const StubSMPlugin* findPlugin(const std::string& pluginName,
                                   WarningList* warnings = NULL);
   static void removePlugin(const std::string& pluginName,
                            WarningList* warnings = NULL);

   virtual STUB_EXPORT_API std::string getPluginName() const;
   virtual std::string getManufacturer() const;
   virtual std::string getReleaseDate() const;
   virtual Version getCsmVersion() const;
   virtual size_t getNumModels() const;
   virtual std::string getModelName(size_t modelIndex) const;
   virtual std::string getModelFamily(size_t modelIndex) const;
   virtual Version getModelVersion(const std::string& modelName) const;
   virtual bool canModelBeConstructedFromState(
      const std::string& modelName,
      const std::string& modelState,
      WarningList* warnings = NULL) const;
   virtual bool canModelBeConstructedFromISD(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;

   virtual STUB_EXPORT_API Model* constructModelFromState(
      const std::string& modelState,
      WarningList* warnings = NULL) const;
   virtual STUB_EXPORT_API Model* constructModelFromISD(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;

   virtual std::string getModelNameFromModelState(
      const std::string& modelState,
      WarningList* warnings = NULL) const;
   virtual bool canISDBeConvertedToModelState(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;
   virtual std::string convertISDToModelState(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;

private:

   //---
   // Types
   //---

   typedef std::list < RasterGM* > StubModels;

   //---
   // Constructors
   //---

   StubSMPlugin();
      //>This special constructor is responsible for registering this
      //plugin by invoking the special "int" base class
      //constructor. Since this is private, only a member of this
      //class, e.g. theRegisteringObject, can invoke it.

   //---
   // Data Members
   //---
   static STUB_EXPORT_API const char* PLUGIN_NAME;
      //> This data member is the name of this plugin.
      //<  

   static STUB_EXPORT_API std::string SENSOR_MODEL_NAME;
      //> This data member is the default name of the sensor model.
      //<  

   static STUB_EXPORT_API std::string mModelName;
      //> This data member is the current name of the sensor model.
      //<  

   mutable StubModels theList;

   static const StubSMPlugin theRegisteringObject;

}; // StubSMPlugin

}; //----- End of namespace

#endif // __STUBSMPLUGIN_H
