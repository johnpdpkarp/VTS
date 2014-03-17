//#############################################################################
//
//    FILENAME:   StubSMPlugin.cpp
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    StubSMPlugin class.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//    NOTES:
//           Returns for each of the methods are passed in on the second line
//           of the command script. Following the returns is a error/warning/null 
//           indicator and an error type or warning type.
//
//           Error/warning/null indicator is defined as 0=Pass, 1=Warning, 2=Error 
//           and 3=NULL.
//
//           Error Type / Warning Type are intigers that map to the enumerated
//           WarningType and ErrorType defined in the header files Warning.h and
//           Error.h
//
//           The returned error messsage for each of the methods is on the
//           third line of the command script. It is free form ASCII.
//
//           Example1:  getPlatformIdentifier -c StubPlatformID
//                      StubPlatformID 0 0
//                      No_Error
//
//                      Passes with no errors or warnings.
//
//           Example2:  getPlatformIdentifier -c StubPlatformID
//                      StubPlatformID 1 2
//                      Warning_message
//
//                      Warning with Error/warning/null indicator=1,
//                      with a WarningType=2 and message of "Warning_message".
//
//           Example3:  getPlatformIdentifier -c StubPlatformID
//                      StubPlatformID 2 3
//                      Error_message
//
//                      Error with Error/warning/null indicator=2,
//                      with an ErrorType=3 and message of "Error_message".
//
//           Example4:  getModelState -c State_Value
//                      State_Value  3 0
//                      No_message
//
//                      NULL with Error/warning/null indicator=3   
//
//#############################################################################
#define STUB_LIBRARY

#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include "StubSMPlugin.h"
#include "StubSensorModel.h"
#include "Warning.h"
#include "Error.h"

#ifndef TESTVTS
#define TESTVTS 0
#endif


using namespace StubSensorPlugin;
using namespace StubSensor;

using namespace csm;

extern void reportWarningList(WarningList* warnings
				     , Warning::WarningType aWarningType
    				 , string text
    				 , string commandName);


#ifdef TESTAPIVERSION
const char* StubSMPlugin::PLUGIN_NAME  = "StubTestPlugin";
string StubSMPlugin::SENSOR_MODEL_NAME  ("STUB_APITEST_MODEL");
#else
const char* StubSMPlugin::PLUGIN_NAME  = "StubPlugin";
string StubSMPlugin::SENSOR_MODEL_NAME  ("STUB_SENSOR_MODEL");
#endif

const StubSMPlugin StubSMPlugin::theRegisteringObject;
string StubSMPlugin::mModelName = SENSOR_MODEL_NAME;

//*****************************************************************************
// StubSMPlugin::StubSMPlugin
//*****************************************************************************
StubSMPlugin::StubSMPlugin()
{
#if TESTVTS
  cout << "constructing a StubSMPlugin object\n";
#endif
}


//*****************************************************************************
// StubSMPlugin::getCsmVersion - tested
//*****************************************************************************
//This method returns the CSM API version that the plug-in was written to.
//
Version StubSMPlugin::getCsmVersion() const
{
   Version csmVersion = Version("1.1.2");
   string myname("StubSMPlugin::getCsmVersion");
   #ifdef TESTAPIVERSION
      csmVersion = Version("3.0.1.1");
   #else
      csmVersion = Version("3.0.1.0");
   #endif
   return csmVersion;
}

//*****************************************************************************
// StubSMPlugin::getPluginName - tested
//*****************************************************************************
//returns the plugin name.
//
string StubSMPlugin::getPluginName() const
{
	string pluginName = PLUGIN_NAME;
	return pluginName;
}

//*****************************************************************************
// StubSMPlugin::getManufacturer - tested
//*****************************************************************************
string StubSMPlugin::getManufacturer() const
{
   string manufacturer_name = "GENERAL_DYNAMICS"; 
   return manufacturer_name;
}

//*****************************************************************************
// StubSMPlugin::getReleaseDate - tested
//*****************************************************************************
string StubSMPlugin::getReleaseDate() const
{
   string release_date = "17760704"; 
   return release_date;
}

//*****************************************************************************
// StubSMPlugin::getNumModels - tested
//*****************************************************************************
size_t StubSMPlugin::getNumModels() const
{
   size_t n_sensor_models = 2; 
   return n_sensor_models;
}

//*****************************************************************************
// StubSMPlugin::getModelName - tested
//*****************************************************************************
string StubSMPlugin::getModelName(size_t modelIndex) const
{
   string myname("StubSMPlugin::getModelName");
#if TESTVTS
   cout << "    StubSMPlugin::getModelName called." << endl;
   cout << "      Passed values are: " << endl;
   cout 
        << "        modelIndex=" << modelIndex << endl;
#endif

  string smBase(SENSOR_MODEL_NAME);
  string modelName;
  switch (modelIndex)
  {
    case 0:
       modelName = smBase;
       break;
    case 1:
       modelName = smBase + "1";
       break;
    case 2:
       modelName = smBase + "2";
       break;
    case 3:
       modelName = smBase + "3";
       break;
    case 4:
       modelName = smBase + "4";
       break;
    case 5:
       modelName = smBase + "5";
       break;
    case 6:
       modelName = smBase + "6";
       break;
    case 7:
       modelName = smBase + "7";
       break;
    case 8:
       modelName = smBase + "8";
       break;
    case 9:
       modelName = smBase + "9";
       break;
    default:
       modelName = smBase + "N";
       break;
  }
  return modelName;
}

//*****************************************************************************
// StubSMPlugin::getModelFamily
//*****************************************************************************
string StubSMPlugin::getModelFamily(size_t modelIndex) const
{
   string modelFamily = CSM_RASTER_FAMILY;
   return modelFamily;
}

//*****************************************************************************
// StubSMPlugin::getModelVersion - tested
//*****************************************************************************
Version StubSMPlugin::getModelVersion(const string& modelName) const
{
   Version sensor_model_version = Version("2"); 
   return sensor_model_version;
}

//*****************************************************************************
// StubSMPlugin::canModelBeConstructedFromState - tested
//*****************************************************************************
bool StubSMPlugin::canModelBeConstructedFromState(
      const string& modelName,
      const string& modelState,
      WarningList* warnings) const
{
   bool constructible = true;
   string myname("StubSMPlugin::canModelBeConstructedFromState");
   if (0 != modelName.compare(mModelName)) 
   {
      constructible = false;
	  reportWarningList(warnings
		  , csm::Warning::UNKNOWN_WARNING
		  , "Sensor Model Name does not match"
		  , myname);
   }
   return constructible;
}

//*****************************************************************************
// StubSMPlugin::canModelBeConstructedFromISD - tested
//*****************************************************************************
bool StubSMPlugin::canModelBeConstructedFromISD(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
   bool constructible = true;
   string myname("StubSMPlugin::canModelBeConstructedFromISD");
   if (0 != modelName.compare(mModelName)) 
   {
      constructible = false;
	  reportWarningList(warnings
		  , csm::Warning::UNKNOWN_WARNING
		  , "Sensor Model Name does not match"
		  , myname);
   }
   return constructible;
}


//*****************************************************************************
// StubSMPlugin::constructModelFromState - tested
//*****************************************************************************
STUB_EXPORT_API Model* StubSMPlugin::constructModelFromState(
      const string& modelState,
      WarningList* warnings) const
{
   RasterGM* sensor_model = new StubSensor::StubSensorModel();
   theList.push_back(sensor_model);
   return sensor_model;
}

//*****************************************************************************
// StubSMPlugin::constructModelFromISD - tested
//*****************************************************************************
STUB_EXPORT_API Model* StubSMPlugin::constructModelFromISD(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
   RasterGM* sensor_model = new StubSensor::StubSensorModel();
   theList.push_back(sensor_model);
   return sensor_model;
}

//*****************************************************************************
// StubSMPlugin::getModelNameFromModelState - tested
//*****************************************************************************
string StubSMPlugin::getModelNameFromModelState(
      const string& modelState,
      WarningList* warnings) const
{
	   string sensor_model_name = "STUB_SENSOR_MODEL_FROM_STATE"; 
	   return sensor_model_name;
}

//*****************************************************************************
// StubSMPlugin::canISDBeConvertedToModelState - tested
//*****************************************************************************
bool StubSMPlugin::canISDBeConvertedToModelState(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
   bool convertable = true;
   string myname("StubSMPlugin::canISDBeConvertedToSensorModelState");
   if (0 != modelName.compare(mModelName)) 
   {
      convertable = false;
	  reportWarningList(warnings
		  , csm::Warning::UNKNOWN_WARNING
		  , "Sensor Model Name does not match"
		  , myname);
   }
   return convertable;
}

//*****************************************************************************
// StubSMPlugin::convertISDToModelState - tested
//*****************************************************************************
string StubSMPlugin::convertISDToModelState(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
   string myname("StubSMPlugin::convertISDToSensorModelState");
   string returned_sensor_model_state = "Converted ISD to Sensor Model State";
   if (0 != modelName.compare(mModelName)) 
   {
	  reportWarningList(warnings
		  , csm::Warning::UNKNOWN_WARNING
		  , "Sensor Model Name does not match"
		  , myname);
   }
   return returned_sensor_model_state;
}

