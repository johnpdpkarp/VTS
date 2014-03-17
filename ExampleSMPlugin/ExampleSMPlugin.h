//#############################################################################
//
//    FILENAME:   ExampleSMPlugin.h
//
//    DESCRIPTION:
//
//    This file contains the definition for an example plugin's class derived
//    from class Plugin.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//    NOTES:
//
//    The static instance of the class is responsible for registering the class
//    with "the list" by invoking the appropriate base class constructor. It
//    does this by invoking its own private "int" constructor.
//
//#############################################################################
#ifndef __EXAMPLESMPLUGIN_H
#define __EXAMPLESMPLUGIN_H

#include <list>
#include "RasterGM.h"
#include "Plugin.h"
#include "Error.h"
#include "Warning.h"

using namespace csm;
//class RasterGM;

#ifdef _WIN32
# ifdef EXAMPLE_LIBRARY
#  define EXAMPLE_EXPORT_API __declspec(dllexport)
# else
#  define EXAMPLE_EXPORT_API __declspec(dllimport)
# endif
#else
#  define EXAMPLE_EXPORT_API
#endif

namespace ExampleSensorPlugin   //----- Define a Namespace
{

class ExampleSMPlugin : public Plugin
{
public:

   //---
   // Constructors/Destructor
   //---

   static const PluginList& getList();
   static const ExampleSMPlugin* findPlugin(const std::string& pluginName,
                                   WarningList* warnings = NULL);
   static void removePlugin(const std::string& pluginName,
                            WarningList* warnings = NULL);

	virtual EXAMPLE_EXPORT_API ~ExampleSMPlugin() {}

   virtual std::string getModelFamily(size_t modelIndex) const;

   // CSM Plugin Descriptors
   virtual std::string getManufacturer() const;
   virtual std::string getReleaseDate() const;
   virtual Version getCsmVersion() const;

   // Sensor Model Availability
   virtual size_t getNumModels() const;
   
   virtual std::string getModelName(size_t modelIndex) const;
   
   // Sensor Model Descriptors
   virtual Version getModelVersion(const std::string& modelName) const;

   virtual bool canModelBeConstructedFromISD(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;
   // If the sensor_model_name matches with the sensor model name
   // in ISD, then announce that the sensor model can be
   // constructed.

   virtual bool canModelBeConstructedFromState(
      const std::string& modelName,
      const std::string& modelState,
      WarningList* warnings = NULL) const;
   // If the sensor_model_name matches with the sensor model name
   // in state, then announce that the sensor model can be
   // constructed.

   virtual EXAMPLE_EXPORT_API Model* constructModelFromState(
      const std::string& modelState,
      WarningList* warnings = NULL) const;

   virtual EXAMPLE_EXPORT_API Model* constructModelFromISD(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;
   
   virtual std::string getModelNameFromModelState(
      const std::string& modelState,
      WarningList* warnings = NULL) const;
   
   // Image Support Data Conversions
   virtual bool canISDBeConvertedToModelState(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;
   
   virtual std::string convertISDToModelState(
      const Isd& imageSupportData,
      const std::string& modelName,
      WarningList* warnings = NULL) const;

   //---
   // Accessors
   //---

   virtual EXAMPLE_EXPORT_API std::string getPluginName() const;

private:

   //---
   // Types
   //---

   typedef std::list < Model* > ExampleModels;

   //---
   // Constructors
   //---

   ExampleSMPlugin();
      //>This special constructor is responsible for registering this plugin by
      // invoking the special "int" base class constructor. Since this is
      // private, only a member of this class, e.g. theRegisteringObject, can
      // invoke it.

   //---
   // Data Members
   //---
   static EXAMPLE_EXPORT_API const char* PLUGIN_NAME;
      //> This data member is the name of this plugin.
      //<  

   static EXAMPLE_EXPORT_API const char* SENSOR_MODEL_NAME;
      //> This data member is the name of the sensor model.
      //<  

   mutable ExampleModels theList;

   static const ExampleSMPlugin theRegisteringObject;

}; // ExampleSMPlugin

}; //----- End of Namespace

#endif // __EXAMPLESMPLUGIN_H
