//#############################################################################
//
//    FILENAME:   ExampleSMPlugin.cpp
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    ExampleSMPlugin class.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//#############################################################################
#define EXAMPLE_LIBRARY

#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>

#include "ExampleSMPlugin.h"
#include "ExampleSensorModel.h"
#include "Warning.h"
#include "Error.h"

#ifndef TESTVTS
#define TESTVTS 0
#endif

using namespace ExampleSensorPlugin;

const char* ExampleSMPlugin::PLUGIN_NAME  = "ExamplePlugin";
const char* ExampleSMPlugin::SENSOR_MODEL_NAME  = "EXAMPLE_SENSOR_MODEL";
const ExampleSMPlugin ExampleSMPlugin::theRegisteringObject;

//*****************************************************************************
// ExampleSMPlugin::ExampleSMPlugin
//*****************************************************************************
ExampleSMPlugin::ExampleSMPlugin()
{
#if TESTVTS
  cout << "constructing an ExampleSMPlugin object";
#endif
}

//*****************************************************************************
// ExampleSMPlugin::constructModelFromState
//*****************************************************************************
EXAMPLE_EXPORT_API Model* ExampleSMPlugin::constructModelFromState(
      const string& modelState,
      WarningList* warnings) const
{
   string myname("ExampleSMPlugin::constructModelFromState");
   Model* result = new ExampleSensor::ExampleSensorModel();

   theList.push_back(result);
   return result;
}

//*****************************************************************************
// ExampleSMPlugin::constructModelFromISD
//*****************************************************************************
EXAMPLE_EXPORT_API Model* ExampleSMPlugin::constructModelFromISD(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
  string myname("ExampleSMPlugin::constructModelFromISD");
  Model* result = new ExampleSensor::ExampleSensorModel();
  
  theList.push_back(result);
  
  return result;
}

//*****************************************************************************
// ExampleSMPlugin::canModelBeConstructedFromState
//*****************************************************************************
bool ExampleSMPlugin::canModelBeConstructedFromState(
      const string& modelName,
      const string& modelState,
      WarningList* warnings) const
{
  bool constructible;
  string myname("ExampleSMPlugin::canModelBeConstructedFromState");
  cout << "*****  enter " <<myname << " " << __FILE__ << " " << __LINE__ << '\n';
  if (0 == modelName.compare(SENSOR_MODEL_NAME)) 


   {
      constructible = 1;
   }
   else
   {
      constructible = 0;
	  if(warnings != NULL)
	  {
		  Warning csmWarn(csm::Warning::UNKNOWN_WARNING, 
			       "Sensor Model Name does not match", myname);
		  warnings->push_back(csmWarn);
	  }
   }
   return constructible;
}

//*****************************************************************************
// ExampleSMPlugin::canModelBeConstructedFromISD
//*****************************************************************************
bool ExampleSMPlugin::canModelBeConstructedFromISD(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
	bool constructible;
	string myname("ExampleSMPlugin::canModelBeConstructedFromISD");
	if (0 == modelName.compare(SENSOR_MODEL_NAME)) 
	{
		constructible = 1;
	}
	else
	{
		constructible = 0;
		if(warnings != NULL)
		{
			Warning csmWarn(csm::Warning::UNKNOWN_WARNING, 
				"Sensor Model Name does not match", myname);
			warnings->push_back(csmWarn);
		}
	}
	return constructible;
}

//*****************************************************************************
// ExampleSMPlugin::getNumModels
//*****************************************************************************
size_t ExampleSMPlugin::getNumModels() const
{
  string myname("ExampleSMPlugin::getNumModels");
  size_t numModels = 1; 
  return numModels;
}

//*****************************************************************************
// ExampleSMPlugin::getModelName
//*****************************************************************************
string ExampleSMPlugin::getModelName(size_t modelIndex) const
{
  string myname("ExampleSMPlugin::getModelName");
  string modelName;
#if TESTVTS
  cout << "    ExampleSMPlugin::getModelName called." << endl;
  cout << "      Passed values are: " << endl;
  cout 
    << "        modelIndex=" << modelIndex << endl;
#endif

  string smBase(SENSOR_MODEL_NAME);

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
// ExampleSMPlugin::getModelNameFromModelState
//*****************************************************************************
string ExampleSMPlugin::getModelNameFromModelState(
      const string& modelState,
      WarningList* warnings) const
{
	return "";
}

//*****************************************************************************
// ExampleSMPlugin::getPluginName
//*****************************************************************************
EXAMPLE_EXPORT_API string ExampleSMPlugin::getPluginName() const
{
	string pluginName = PLUGIN_NAME;
	return pluginName;
}

string ExampleSMPlugin::getManufacturer() const
{
	string manuf = "none";
	return manuf;
}

string ExampleSMPlugin::getReleaseDate() const
{
	string x = "xx";
	return x;
}

Version ExampleSMPlugin::getCsmVersion() const
{
  string myname("ExampleSMPlugin::getCsmVersion");
  Version version("1.2.3"); 
  return version;
}

string ExampleSMPlugin::getModelFamily(size_t modelIndex) const
{
  string myname("ExampleSMPlugin::getModelFamily");
  string modelFamily = "model family"; 
  return modelFamily;
}

Version ExampleSMPlugin::getModelVersion(const string& modelName) const
{
  string myname("ExampleSMPlugin::getModelVersion");
  Version modelVersion = Version("1"); 
  return modelVersion;
}

bool ExampleSMPlugin::canISDBeConvertedToModelState(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
  string myname("ExampleSMPlugin::getNumModels");
  bool convertable = true; 
  return convertable;
}

string ExampleSMPlugin::convertISDToModelState(
      const Isd& imageSupportData,
      const string& modelName,
      WarningList* warnings) const
{
  string myname("ExampleSMPlugin::convertISDToModelState");
  string state = "model state"; 
  return state;
}
/*
string ExampleSMPlugin::getReleaseDate() const
Version ExampleSMPlugin::getCsmVersion() const
string ExampleSMPlugin::getModelNameFromModelState(
      const string& modelState,
      WarningList* warnings) const
   
*/
