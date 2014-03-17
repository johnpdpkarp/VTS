//#############################################################################
//
//    FILENAME:   StubSensorModel.cpp
//
//    DESCRIPTION:
//
//    Implementation of StubSensorModel class.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      09 Mar 2010  DSL   CCB Change Deleted DATA_NOT_AVAILABLE 
//      22 Oct 2010  DSL   CCB Change add getCurrentCrossCovarianceMatrix 
//                                    and getOriginalCrossCovarianceMatrix
//      25 Oct 2010  DSL   CCB Change add getNumGeometricCorrectionSwitches,
//                                        getGeometricCorrectionName,
//                                        getCurrentGeometricCorrectionSwitch,
//                                    and setCurrentGeometricCorrectionSwitch
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      23 Jan 2013  DSL   added error checking to getSensorPosition (1 & 2), 
//                         getSensorVelocity (1 & 2), and getIlluminationDirection
//                         added return of larger arrays in getAllSensorPartials (1&2)
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
#include <iostream>
#include <string>
#include <vector>
#include "StubSensorModel.h"
#include "Warning.h"
#include "Error.h"

#ifndef TESTVTS
//#define TESTVTS 0  todo: change to 0
#define TESTVTS 1
#endif

using namespace std;
using namespace csm;
using namespace StubSensor;
//extern SensorTypeAndMode EO_FRAME;

string parseSegment(string dataLine, int& beginIndex)
{
   int    endIndex;
   string segment = "";

   beginIndex = (int)dataLine.find_first_not_of(" \t", beginIndex);
   if(beginIndex > -1)
   {
      endIndex = (int)dataLine.find_first_of(" \t\n", beginIndex);

      segment = dataLine.substr(beginIndex, endIndex - beginIndex);
      beginIndex = endIndex;
   }
   return segment;
}

vector<string> getInputs(const string& myname)
{
   vector<string> inputArray;
   string         dataLine;
   int            beginIndex = 0;

   // Prompt for the desired error message
   cout << myname << ">> ";

   // Remove all the leading white spaces
   cin >> ws;

   getline(cin, dataLine);

   inputArray.push_back(parseSegment(dataLine, beginIndex));
   while(beginIndex != -1)
   {
      inputArray.push_back(parseSegment(dataLine, ++beginIndex));
   }

   return inputArray;
}

Warning getError(const int& errSwitch,
   const int& errEnum,
   const string& myname)
   throw               (Error)
{
   Warning csmWarn((Warning::WarningType)-1,"","");
   Error    csmErr;
   string      message="";

   // Prompt for the desired error message
   cout << myname << ">> ";

   // Remove all the leading white spaces
   cin >> ws;

   getline(cin, message);

   switch (errSwitch)
   {
      case STUBNONE:
      case STUBNULL:
         break;
      case STUBWARN:
		  csmWarn.setWarning(Warning::WarningType(errEnum),
             message,
             myname);
         break;
      case STUBERROR:
         csmErr.setError
            (
               Error::ErrorType(errEnum),
               message,
               myname);
         throw csmErr;
         break;
      default:
         csmErr.setError
            (Error::UNKNOWN_ERROR,
             "VTS invalid error switch value : " + errSwitch,
             myname);
         throw (csmErr);
   }
#if TESTVTS
   cout << endl << "   Returned function and error message:"
             << endl   << "      "
             << csmWarn.getFunction() << "/"
             << csmWarn.getMessage()
             << endl;
#endif

   return csmWarn;
}


void reportWarningList(WarningList* warnings, Warning csmWarn)
{
	if(warnings)
	{
		if(csmWarn.getWarning() != (Warning::WarningType)-1)
		{
			warnings->push_back(csmWarn);
		}
	}
}

void reportWarningList(WarningList* warnings
				     , Warning::WarningType aWarningType
    				 , string text
    				 , string commandName)
{
	if(warnings)
	{
			Warning csmWarn(aWarningType, text, commandName);
			warnings->push_back(csmWarn);
	}
}

void reportIncorrectNumParams(WarningList* warnings, int expected,int actual, string myname)
{
	cout << "        Incorrect # of return parameters: entered " 
               << expected << " requires " << actual << " !"<< endl;

     string text = "Internal VTS Warning - Incorrect # of return parameters in command";
	 reportWarningList(warnings, Warning::UNKNOWN_WARNING, text, myname);
}





//*****************************************************************************
// StubSensorModel::StubSensorModel
//*****************************************************************************
StubSensorModel::StubSensorModel()
{
   cout << "***constructing a sensor model\n";
   covM = new FourParameterCorrelationModel(3, 2);
}

// StubSensorModel::~StubSensorModel
//*****************************************************************************
StubSensorModel::~StubSensorModel()
{
	delete covM;
}

//*****************************************************************************
// StubSensorModel::getVersion - tested
//*****************************************************************************
//This method returns the CSM API version that the plug-in was written to.
Version StubSensorModel::getVersion() const
{
   #ifdef TESTAPIVERSION
      Version version = CURRENT_CSM_VERSIONp1;
   #else
      Version version = CURRENT_CSM_VERSION;
   #endif
   return version;
}

//*****************************************************************************
// StubSensorModel::getModelType - tested
//*****************************************************************************
string StubSensorModel::getModelType() const
{
   string myname = "StubSensorModel::getModelType";
   vector<string> inputArray = getInputs(myname);
   string modeltype;
#if TESTVTS
   cout << "  StubSensorModel::getModelType called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif
   modeltype = inputArray[0];
#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        modeltype=" << modeltype << endl;
#endif     
   return modeltype;
}

//*****************************************************************************
// StubSensorModel::getModelName2 - Tested
//*****************************************************************************
string StubSensorModel::getModelName() const
{
   string myname = "StubSensorModel::getModelName2";
   string name;
   int num_returns = 1;
   vector<string> inputArray = getInputs(myname);
#if TESTVTS
   cout << "  StubSensorModel::getModelName2 called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif
   name = inputArray[0];
#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        name=" << name << endl;
#endif     
   return name;
}

//*****************************************************************************
// StubSensorModel::getPedigree - tested
//*****************************************************************************
std::string StubSensorModel::getPedigree() const
{
   string pedigree = "";
   string         myname = "StubSensorModel::getPedigree";
   int            num_returns = 1;
   vector<string> inputArray = getInputs(myname);
  
#if TESTVTS
   cout << "    StubSensorModel::getPedigree called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif

   // Assign all of the parameters
   pedigree  = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        pedigree=" << pedigree << endl;
#endif

   return pedigree;
}

//*****************************************************************************
// StubSensorModel::getImageIdentifier - tested
//*****************************************************************************
string StubSensorModel::getImageIdentifier() const
{
   string imageId;
   string         myname = "StubSensorModel::getImageIdentifier";
   int            num_returns = 1;
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getImageIdentifier called." 
	     << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   imageId   = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        imageId=" << imageId << endl;
#endif     

   return imageId;
}

//*****************************************************************************
// StubSensorModel::setImageIdentifier - tested
//*****************************************************************************
void StubSensorModel::setImageIdentifier(const std::string& imageId,
                                   WarningList* warnings)
{
   string         myname = "StubSensorModel::setImageIdentifier";
   int            num_returns = 2;
   vector<string> inputArray = getInputs(myname);
   int            errSwitch;
   int            errEnum;

#if TESTVTS
   cout << "    StubSensorModel::setImageIdentifier called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        imageId=" << imageId << endl;
#endif     

   if(inputArray.size() == num_returns)
   {
     // Assign all of the parameters
     // NONE

     errSwitch = atoi(inputArray[0].c_str());
     errEnum   = atoi(inputArray[1].c_str());
	 reportWarningList(warnings, getError(errSwitch, errEnum, myname));
#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        NONE" << endl;
#endif
   }
   else
   {
     reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
   }

   return;
}

//*****************************************************************************
// StubSensorModel::getSensorIdentifier - tested
//*****************************************************************************
std::string StubSensorModel::getSensorIdentifier() const
{
   string         myname = "StubSensorModel::getSensorIdentifier";
   string sensorId;
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getSensorIdentifier called."  << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

     // Assign all of the parameters
     sensorId  = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        sensorId=" << sensorId.c_str() << endl;
#endif     

   return sensorId;
}


//*****************************************************************************
// StubSensorModel::getPlatformIdentifier - tested
//*****************************************************************************
std::string StubSensorModel::getPlatformIdentifier() const
{
   string         myname = "StubSensorModel::getPlatformIdentifier";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getPlatformIdentifier called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif

   // Assign all of the parameters
   string platformId = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        platformId=" << platformId << endl;
#endif     

   return platformId;
}

//*****************************************************************************
// StubSensorModel::getCollectionIdentifier - tested
//*****************************************************************************
std::string StubSensorModel::getCollectionIdentifier() const
{
   string         myname = "StubSensorModel::getCollectionIdentifier";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getCollectionIdentifier called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   string collectionId = inputArray[0];    

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        collectionId=" << collectionId << endl;
#endif     

   return collectionId;
}



//*****************************************************************************
// StubSensorModel::getParameterUnits
//*****************************************************************************
string StubSensorModel::getParameterUnits(int index) const
{
   string         myname = "StubSensorModel::getParameterUnits";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getParameterUnits called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        index = " << index << endl;
#endif     

   // Assign all of the parameters
   string units = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        units=" << units << endl;
#endif     

   return units;
}

//*****************************************************************************
// StubSensorModel::hasShareableParameters
//*****************************************************************************
bool StubSensorModel::hasShareableParameters() const
{
   string         myname = "StubSensorModel::hasShareableParameters";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::hasShareableParameters called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   int intsharable  = atoi(inputArray[0].c_str());
   bool sharable  = (intsharable != 0);

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        sharable=" << sharable << endl;
#endif     

	return sharable;
}

//*****************************************************************************
// StubSensorModel::getSensorType
//*****************************************************************************
string StubSensorModel::getSensorType() const
{
   string         myname = "StubSensorModel::getSensorType";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getSensorType called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   string type = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        type=" << type << endl;
#endif     

   return type;
}

//*****************************************************************************
// StubSensorModel::getSensorMode
//*****************************************************************************
string StubSensorModel::getSensorMode() const
{

   string         myname = "StubSensorModel::getSensorMode";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getSensorMode called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   string mode = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        mode=" << mode << endl;
#endif     

   return mode;
}

//*****************************************************************************
// StubSensorModel::getFamily - tested
//*****************************************************************************
//string StubSensorModel::getFamily() const
//{
//   string family = CSM_RASTER_FAMILY;
//   return family;
//}

//*****************************************************************************
// StubSensorModel::getReferencePoint - tested
//*****************************************************************************
EcefCoord StubSensorModel::getReferencePoint() const
{
   EcefCoord grndPt;
   string         myname = "StubSensorModel::getReferencePoint";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getReferencePoint called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   grndPt.x         = atof(inputArray[0].c_str());
   grndPt.y         = atof(inputArray[1].c_str());
   grndPt.z         = atof(inputArray[2].c_str());

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        x=" << grndPt.x << endl;
   cout << "        y=" << grndPt.y << endl;
   cout << "        z=" << grndPt.z << endl;
#endif     

   return grndPt;
}

//*****************************************************************************
// StubSensorModel::setReferencePoint - tested
//*****************************************************************************
void StubSensorModel::setReferencePoint(const EcefCoord& grndPt)
{
   string         myname = "StubSensorModel::setReferencePoint";

#if TESTVTS
   cout << "    StubSensorModel::setReferencePoint called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        x,y,z=" << grndPt.x  << "," << grndPt.y << "," << grndPt.z << endl;
#endif     

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        NONE" << endl;
#endif

   return;
}

//*****************************************************************************
// StubSensorModel::getReferenceDateAndTime - tested
//*****************************************************************************
string StubSensorModel::getReferenceDateAndTime() const
{
   string         myname = "StubSensorModel::getReferenceDateAndTime";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getReferenceDateAndTime called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   string date_and_time = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        date_and_time=" << date_and_time << endl;
#endif     

   return date_and_time;
}

//************************************************************************
// StubSensorModel::getModelState - tested
//************************************************************************
std::string StubSensorModel::getModelState() const
{
   string         myname = "StubSensorModel::getModelState";
   int            num_returns = 3;
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getModelState called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE" << endl;
#endif     

   // Assign all of the parameters
   string state     = inputArray[0];

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        state=" << state << endl;
#endif

   return state;
}


//*****************************************************************************
// StubSensorModel::groundToImage - tested
//*****************************************************************************
ImageCoord StubSensorModel::groundToImage(const EcefCoord& groundPt,
             double desired_precision,
             double* achieved_precision,
             WarningList* warnings) const
{
   string         myname = "StubSensorModel::groundToImage";
   int            num_returns = 5;
   vector<string> inputArray = getInputs(myname);
   int            errSwitch;
   int            errEnum;

   ImageCoord imagePt;

   double x = groundPt.x;
   double y = groundPt.y;
   double z = groundPt.z;

#if TESTVTS
   cout << "    StubSensorModel::groundToImage form 1 called."  << endl;
   cout << "      Passed values are: " << endl;
   cout << "        x,y,z=" << x  << "," << y << "," << z << endl;
   cout << "        desired_precision=" << desired_precision << endl;
#endif     

   if(inputArray.size() == num_returns) 
   {
     // Assign all of the parameters
     imagePt.line               = atof(inputArray[0].c_str());
     imagePt.samp               = atof(inputArray[1].c_str());
     *achieved_precision = atof(inputArray[2].c_str());
     errSwitch          = atoi(inputArray[3].c_str());
     errEnum            = atoi(inputArray[4].c_str());
	 reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
     cout << "      Returning values are: " << endl;
     cout << "        line=" << imagePt.line << endl;
     cout << "        sample=" << imagePt.samp << endl;
     cout << "        achieved_precision=" << *achieved_precision 
	       << endl;
#endif
   }
   else 
   {
     reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
   }

   return imagePt;
}


//*****************************************************************************
// StubSensorModel::groundToImage (covariance) - tested
//*****************************************************************************
ImageCoordCovar StubSensorModel::groundToImage(const EcefCoordCovar& groundPt,
                                         double desired_precision,
                                         double* achieved_precision,
                                         WarningList* warnings) const
{
	ImageCoordCovar icCov;

	string         myname = "StubSensorModel::groundToImage";
   int            num_returns = 9;
   vector<string> inputArray = getInputs(myname);
   int            errSwitch;
   int            errEnum;

#if TESTVTS
   cout << "    StubSensorModel::groundToImage form 2 called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
   cout << "        desired_precision=" << desired_precision << endl;
   cout << "        groundCovariance=" 
	    << groundPt.covariance[0]  << "," << groundPt.covariance[1]  << "," 
	    << groundPt.covariance[2]  << "," << groundPt.covariance[3]  << "," 
	    << groundPt.covariance[4]  << "," << groundPt.covariance[5]  << "," 
	    << groundPt.covariance[7]  << "," << groundPt.covariance[8]  << endl;
#endif     

   if(inputArray.size() == num_returns)
   {
     // Assign all of the parameters
     icCov.line               = atof(inputArray[0].c_str());
     icCov.samp             = atof(inputArray[1].c_str());
	 icCov.covariance[0] = atof(inputArray[3].c_str());
	 icCov.covariance[1] = atof(inputArray[4].c_str());
	 icCov.covariance[2] = atof(inputArray[5].c_str());
	 icCov.covariance[3] = atof(inputArray[6].c_str());
     *achieved_precision = atof(inputArray[2].c_str());
     errSwitch          = atoi(inputArray[7].c_str());
     errEnum            = atoi(inputArray[8].c_str());
	 reportWarningList(warnings, getError(errSwitch, errEnum, myname));
     
#if TESTVTS
     cout << "      Returning values are: " << endl;
     cout << "        line=" << icCov.line << endl;
     cout << "        sample=" << icCov.samp << endl;
     cout << "        imageCovariance=" 
		  << icCov.covariance[0]  << "," 
	      << icCov.covariance[1]  << endl
		  << "                        " 
		  << icCov.covariance[2]  << "," 
	      << icCov.covariance[3]  << endl;
     cout << "        achieved_precision=" << *achieved_precision 
		  << endl;
#endif     
   }
   else
   {
	   reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
   }

   return icCov;
}


//*****************************************************************************
// StubSensorModel::imageToGround - tested
//*****************************************************************************
EcefCoord StubSensorModel::imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desired_precision,
                                   double* achieved_precision,
                                   WarningList* warnings) const
{
	EcefCoord grndPt;
	string         myname = "StubSensorModel::imageToGround1";
	int            num_returns = 6;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::imageToGround form 1 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        height=" << height << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     


	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		grndPt.x           = atof(inputArray[0].c_str());
		grndPt.y           = atof(inputArray[1].c_str());
		grndPt.z           = atof(inputArray[2].c_str());
		*achieved_precision = atof(inputArray[3].c_str());
		errSwitch          = atoi(inputArray[4].c_str());
		errEnum            = atoi(inputArray[5].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        x=" << grndPt.x << endl;
		cout << "        y=" << grndPt.y << endl;
		cout << "        z=" << grndPt.z << endl;
		cout << "        achieved_precision=" << *achieved_precision 
			<< endl;
#endif
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}

	return grndPt;
}

	
//*****************************************************************************
// StubSensorModel::imageToGround (covariance) - tested
//*****************************************************************************
EcefCoordCovar StubSensorModel::imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desired_precision,
                                        double* achieved_precision,
                                        WarningList* warnings) const
{
	EcefCoordCovar grndPtCov;
	string         myname = "StubSensorModel::imageToGround2";
	int            num_returns = 15;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::imageToGround form 2 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        imageCovariance=" 
		 << imagePt.covariance[0]  << "," 
		 << imagePt.covariance[1]  << endl
		 << "                        " 
		 << imagePt.covariance[2]  << "," 
		 << imagePt.covariance[3]  << endl;
	cout << "        height=" << height << endl;
	cout << "        heightVariance=" << heightVariance << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		grndPtCov.x          = atof(inputArray[0].c_str());
		grndPtCov.y          = atof(inputArray[1].c_str());
		grndPtCov.z          = atof(inputArray[2].c_str());
		*achieved_precision  = atof(inputArray[3].c_str());
		grndPtCov.covariance[0]   = atof(inputArray[4].c_str());
		grndPtCov.covariance[1]   = atof(inputArray[5].c_str());
		grndPtCov.covariance[2]   = atof(inputArray[6].c_str());
		grndPtCov.covariance[3]   = atof(inputArray[7].c_str());
		grndPtCov.covariance[4]   = atof(inputArray[8].c_str());
		grndPtCov.covariance[5]   = atof(inputArray[9].c_str());
		grndPtCov.covariance[6]   = atof(inputArray[10].c_str());
		grndPtCov.covariance[7]   = atof(inputArray[11].c_str());
		grndPtCov.covariance[8]   = atof(inputArray[12].c_str());

		errSwitch            = atoi(inputArray[13].c_str());
		errEnum              = atoi(inputArray[14].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));
#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        x=" << grndPtCov.x << endl;
		cout << "        y=" << grndPtCov.y << endl;
		cout << "        z=" << grndPtCov.z << endl;
		cout << "        groundCovariance=" 
			 << grndPtCov.covariance[0]  << "," 
 			 << grndPtCov.covariance[1] << "," 
			 << grndPtCov.covariance[2] << endl
			 << "                         " 
			 << grndPtCov.covariance[3]  << "," 
			 << grndPtCov.covariance[4] << "," 
			 << grndPtCov.covariance[5] << endl
			 << "                         " 
			 << grndPtCov.covariance[6]  << "," 
			 << grndPtCov.covariance[7] << "," 
			 << grndPtCov.covariance[8] << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif     
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}

	return grndPtCov;
}

//*****************************************************************************
// StubSensorModel::imageToProximateImagingLocus - tested
//*****************************************************************************
EcefLocus StubSensorModel::imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desired_precision,
      double* achieved_precision,
      WarningList* warnings) const 
{
	EcefLocus locus;
	string         myname("StubSensorModel::imageToProximateImagingLocus");
	int            num_returns = 9;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::imageToProximateImagingLocus called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		*achieved_precision = atof(inputArray[0].c_str());
		locus.direction.x = atof(inputArray[1].c_str());
		locus.direction.y = atof(inputArray[2].c_str());
		locus.direction.z = atof(inputArray[3].c_str());
		locus.point.x = atof(inputArray[4].c_str());
		locus.point.y = atof(inputArray[5].c_str());
		locus.point.z = atof(inputArray[6].c_str());
		errSwitch     = atoi(inputArray[7].c_str());
		errEnum       = atoi(inputArray[8].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}
	return locus;
}

//*****************************************************************************
// StubSensorModel::imageToRemoteImagingLocus - tested
//*****************************************************************************
EcefLocus StubSensorModel::imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desired_precision,
      double* achieved_precision,
      WarningList* warnings) const 
{
	EcefLocus locus;
	string         myname ("StubSensorModel::imageToRemoteImagingLocus");
	int            num_returns = 9;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::imageToRemoteImagingLocus called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		*achieved_precision = atof(inputArray[0].c_str());
		locus.direction.x = atof(inputArray[1].c_str());
		locus.direction.y = atof(inputArray[2].c_str());
		locus.direction.z = atof(inputArray[3].c_str());
		locus.point.x = atof(inputArray[4].c_str());
		locus.point.y = atof(inputArray[5].c_str());
		locus.point.z = atof(inputArray[6].c_str());
		errSwitch           = atoi(inputArray[7].c_str());
		errEnum             = atoi(inputArray[8].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        locus=" << locus.direction.x  << "," 
			                     << locus.direction.y << ","  
			                     << locus.direction.z << endl
			 << "              " << locus.point.x  << ","  
			                     << locus.point.y << ","  
			                     << locus.point.z << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif     
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}
	return locus;
}

//*****************************************************************************
// StubSensorModel::getImageStart - tested
//*****************************************************************************
ImageCoord StubSensorModel::getImageStart() const
{
	ImageCoord imagePt;
	string         myname ("StubSensorModel::getImageStart");
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getImageStart called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

	// Assign all of the parameters
	imagePt.line = atof(inputArray[0].c_str());
	imagePt.samp = atof(inputArray[1].c_str());

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        line=" << imagePt.line << "," << "sample=" << "," << imagePt.samp << endl;
#endif     
	return imagePt;
}

//*****************************************************************************
// StubSensorModel::getImageSize - tested
//*****************************************************************************
ImageVector StubSensorModel::getImageSize() const
{
	ImageVector imageVec;
	string         myname = "StubSensorModel::getImageSize";
	int            num_returns = 2;
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "  StubSensorModel::getImageSize called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     
	
	// Assign all of the parameters
	imageVec.line = atoi(inputArray[0].c_str());
	imageVec.samp = atoi(inputArray[1].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        num_lines=" << imageVec.line << endl;
	cout << "        num_samples=" << imageVec.samp << endl;
#endif
	return imageVec;
}

//*****************************************************************************
// StubSensorModel::getValidHeightRange - tested
//*****************************************************************************
pair<double,double> StubSensorModel::getValidHeightRange() const
{
	pair<double,double> heightRg;
	string         myname = "StubSensorModel::validHeightRange";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::validHeightRange called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

	// Assign all of the parameters
	double minHeight = atof(inputArray[0].c_str());

	double maxHeight = atof(inputArray[1].c_str());
	heightRg = make_pair(minHeight, maxHeight);

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        minHeight=" << heightRg.first << endl;
	cout << "        maxHeight=" << heightRg.second << endl;
#endif     
	return heightRg;
}

//*****************************************************************************
// StubSensorModel::getValidImageRange - tested
//*****************************************************************************
pair<ImageCoord,ImageCoord> StubSensorModel::getValidImageRange() const
{
	pair<ImageCoord,ImageCoord> imageRg;
	string         myname = "StubSensorModel::getValidImageRange";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getValidImageRange called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

	// Assign all of the parameters     
	ImageCoord icmin;
	ImageCoord icmax;
	icmin.line = atof(inputArray[0].c_str());
	icmax.line = atof(inputArray[1].c_str());
	icmin.samp = atof(inputArray[2].c_str());
	icmax.samp = atof(inputArray[3].c_str());
	imageRg = make_pair(icmin, icmax);

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        minRow=" << imageRg.first.line << endl;
	cout << "        maxRow=" << imageRg.second.line << endl;
	cout << "        minCol=" << imageRg.first.samp << endl;
	cout << "        maxCol=" << imageRg.second.samp << endl;
#endif     
	return imageRg;
}


//*****************************************************************************
// StubSensorModel::getIlluminationDirection     todo: test for thrown Error
//*****************************************************************************
EcefVector StubSensorModel::getIlluminationDirection(const EcefCoord& gndPt) const
{
	EcefVector illumDir;
	string         myname = "StubSensorModel::getIlluminationDirection";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getIlluminationDirection called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        x,y,z=" << gndPt.x  << "," << gndPt.y << "," << gndPt.z << endl;
#endif     

	// Assign all of the parameters
	illumDir.x = atof(inputArray[0].c_str());
	illumDir.y = atof(inputArray[1].c_str());
	illumDir.z = atof(inputArray[2].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        direction_x=" << illumDir.x << endl;
	cout << "        direction_y=" << illumDir.y << endl;
	cout << "        direction_z=" << illumDir.z << endl;
#endif     
   int errSwitch = atoi(inputArray[3].c_str());
   int errEnum   = atoi(inputArray[4].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0

   return illumDir;
}

string StubSensorModel::getTrajectoryIdentifier() const
//*****************************************************************************
// StubSensorModel::getTrajectoryIdentifier - tested
//*****************************************************************************
{
	string trajectoryId;
	string         myname = "StubSensorModel::getTrajectoryIdentifier";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getTrajectoryIdentifier called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

	// Assign all of the parameters
	trajectoryId = inputArray[0];    

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        trajectoryId=" << trajectoryId << endl;
#endif     

   return trajectoryId;
}

//*****************************************************************************
// StubSensorModel::getImageTime - tested
//*****************************************************************************
double StubSensorModel::getImageTime(const ImageCoord& pt) const
{
	double time;
	string         myname = "StubSensorModel::getImageTime";
	int            num_returns = 1;
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getImageTime called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << pt.line << endl;
	cout << "        sample=" << pt.samp << endl;
#endif     

	// Assign all of the parameters
	time = atof(inputArray[0].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        time=" << time << endl;
#endif

	return time;
}

//*****************************************************************************
// StubSensorModel::getSensorPosition (from image coord)
//*****************************************************************************
EcefCoord StubSensorModel::getSensorPosition(const ImageCoord& pt) const  
{
	EcefCoord pos;
	string         myname = "StubSensorModel::getSensorPosition1";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getSensorPosition form 1 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << pt.line << endl;
	cout << "        sample=" << pt.samp << endl;
#endif     

	// Assign all of the parameters
	pos.x = atof(inputArray[0].c_str());
	pos.y = atof(inputArray[1].c_str());
	pos.z = atof(inputArray[2].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        x=" << pos.x << endl;
	cout << "        y=" << pos.y << endl;
	cout << "        z=" << pos.z << endl;
#endif     
   int errSwitch = atoi(inputArray[3].c_str());
   int errEnum   = atoi(inputArray[4].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0

	return pos;
}

//*****************************************************************************
// StubSensorModel::getSensorPosition (from time) - todo: test for thrown Error
//*****************************************************************************
EcefCoord StubSensorModel::getSensorPosition(double time) const   
{
	EcefCoord pos;
	string         myname = "StubSensorModel::getSensorPosition2";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getSensorPosition form 2 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        time=" << time << endl;
#endif     

	// Assign all of the parameters
	pos.x = atof(inputArray[0].c_str());
	pos.y = atof(inputArray[1].c_str());
	pos.z = atof(inputArray[2].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        x=" << pos.x << endl;
	cout << "        y=" << pos.y << endl;
	cout << "        z=" << pos.z << endl;
#endif     
   int errSwitch = atoi(inputArray[3].c_str());
   int errEnum   = atoi(inputArray[4].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0

	return pos;
}

//*****************************************************************************
// StubSensorModel::getSensorVelocity (from image coord) - todo: test for thrown Error
//*****************************************************************************
EcefVector StubSensorModel::getSensorVelocity(const ImageCoord& pt) const
{
	EcefVector vel;
	string         myname = " StubSensorModel::getSensorVelocity1";
	int            num_returns = 3;
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getSensorVelocity form 1 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << pt.line << endl;
	cout << "        sample=" << pt.samp << endl;
#endif     

	// Assign all of the parameters
	vel.x        = atof(inputArray[0].c_str());
	vel.y        = atof(inputArray[1].c_str());
	vel.z        = atof(inputArray[2].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        vx=" << vel.x << endl;
	cout << "        vy=" << vel.y << endl;
	cout << "        vz=" << vel.z << endl;
#endif     
   int errSwitch = atoi(inputArray[3].c_str());
   int errEnum   = atoi(inputArray[4].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0

	return vel;
}

//*****************************************************************************
// StubSensorModel::getSensorVelocity (from time) - todo: test for thrown Error
//*****************************************************************************
EcefVector StubSensorModel::getSensorVelocity(double time) const 
{
	EcefVector vel;
	string         myname = " StubSensorModel::getSensorVelocity2";
	int            num_returns = 3;
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getSensorVelocity form 2 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        time=" << time << endl;
#endif     

// Assign all of the parameters
	vel.x        = atof(inputArray[0].c_str());
	vel.y        = atof(inputArray[1].c_str());
	vel.z        = atof(inputArray[2].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        vx=" << vel.x << endl;
	cout << "        vy=" << vel.y << endl;
	cout << "        vz=" << vel.z << endl;
#endif     
   int errSwitch = atoi(inputArray[3].c_str());
   int errEnum   = atoi(inputArray[4].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0

	return vel;
}

//*****************************************************************************
// StubSensorModel::getNumParameters - tested
//*****************************************************************************
int StubSensorModel::getNumParameters() const
{
	int numParams;
	string         myname = "StubSensorModel::getNumParameters";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getNumParameters called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

	// Assign all of the parameters
	numParams = atoi(inputArray[0].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        numParams=" << numParams << endl;
#endif

	return numParams;
}

//*****************************************************************************
// StubSensorModel::getParameter ???
//*****************************************************************************
GeometricModel::Parameter StubSensorModel::getParameter(int index) const
{
	Parameter p;
	string         myname = "StubSensorModel::getParameter";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getParameter called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index:" << index << endl;
#endif     

	// Assign all of the parameters
	string pname = inputArray[0];
	double pvalue = atof(inputArray[1].c_str());
	string punits = inputArray[2];
	
	p = Parameter(pname, pvalue, punits, param::NONE,  SharingCriteria());
#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        pname=" << p.name << endl;
	cout << "        pvalue=" << p.value << endl;
	cout << "        punits=" << p.units << endl;
#endif

	return p;   
}

//*****************************************************************************
// StubSensorModel::setParameter  ???
//*****************************************************************************
//void StubSensorModel::setParameter(int index, const Parameter& param)
//{
//   setParameterValue (index,param.value);
//   setParameterType  (index,param.type);
//}



//*****************************************************************************
// StubSensorModel::getParameterName - tested
//*****************************************************************************
string StubSensorModel::getParameterName(int index) const
{
	string         name;
	string         myname = "StubSensorModel::getParameterName";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getParameterName called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	// Assign all of the parameters
	name      = inputArray[0];

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        name=" << name << endl;
#endif

	return name;
}


//*****************************************************************************
// StubSensorModel::isParameterShareable - tested
//*****************************************************************************
bool StubSensorModel::isParameterShareable(int index) const
{
	bool shareable;
	string         myname = "StubSensorModel::isParameterShareable";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::isParameterShareable called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	// Assign all of the parameters
	if (atoi(inputArray[0].c_str()) == 0)
		shareable = false;
	else
		shareable = true;

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        shareable=" << shareable << endl;
#endif     
	return shareable;
}

//*****************************************************************************
// StubSensorModel::getParameterSharingCriteria - ???
//*****************************************************************************
csm::SharingCriteria StubSensorModel::getParameterSharingCriteria(int index) const 
{
	csm::SharingCriteria criteria;
	string         myname = "StubSensorModel::getParameterSharingCriteria";
	vector<string> inputArray = getInputs(myname);
	int asize = inputArray.size();

#if TESTVTS
	cout << "    StubSensorModel::getParameterSharingCriteria called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     
    int i = 0;
	// Assign all of the parameters
	if(asize > i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesName = false
	                                    : criteria.matchesName = true; 
	if(asize > ++i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesSensorID = false
	                                    : criteria.matchesSensorID = true;
	if(asize > ++i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesPlatformID = false
	                                    : criteria.matchesPlatformID = true;
	if(asize > ++i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesCollectionID = false
	                                    : criteria.matchesCollectionID = true;
	if(asize > ++i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesTrajectoryID = false
	                                    : criteria.matchesTrajectoryID = true;
	if(asize > ++i)
       atoi(inputArray[i].c_str()) == 0 ? criteria.matchesDateTime = false
	                                    : criteria.matchesDateTime = true;
	if(asize > ++i)
       criteria.maxTimeDelta = atof(inputArray[i].c_str());

#if TESTVTS
		cout << "      Returning values are: " << endl;
			cout << "       matchesName="<< criteria.matchesName << endl;
			cout << "       matchesSensorID="<< criteria.matchesSensorID << endl;
			cout << "       matchesPlatformID="<< criteria.matchesPlatformID << endl;
			cout << "       matchesCollectionID="<< criteria.matchesCollectionID << endl;
			cout << "       matchesTrajectoryID="<< criteria.matchesTrajectoryID << endl;
			cout << "       matchesDateTime="<< criteria.matchesDateTime << endl;
			cout << "       maxTimeDelta="<< criteria.maxTimeDelta << endl;
#endif     
	return criteria;
}

//*****************************************************************************
// StubSensorModel::getParameterValue - tested
//*****************************************************************************
double StubSensorModel::getParameterValue(int index) const
{
	double value;
	string         myname = "StubSensorModel::getParameterValue";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getParameterValue called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	// Assign all of the parameters
	value     = atof(inputArray[0].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        value=" << value << endl;
#endif     

	return value;
}
   
//*****************************************************************************
// StubSensorModel::setParameterValue - tested
//*****************************************************************************
void StubSensorModel::setParameterValue(int index, double value)
{
	string         myname = "StubSensorModel::setParameterValue";

#if TESTVTS
	cout << "    StubSensorModel::setParameterValue called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
	cout << "        value=" << value << endl;
#endif     

	// Assign all of the parameters
	// NONE

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        NONE" << endl;
#endif
	return;
}

//*****************************************************************************
// StubSensorModel::getParameterType - tested
//*****************************************************************************
param::Type StubSensorModel::getParameterType(int index) const
{
	param::Type value;
	string         myname = "StubSensorModel::getParameterType";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getParameterType called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	// Assign all of the parameters
	value     = (param::Type) atoi(inputArray[0].c_str());

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        value=" << value << endl;
#endif     
	return value;
}

//*****************************************************************************
// StubSensorModel::setParameterType - tested
//*****************************************************************************
void StubSensorModel::setParameterType(int index, param::Type pType)
{
	string         myname = "StubSensorModel::setParameterType";

#if TESTVTS
	cout << "    StubSensorModel::setParameterType called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
	cout << "        parameterType=" << pType << endl;
#endif     

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        None"<< endl;
#endif     

	return;
}


//*****************************************************************************
// StubSensorModel::computeGroundPartials - tested
//*****************************************************************************
vector<double> StubSensorModel::computeGroundPartials(const EcefCoord& groundPt) const
{
	vector<double> partials;

	string         myname = "StubSensorModel::computeGroundPartials";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::computeGroundPartials called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
#endif

	// Assign all of the parameters
	partials.push_back(atof(inputArray[0].c_str()));
	partials.push_back(atof(inputArray[1].c_str()));
	partials.push_back(atof(inputArray[2].c_str()));
	partials.push_back(atof(inputArray[3].c_str()));
	partials.push_back(atof(inputArray[4].c_str()));
	partials.push_back(atof(inputArray[5].c_str()));

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        partials=" << partials[0]  << "," 
                           		<< partials[1] << "," 
								<< partials[2] << endl
								<< "                 " 
								<< partials[3]  << "," 
								<< partials[4] << "," 
								<< partials[5] << endl;
#endif     

	return partials;
}

//*****************************************************************************
// StubSensorModel::computeSensorPartials form 1 - tested
//*****************************************************************************
RasterGM::SensorPartials StubSensorModel::computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	SensorPartials partials;
	string         myname = "StubSensorModel::computeSensorPartials";
	int            num_returns = 5;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::computeSensorPartials form 1 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		partials.first = atof(inputArray[0].c_str());
		partials.second = atof(inputArray[1].c_str());
		*achieved_precision = atof(inputArray[2].c_str());
		errSwitch          = atoi(inputArray[3].c_str());
		errEnum            = atoi(inputArray[4].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        line_partial=" << partials.first << endl;
		cout << "        sample_partial=" << partials.second << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif     
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}
	return partials;
}

//*****************************************************************************
// StubSensorModel::computeSensorPartials form 2 - tested
//*****************************************************************************
RasterGM::SensorPartials StubSensorModel::computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	SensorPartials partials;
	string         myname = "StubSensorModel::computeSensorPartials";
	int            num_returns = 5;
	vector<string> inputArray = getInputs(myname);
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::computeSensorPartials form 2 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;   cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if(inputArray.size() == num_returns)
	{
		// Assign all of the parameters
		partials.first = atof(inputArray[0].c_str());
		partials.second = atof(inputArray[1].c_str());
		*achieved_precision = atof(inputArray[2].c_str());
		errSwitch          = atoi(inputArray[3].c_str());
		errEnum            = atoi(inputArray[4].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        line_partial=" << partials.first << endl;
		cout << "        sample_partial=" << partials.second << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif
	}
	else
	{
		reportIncorrectNumParams(warnings, inputArray.size(),num_returns, myname);
	}

	return partials;
}

//*****************************************************************************
// StubSensorModel::computeAllSensorPartials form 1
//*****************************************************************************
vector<RasterGM::SensorPartials> StubSensorModel::computeAllSensorPartials(
                const EcefCoord& groundPt,
                param::Set pSet,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	vector<RasterGM::SensorPartials> partials;
	string         myname = "StubSensorModel::computeAllSensorPartials";
	vector<string> inputArray = getInputs(myname);
	int            num_returns = inputArray.size();
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::computeAllSensorPartials form 1 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
	cout << "        pSet=" << pSet << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

//  num_returns must be > 4 and odd
	if((num_returns > 4) && (num_returns == num_returns / 2 * 2 + 1 ) ) 
//	if((int)inputArray.size() >= num_returns) 
	{
		// Assign all of the parameters
		int i=0;
		while(i< num_returns - 3)
		{
           SensorPartials part;
           part.first = atof(inputArray[i++].c_str());
           part.second = atof(inputArray[i++].c_str());
           partials.push_back(part);
		}
		*achieved_precision = atof(inputArray[i++].c_str());
		errSwitch          = atoi(inputArray[i++].c_str());
		errEnum            = atoi(inputArray[i++].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        line_partial=" << partials[0].first << endl;
		cout << "        sample_partial=" << partials[0].second << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif
	}
	else
	{
        int expectedSize = 5;
		if(num_returns >5)
		{
			expectedSize = num_returns + 1;
		}
		reportIncorrectNumParams(warnings, num_returns, expectedSize, myname);
	}
	return partials;
}

//*****************************************************************************
// StubSensorModel::computeAllSensorPartials form 2 - ???
//*****************************************************************************
vector<RasterGM::SensorPartials> StubSensorModel::computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                param::Set pSet,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	vector<RasterGM::SensorPartials> partials;
	string         myname = "StubSensorModel::computeAllSensorPartials";
	vector<string> inputArray = getInputs(myname);
	int            num_returns = inputArray.size();
	int            errSwitch;
	int            errEnum;

#if TESTVTS
	cout << "    StubSensorModel::computeAllSensorPartials form 2 called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line=" << imagePt.line << endl;
	cout << "        sample=" << imagePt.samp << endl;
	cout << "        x,y,z=" << groundPt.x  << "," << groundPt.y << "," << groundPt.z << endl;
	cout << "        pSet=" << pSet << endl;
	cout << "        desired_precision=" << desired_precision << endl;
#endif     

	if((num_returns > 4) && (num_returns == num_returns / 2 * 2 + 1 ) )
	{
		// Assign all of the parameters
		int i=0;
		while(i< num_returns - 3)
		{
           SensorPartials part;
           part.first = atof(inputArray[i++].c_str());
           part.second = atof(inputArray[i++].c_str());
           partials.push_back(part);
		}
        *achieved_precision = atof(inputArray[i++].c_str());
		errSwitch          = atoi(inputArray[i++].c_str());
		errEnum            = atoi(inputArray[i++].c_str());
		reportWarningList(warnings, getError(errSwitch, errEnum, myname));

#if TESTVTS
		cout << "      Returning values are: " << endl;
		cout << "        line_partial=" << partials[0].first << endl;
		cout << "        sample_partial=" << partials[0].second << endl;
		cout << "        achieved_precision=" << *achieved_precision << endl;
#endif
	}
	else
	{
        int expectedSize = 5;
        if(num_returns >5)
        {
           expectedSize = num_returns + 1;
        }
        reportIncorrectNumParams(warnings, num_returns, expectedSize, myname);
	}
	return partials;
}

//*****************************************************************************
// StubSensorModel::getParameterCovariance - tested
//*****************************************************************************
double StubSensorModel::getParameterCovariance(int index1,
                                                int index2) const 
{
   double covariance;
   string         myname = "StubSensorModel::getParameterCovariance";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getParameterCovariance called" << endl;
   cout << "      Passed values are: " << endl;
   cout << "        index1=" << index1 << endl;
   cout << "        index2=" << index2 << endl;
#endif     
 
     // Assign all of the parameters
     covariance = atof(inputArray[0].c_str());
#if TESTVTS
	 cout << "      Returning values are: " << endl;
	 cout << "        covariance=" << covariance << endl;
#endif     

	 return covariance;
}

//*****************************************************************************
// StubSensorModel::setParameterCovariance - tested
//*****************************************************************************
void StubSensorModel::setParameterCovariance(int index1,
                                              int index2,
                                              double covariance)
{
   string         myname = "StubSensorModel::setParameterCovariance";

#if TESTVTS
   cout << "    StubSensorModel::setParameterCovariance called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        index1=" << index1 << endl;
   cout << "        index2=" << index2 << endl;
   cout << "        covariance=" << covariance << endl;
#endif     

#if TESTVTS
     cout << "      Returning values are: " << endl;
     cout << "        NONE" << endl;
#endif

   return;
}

//*****************************************************************************
// StubSensorModel::getNumGeometricCorrectionSwitches xc
//*****************************************************************************
int StubSensorModel::getNumGeometricCorrectionSwitches() const
{
	string         myname = "StubSensorModel::getNumGeometricCorrectionSwitches";
	vector<string> inputArray = getInputs(myname);
	int number = atoi(inputArray[0].c_str());

#if TESTVTS
	cout << "    StubSensorModel::getNumGeometricCorrectionSwitches called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        number=" << number << endl;
#endif

	return number;
}


//*********************************************************************
// StubSensorModel::getGeometricCorrectionName - tested
//***********************************************************************
std::string StubSensorModel::getGeometricCorrectionName(int index) const
{
    string myname("StubSensorModel::getGeometricCorrectionName");
    vector<string> inputArray = getInputs(myname);
 
    string  name      = inputArray[0];
#if TESTVTS
    cout << "    StubSensorModel::getGeometricCorrectionName called." << endl;
    cout << "      Passed values are: " << endl;
    cout << "        index=" << index << endl;
#endif     

#if TESTVTS
    cout << "      Returning values are: " << endl;
    cout << "        name=" << name << endl;
#endif     
 
    return name;
 }


//*****************************************************************************
// StubSensorModel::setGeometricCorrectionSwitch - tested
//*****************************************************************************
void StubSensorModel::setGeometricCorrectionSwitch(int index,
                                                    bool value,
                                                    param::Type pType)
{
	string         myname = "StubSensorModel::setGeometricCorrectionSwitch";

#if TESTVTS
	cout << "StubSensorModel::setGeometricCorrectionSwitch called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	if (value == false)
		cout << "        value= false" << endl;
	else
		cout << "        value= true" << endl;
	cout << "        parameterType=" << pType << endl;

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        NONE" << endl;
#endif
	return;
}

//*****************************************************************************
// StubSensorModel::getGeometricCorrectionSwitch - tested
//*****************************************************************************
bool StubSensorModel::getGeometricCorrectionSwitch(int index) const
{
	string         myname = "StubSensorModel::getGeometricCorrectionSwitch";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getGeometricCorrectionSwitch called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        index=" << index << endl;
#endif     

	bool correctionSwitch;

	if (atoi(inputArray[0].c_str()) == 0)
		correctionSwitch = false;
	else
		correctionSwitch = true;

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        correctionSwitch=" << correctionSwitch << endl;
#endif     

	return correctionSwitch;
}

//*****************************************************************************
// StubSensorModel::getCrossCovarianceMatrix ???
//*****************************************************************************
vector<double> StubSensorModel::getCrossCovarianceMatrix(
          const GeometricModel& comparisonModel,
          param::Set pSet,
          const GeometricModelList& otherModels) const 
{
	vector<double> crossCovarianceMatrix;
	string         myname = "StubSensorModel::getCrossCovarianceMatrix";
	vector<string> inputArray = getInputs(myname);

	cout << "      Returning values are: " << endl;
	cout << "        pSet=" << pSet << endl;
	cout << "        and models to be compared " << endl;

	int M = inputArray.size();

	for(int nn=0;nn<M;nn++)
	{
		double val = atof(inputArray[nn].c_str());
		crossCovarianceMatrix.push_back(val);
	}

	return crossCovarianceMatrix;
}

//*****************************************************************************
// StubSensorModel::getCovarianceModel xc
//*****************************************************************************
CorrelationModel& StubSensorModel::getCorrelationModel() const
{
	CorrelationModel* retCovM = NULL;
	string         myname = "StubSensorModel::getCovarianceModel";

#if TESTVTS
	cout << "    StubSensorModel::getCovarianceModel called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        NONE" << endl;
#endif     

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        covarianceModel object" <<  endl;
#endif     

	   retCovM = (CorrelationModel*)covM;

	   return *retCovM;
}

//*****************************************************************************
// StubSensorModel::getUnmodeledError - tested
//*****************************************************************************
vector<double> StubSensorModel::getUnmodeledError(const ImageCoord& pt) const
{
	vector<double> covariance;
	string         myname = "StubSensorModel::getUnmodeledError";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getUnmodeledError called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        line,sample=" << pt.line  << "," << pt.samp << endl;
#endif

	// Assign all of the parameters
	for(int i=0;i<4;i++)
	{
		double cov = atof(inputArray[i].c_str());
		covariance.push_back(cov);
	}

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        covariance=" << covariance[0]  << "," << covariance[1] << endl;
	cout << "                 " << covariance[2]  << "," << covariance[3] << endl;
#endif     

	return covariance;
}

//*****************************************************************************
// StubSensorModel::getUnmodeledCrossCovariance - tested
//*****************************************************************************
vector<double> StubSensorModel::getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const 
{
	vector<double> xCov;
	string         myname = "StubSensorModel::getUnmodeledCrossCovariance";
	vector<string> inputArray = getInputs(myname);

#if TESTVTS
	cout << "    StubSensorModel::getUnmodeledCrossCovariance called." << endl;
	cout << "      Passed values are: " << endl;
	cout << "        pt1Line,pt1Sample=" << pt1.line  << "," << pt1.samp << endl;
	cout << "        pt2Line,pt2Sample=" << pt2.line  << "," << pt2.samp << endl;
#endif

	// Assign all of the parameters
	for(int i=0;i<4;i++)
	{
		double crCov = atof(inputArray[i].c_str());
		xCov.push_back(crCov);
	}

#if TESTVTS
	cout << "      Returning values are: " << endl;
	cout << "        crossCovariance=" << xCov[0]  << "," << xCov[1] << endl;
	cout << "                 " << xCov[2]  << "," << xCov[3] << endl;
#endif     

	return xCov;
}

//---
// Sensor Model Information
//---

//*****************************************************************************
// StubSensorModel::replaceModelState ???
//*****************************************************************************
void StubSensorModel::replaceModelState(const std::string& state)
{
   string         myname = "StubSensorModel::replaceModelState";
   int            errSwitch;
   int            errEnum;
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::replaceModelState called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        state=" << state << endl;
#endif     

   // Assign all of the parameters
   // NONE

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        NONE" << endl;
#endif
   errSwitch = atoi(inputArray[0].c_str());
   errEnum   = atoi(inputArray[1].c_str());
   getError(errSwitch, errEnum, myname);   // throws error if errSwitch != 0
   return;
}

//*****************************************************************************
// StubSensorModel::getParameters ???
//*****************************************************************************
std::vector<GeometricModel::Parameter> StubSensorModel::getParameters(param::Set pSet) const
{
   std::vector<GeometricModel::Parameter> params;
   GeometricModel::Parameter p1;
   GeometricModel::Parameter p2;
   string         myname = "StubSensorModel::getParameters";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getParameters called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        NONE " << endl;
#endif

   // Assign all of the parameters
   string pname = inputArray[0];
   double pvalue = atof(inputArray[1].c_str());
   string punits = inputArray[2];
   p1 = Parameter(pname, pvalue, punits, param::NONE,  SharingCriteria());
   pname = inputArray[3];
   pvalue = atof(inputArray[4].c_str());
   punits = inputArray[5];
   p2 = Parameter(pname, pvalue, punits, param::NONE,  SharingCriteria());
	
   params.push_back(p1);
   params.push_back(p2);

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        p1.pname=" << p1.name << endl;
   cout << "        p1.pvalue=" << p1.value << endl;
   cout << "        p1.punits=" << p1.units << endl;
   cout << "        p2.pname=" << p2.name << endl;
   cout << "        p2.pvalue=" << p2.value << endl;
   cout << "        p2.punits=" << p2.units << endl;
#endif

   return params;
}

//*****************************************************************************
// StubSensorModel::getParameterSetIndices ???
//*****************************************************************************
std::vector<int> StubSensorModel::getParameterSetIndices(param::Set pSet) const
{
   std::vector<int> indices;
   string         myname = "StubSensorModel::getParameterSetIndices";
   vector<string> inputArray = getInputs(myname);

#if TESTVTS
   cout << "    StubSensorModel::getParameterSetIndices called." << endl;
   cout << "      Passed values are: " << endl;
   cout << "        pSet=" << pSet << endl;
#endif

   // Assign all of the parameters
   // NONE

   for (vector<string>::iterator iter=inputArray.begin();iter!=inputArray.end();iter++)
   {
	   int ind = atoi((*iter).c_str());
	   indices.push_back(ind);
   }

#if TESTVTS
   cout << "      Returning values are: " << endl;
   cout << "        NONE" << endl;
   for (vector<int>::iterator iter=indices.begin();iter!=indices.end();iter++)
   {
	   cout << *iter << ",";
   }
#endif
   return indices;
}
