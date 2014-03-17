//#############################################################################
//
//    FILENAME:   ExampleSensorModel.cpp
//
//    DESCRIPTION:
//
//    Implementation of ExampleSensorModel class.
//
//    SOFTWARE HISTORY:
//       Date       Author Comment    
//      13-Jan-2004  LMT   Initial version.
//      22 Oct 2010  DSL   CCB Change add getCrossCovarianceMatrix 
//                         and getOriginalCrossCovarianceMatrix
//      29 Jun 2011  DSL   Modified for thread testing 
//      10 Jan 2013  DSL   changes to reflect C++ reformat CRs
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//    NOTES:
//      The functions in the ExampleSensorModel return an error:
//          "Function not supported in ExampleSensorModel"
//
//      The following functions were changed to return "stub" values for thread testing:
//          groundToImage, imageToGround, computeGroundPartials, computeSensorPartials,
//          getNumParameters, getReferencePoint, getModelName, getImageSize, getImageSize 
//
//      The getCovarianceModel function was changed to return the covariance model to 
//          support testing of the Linear Decay covariance model. Now, in the 
//          constructor, a LinearDecayCorrelationModel is instantiated.
//#############################################################################
#include <iostream>
#include "ExampleSensorModel.h"

#pragma warning( disable : 4290 )

using namespace csm;
using namespace ExampleSensor;

//*****************************************************************************
// ExampleSensorModel::ExampleSensorModel
//*****************************************************************************
ExampleSensorModel::ExampleSensorModel()
{
   covM = new LinearDecayCorrelationModel(3, 2);
}

//*****************************************************************************
// ExampleSensorModel::~ExampleSensorModel
//*****************************************************************************
ExampleSensorModel::~ExampleSensorModel()
{
	delete covM;
}

//*****************************************************************************
// ExampleSensorModel::groundToImage
//*****************************************************************************

ImageCoord ExampleSensorModel::groundToImage(const EcefCoord& groundPt,
                                    double desired_precision,
                                    double* achieved_precision,
                                    WarningList* warnings) const
{
   string myname("ExampleSensorModel::groundToImage1");
   Error csmErr;
   cout << "ExampleSensorModel::groundToImage form 1 called." 
	     << endl;

   ImageCoord imagePt;
   imagePt.line = 100;
   imagePt.samp = 200;
   achieved_precision[0] = 1;
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return imagePt;
}

ImageCoordCovar ExampleSensorModel::groundToImage(const EcefCoordCovar& groundPt,
                                         double desired_precision,
                                         double* achieved_precision,
                                         WarningList* warnings) const
{
	ImageCoordCovar icCov;
	string myname("ExampleSensorModel::groundToImage2");
   Error csmErr;
   cout << "  ExampleSensorModel::groundToImage form 2 called." 
	     << endl;

   csmErr.setError(
	   Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return icCov;
}

//*****************************************************************************
// ExampleSensorModel::imageToGround
//*****************************************************************************
   
EcefCoord ExampleSensorModel::imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desired_precision,
                                   double* achieved_precision,
                                   WarningList* warnings) const
{
   string myname("ExampleSensorModel::imageToGround1");
   Error csmErr;
   cout << "  ExampleSensorModel::imageToGround form 1 called." 
	     << endl;
   EcefCoord ecef(20,40,60);
  // achieved_precision = 1;
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return ecef;
}
            
EcefCoordCovar ExampleSensorModel::imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desired_precision,
                                        double* achieved_precision,
                                        WarningList* warnings) const
{
   string myname("ExampleSensorModel::imageToGround2");
   EcefCoordCovar ecefCov;
   Error csmErr;
   cout << "  ExampleSensorModel::imageToGround form 2 called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecefCov;
}

//*****************************************************************************
// ExampleSensorModel::imageToProximateImagingLocus
//*****************************************************************************
EcefLocus ExampleSensorModel::imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desired_precision,
      double* achieved_precision,
      WarningList* warnings) const
{
	string myname("ExampleSensorModel::imageToProximateImagingLocus");

	EcefLocus locus;
	Error csmErr;
	cout << "  ExampleSensorModel::imageToProximateImagingLocus called." 
		<< endl;

	csmErr.setError (
		Error::UNSUPPORTED_FUNCTION,
		"Function not supported in ExampleSensorModel",
		myname);
	throw csmErr;

	return locus;
}

//*****************************************************************************
// ExampleSensorModel::imageToRemoteImagingLocus
//*****************************************************************************
EcefLocus ExampleSensorModel::imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desired_precision,
      double* achieved_precision,
      WarningList* warnings) const
{
	EcefLocus locus;
	string myname("ExampleSensorModel::imageToRemoteImagingLocus");
	Error csmErr;
	cout << "  ExampleSensorModel::imageToRemoteImagingLocus called." 
		<< endl;

	csmErr.setError (
		Error::UNSUPPORTED_FUNCTION,
		"Function not supported in ExampleSensorModel",
		myname);
	throw csmErr;

	return locus;
}


   //---
   // Uncertainty Propagation
   //---

//*****************************************************************************
// ExampleSensorModel::computeGroundPartials
//*****************************************************************************
vector<double> ExampleSensorModel::computeGroundPartials(const EcefCoord& groundPt) const
{
   string myname("ExampleSensorModel::computeGroundPartials");
   Error csmErr;
   cout << "  ExampleSensorModel::computeGroundPartials called." 
	     << endl;
   vector<double> partials;
   partials.push_back(1.0);
   partials.push_back(2.0);
   partials.push_back(3.0);
   partials.push_back(4.0);
   partials.push_back(5.0);
   partials.push_back(6.0);
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return partials;
}

   
//*****************************************************************************
// ExampleSensorModel::computeSensorPartials
//*****************************************************************************
RasterGM::SensorPartials ExampleSensorModel::computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
   string myname("ExampleSensorModel::computeSensorPartials");
   Error csmErr;
   cout << "  ExampleSensorModel::computeSensorPartials form 1 called." 
	     << endl;
   RasterGM::SensorPartials sp;
   sp.first = index * (((groundPt.x + 2) * groundPt.y + 3) + groundPt.z);
   sp.second = index * (((2*groundPt.x + 1) * groundPt.y + 2) + 3* groundPt.z);
   achieved_precision[0] = 1;
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return sp;
}

RasterGM::SensorPartials ExampleSensorModel::computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	string myname("ExampleSensorModel::computeSensorPartials");
	RasterGM::SensorPartials sp;
	Error csmErr;
	cout << "  ExampleSensorModel::computeSensorPartials form 2 called." 
		<< endl;

	csmErr.setError (
		Error::UNSUPPORTED_FUNCTION,
		"Function not supported in ExampleSensorModel",
		myname);
	throw csmErr;
	return sp;
}

//*****************************************************************************
// ExampleSensorModel::computeAllSensorPartials
//*****************************************************************************
vector<RasterGM::SensorPartials > ExampleSensorModel::computeAllSensorPartials(
                const EcefCoord& groundPt,
                param::Set pSet,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
	string myname("ExampleSensorModel::computeAllSensorPartials");
	Error csmErr;
	vector<RasterGM::SensorPartials> sp;
	cout << "  ExampleSensorModel::computeAllSensorPartials form 1 called." 
		<< endl;

	csmErr.setError (
		Error::UNSUPPORTED_FUNCTION,
		"Function not supported in ExampleSensorModel",
		myname);
	throw csmErr;

	return sp;
}

vector<RasterGM::SensorPartials > ExampleSensorModel::computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                param::Set pSet,
                double desired_precision,
                double* achieved_precision,
                WarningList* warnings) const
{
    string myname("ExampleSensorModel::computeAllSensorPartials");
	vector<RasterGM::SensorPartials > sp;
    Error csmErr;
    cout << "  ExampleSensorModel::computeAllSensorPartials form 2 called." 
	     << endl;

    csmErr.setError (
	  Error::UNSUPPORTED_FUNCTION,
	  "Function not supported in ExampleSensorModel",
	  myname);
    throw csmErr;

	return sp;
}



//*****************************************************************************
// ExampleSensorModel::ParameterCovariance
//*****************************************************************************
double ExampleSensorModel::getParameterCovariance(int index1,
                                                int index2) const 
{
   string myname("ExampleSensorModel::getParameterCovariance");
   Error csmErr;
   double ret = 0.0;
   cout 
     << "  ExampleSensorModel::getParameterCovariance form 1 called." 
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

void ExampleSensorModel::setParameterCovariance(int index1,
                                              int index2,
                                              double covariance)
{
   string myname("ExampleSensorModel::setParameterCovariance");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::setParameterCovariance form 2 called." 
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}

   //---
   // Time and Trajectory
   //---

//*****************************************************************************
// ExampleSensorModel::getTrajectoryIdentifier
//*****************************************************************************
string ExampleSensorModel::getTrajectoryIdentifier() const 
{
   string myname("ExampleSensorModel::getTrajectoryIdentifier");
   string trajID;
   Error csmErr;
   cout << "  ExampleSensorModel::getTrajectoryIdentifier called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return trajID;
}

//*****************************************************************************
// ExampleSensorModel::getReferenceDateAndTime
//*****************************************************************************
   string ExampleSensorModel::getReferenceDateAndTime() const
{
   string myname("ExampleSensorModel::getReferenceDateAndTime");
   string date_and_time;
   Error csmErr;
   cout << "  ExampleSensorModel::getReferenceDateAndTime called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return date_and_time;
}


//*****************************************************************************
// ExampleSensorModel::getImageTime
//*****************************************************************************
double ExampleSensorModel::getImageTime(const ImageCoord& pt) const 
{
   string myname("ExampleSensorModel::getImageTime");
   Error csmErr;
   double time = 0.0;
   cout << "  ExampleSensorModel::getImageTime called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return time;
}


//*****************************************************************************
// ExampleSensorModel::getSensorPosition
//*****************************************************************************
EcefCoord ExampleSensorModel::getSensorPosition(const ImageCoord& pt) const 
{
   string myname("ExampleSensorModel::getSensorPosition");
   EcefCoord ecef;
   Error csmErr;
   cout << "  ExampleSensorModel::getSensorPosition form 1 called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecef;
}

EcefCoord ExampleSensorModel::getSensorPosition(double time) const 
{
   string myname("ExampleSensorModel::getSensorPosition");
   Error csmErr;
   EcefCoord ecef;
   cout << "  ExampleSensorModel::getSensorPosition form 2 called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecef;
}

//*****************************************************************************
// ExampleSensorModel::getSensorVelocity
//*****************************************************************************
EcefVector ExampleSensorModel::getSensorVelocity(const ImageCoord& pt) const 
{
   string myname("ExampleSensorModel::getSensorVelocity1");
   Error csmErr;
   EcefVector ecefVec;
   cout << "  ExampleSensorModel::getSensorVelocity form 1 called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecefVec;
}

EcefVector ExampleSensorModel::getSensorVelocity(const double time) const 
{
   string myname("ExampleSensorModel::getSensorVelocity2");
   EcefVector ecefVec;
   Error csmErr;
   cout << "  ExampleSensorModel::getSensorVelocity form 2 called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecefVec;
}

   //---
   // Sensor Model Parameters
   //---

//*****************************************************************************
// ExampleSensorModel::getParameterValue
//*****************************************************************************
double ExampleSensorModel::getParameterValue(int index) const 
{
   string myname("ExampleSensorModel::getParameterValue");
   double val = 0.0;
   Error csmErr;
   cout << "  ExampleSensorModel::getParameterValue called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return val;
}

//*****************************************************************************
// ExampleSensorModel::setParameterValue
//*****************************************************************************
void ExampleSensorModel::setParameterValue(int index, double value)
{
   string myname("ExampleSensorModel::setParameterValue");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::setParameterValue called." 
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}

//*****************************************************************************
// ExampleSensorModel::getParameterName
//*****************************************************************************
string ExampleSensorModel::getParameterName(int index) const 
{
   string myname("ExampleSensorModel::getParameterName");
   Error csmErr;
   string pname;
   cout << "  ExampleSensorModel::getParameterName called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return pname;
}

//*****************************************************************************
// ExampleSensorModel::getNumParameters
//*****************************************************************************
int ExampleSensorModel::getNumParameters() const
{
   string myname("ExampleSensorModel::getNumParameters");
   Error csmErr;
   cout << "  ExampleSensorModel::getNumParameters called." << endl;

   int numparam = 3;
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return numparam;
}

param::Type ExampleSensorModel::getParameterType(int index) const 
{
   string myname("ExampleSensorModel::getParameterType");
   Error csmErr;
   param::Type pt = csm::param::NONE;
   cout << "  ExampleSensorModel::getParameterType called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return pt;
}

void ExampleSensorModel::setParameterType(int index, param::Type pType)
{
   string myname("ExampleSensorModel::setParameterType");
   Error csmErr;
   cout << "  ExampleSensorModel::setParameterType called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}

GeometricModel::Parameter ExampleSensorModel::getParameter(int index) const
{
   Parameter p;
   string myname("ExampleSensorModel::getParameter");
   Error csmErr;
   cout << "  ExampleSensorModel::getParameter called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
   return p;
}

void ExampleSensorModel::setParameter(int index, const Parameter& parameter)
{
   string myname("ExampleSensorModel::setParameter");
   Error csmErr;
   cout << "  ExampleSensorModel::setParameter called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}

void ExampleSensorModel::replaceModelState(const std::string& argState)
{
   string myname("ExampleSensorModel::replaceModelState");
   Error csmErr;
   cout << "  ExampleSensorModel::replaceModelState called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}


//*****************************************************************************
// ExampleSensorModel::getPedigree
//*****************************************************************************
string ExampleSensorModel::getPedigree() const
{
   string myname("ExampleSensorModel::getPedigree");
   Error csmErr;
   string ped;
   cout << "  ExampleSensorModel::getPedigree called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ped;
}


//*****************************************************************************
// ExampleSensorModel::getImageIdentifier
//*****************************************************************************
string ExampleSensorModel::getImageIdentifier() const
{
   string myname("ExampleSensorModel::getImageIdentifier");
   string id;
   Error csmErr;
   cout << "  ExampleSensorModel::getImageIdentifier called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return id;
}

//*****************************************************************************
// ExampleSensorModel::setImageIdentifier
//*****************************************************************************
void ExampleSensorModel::setImageIdentifier(const string& imageId, WarningList* warnings)
{
   string myname("ExampleSensorModel::setImageIdentifier");
   Error csmErr;
   cout << "  ExampleSensorModel::setImageIdentifier called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}

//*****************************************************************************
// ExampleSensorModel::getSensorIdentifier
//*****************************************************************************
string ExampleSensorModel::getSensorIdentifier() const
{
   string myname("ExampleSensorModel::getSensorIdentifier");
   string id;
   Error csmErr;
   cout << "  ExampleSensorModel::getSensorIdentifier called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return id;
}

//*****************************************************************************
// ExampleSensorModel::getPlatformIdentifier
//*****************************************************************************
string ExampleSensorModel::getPlatformIdentifier() const
{
   string myname("ExampleSensorModel::getPlatformIdentifier");
   Error csmErr;
   string id;
   cout << "  ExampleSensorModel::getPlatformIdentifier called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return id;
}


//*****************************************************************************
// ExampleSensorModel::getReferencePoint
//*****************************************************************************
EcefCoord ExampleSensorModel::getReferencePoint() const
{
   string myname("ExampleSensorModel::getReferencePoint");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::getReferencePoint called." 
     << endl;
   EcefCoord ecef(1,2,3);
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return ecef;
}

//*****************************************************************************
// ExampleSensorModel::setReferencePoint
//*****************************************************************************
void ExampleSensorModel::setReferencePoint(const EcefCoord& groundPt)
{
   string myname("ExampleSensorModel::setReferencePoint");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::setReferencePoint called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
}


//*****************************************************************************
// ExampleSensorModel::getModelName 
//*****************************************************************************

string ExampleSensorModel::getModelName() const
{
   string myname("ExampleSensorModel::getModelName");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::getModelName called." 
     << endl;

   string name = "tempname";
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return name;
}

//*****************************************************************************
// ExampleSensorModel::getImageSize 
//*****************************************************************************

ImageVector ExampleSensorModel::getImageSize() const
{
   string myname("ExampleSensorModel::getImageSize");
   Error csmErr;
   cout << "  ExampleSensorModel::getImageSize called." << endl;

   ImageVector iv(100,200);
  // csmErr.setError (
	 //Error::UNSUPPORTED_FUNCTION,
	 //"Function not supported in ExampleSensorModel",
	 //myname);
  // throw csmErr;

   return iv;
}

   //---
   // Sensor Model State
   //---

//*****************************************************************************
// ExampleSensorModel::getModelState
//*****************************************************************************
string ExampleSensorModel::getModelState() const
{
   string myname("ExampleSensorModel::getModelState");
   Error csmErr;
   cout 
     << "  ExampleSensorModel::getModelState called." 
     << endl;

   string state = ("ExampleSensorModel V2.0 TheState");
   return state;
}

   //---
   //  Monoscopic Mensuration
   //---

//*****************************************************************************
// ExampleSensorModel::validHeightRange
//*****************************************************************************
pair<double,double> ExampleSensorModel::getValidHeightRange() const
{
   string myname("ExampleSensorModel::getValidHeightRange");
   Error csmErr;
   pair<double,double> HtRg;
   cout << "  ExampleSensorModel::validHeightRange called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return HtRg;
}

//*****************************************************************************
// ExampleSensorModel::validImageRange (
//*****************************************************************************
pair<ImageCoord,ImageCoord> ExampleSensorModel::getValidImageRange() const
{
   string myname("ExampleSensorModel::getValidImageRange");
   Error csmErr;
   pair<ImageCoord,ImageCoord> imRg;
   cout << "  ExampleSensorModel::validImageRange called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return imRg;
}


//*****************************************************************************
// ExampleSensorModel::getIlluminationDirection
//*****************************************************************************
EcefVector ExampleSensorModel::getIlluminationDirection(const EcefCoord& gndPt) const
{
   string myname("ExampleSensorModel::getIlluminationDirection");
   Error csmErr;
   EcefVector ecefv;
   cout << "  ExampleSensorModel::getIlluminationDirection called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ecefv;
}

   //---
   //  Error Correction
   //---

//*****************************************************************************
// ExampleSensorModel::numGeometricCorrections
//*****************************************************************************
int ExampleSensorModel::getNumGeometricCorrectionSwitches() const 
{
    string myname("ExampleSensorModel::getNumGeometricCorrectionSwitches");
    Error csmErr;
	int num = 0;
    cout << "  ExampleSensorModel::numGeometricCorrections called." 
              << endl;
 
 
    csmErr.setError (
 	 Error::UNSUPPORTED_FUNCTION,
 	 "Function not supported in ExampleSensorModel",
 	 myname);
    throw csmErr;
 
    return num;
 }


//*****************************************************************************
// ExampleSensorModel::getGeometricCorrectionName
//*****************************************************************************
string ExampleSensorModel::getGeometricCorrectionName(int index) const 
 {
    string myname("ExampleSensorModel::getGeometricCorrectionName");
	string name;
    Error csmErr;
    cout 
      << "  ExampleSensorModel::getGeometricCorrectionName called."
      << endl;
 
    csmErr.setError (
 	 Error::UNSUPPORTED_FUNCTION,
 	 "Function not supported in ExampleSensorModel",
 	 myname);
    throw csmErr;
 
    return name;
 }

//*****************************************************************************
// ExampleSensorModel::GeometricCorrectionSwitch
//*****************************************************************************
void ExampleSensorModel::setGeometricCorrectionSwitch(int index, bool value, param::Type pType)
 {
    string myname("ExampleSensorModel::setGeometricCorrectionSwitch");
     Error csmErr;
    cout 
      << "  ExampleSensorModel::GeometricCorrectionSwitch form 1 called."
      << endl;
 
    csmErr.setError (
 	 Error::UNSUPPORTED_FUNCTION,
 	 "Function not supported in ExampleSensorModel",
 	 myname);
    throw csmErr;
 }

//*****************************************************************************
// ExampleSensorModel::getGeometricCorrectionSwitch
//*****************************************************************************
bool ExampleSensorModel::getGeometricCorrectionSwitch(int index) const 
 {
	 string myname("ExampleSensorModel::getGeometricCorrectionSwitch");
	 Error csmErr;
	 bool swt = true;
	 cout 
		 << "  ExampleSensorModel::GeometricCorrectionSwitch form 2 called."
		 << endl;

	 csmErr.setError (
		 Error::UNSUPPORTED_FUNCTION,
		 "Function not supported in ExampleSensorModel",
		 myname);
	 throw csmErr;

	 return swt;
 }

//*****************************************************************************
// ExampleSensorModel::getCrossCovarianceMatrix
//*****************************************************************************
vector<double> ExampleSensorModel::getCrossCovarianceMatrix(
          const GeometricModel& comparisonModel,
          param::Set pSet,
          const GeometricModelList& otherModels) const 
{
   string myname("ExampleSensorModel::getCrossCovarianceMatrix");
   Error csmErr;
   vector<double> ret;
   cout 
     << "  ExampleSensorModel::getCrossCovarianceMatrix called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

//*****************************************************************************
// ExampleSensorModel::getUnmodeledError
//*****************************************************************************
vector<double> ExampleSensorModel::getUnmodeledError(const ImageCoord& pt) const 
{
   string myname("ExampleSensorModel::getUnmodeledError");
   Error csmErr;
   vector<double> ret;
   cout 
     << "  ExampleSensorModel::getUnmodeledError called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

//*****************************************************************************
// ExampleSensorModel::getUnmodeledCrossCovariance
//*****************************************************************************
vector<double> ExampleSensorModel::getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const 
{
   string myname("ExampleSensorModel::getUnmodeledCrossCovariance");
   Error csmErr;
   vector<double> ret;
   cout 
     << "  ExampleSensorModel::getUnmodeledCrossCovariance called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

//*****************************************************************************
// ExampleSensorModel::getCollectionIdentifier
//*****************************************************************************
string ExampleSensorModel::getCollectionIdentifier() const
{
   string myname("ExampleSensorModel::getCollectionIdentifier");
   Error csmErr;
   string id;
   cout << "  ExampleSensorModel::getCollectionIdentifier called." 
	     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return id;
}

//*****************************************************************************
// ExampleSensorModel::isParameterShareable
//*****************************************************************************
bool ExampleSensorModel::isParameterShareable(int index) const 
{
   string myname("ExampleSensorModel::isParameterShareable");
   Error csmErr;
   bool sharable = true;
   cout 
     << "  ExampleSensorModel::isParameterShareable called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return sharable;
}

//*****************************************************************************
// ExampleSensorModel::getParameterSharingCriteria
//*****************************************************************************
csm::SharingCriteria ExampleSensorModel::getParameterSharingCriteria(int index) const 
{
   string myname("ExampleSensorModel::getParameterSharingCriteria");
   Error csmErr;
   csm::SharingCriteria criteria;
   cout 
     << "  ExampleSensorModel::getParameterSharingCriteria called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return criteria;
}

string ExampleSensorModel::getParameterUnits(int index) const
{
   string myname("ExampleSensorModel::getParameterUnits");
   Error csmErr;
   string units;
   cout 
     << "  ExampleSensorModel::getParameterUnits called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return units;
}

string ExampleSensorModel::getSensorType() const
{
   string myname("ExampleSensorModel::getSensorType");
   Error csmErr;
   string type;
   cout 
     << "  ExampleSensorModel::getSensorType called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return type;
}

string ExampleSensorModel::getSensorMode() const
{
   string myname("ExampleSensorModel::getSensorMode");
   Error csmErr;
   string mode;
   cout 
     << "  ExampleSensorModel::getParameterShargetSensorModeingCriteria called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return mode;
}

bool ExampleSensorModel::hasShareableParameters() const
{
   string myname("ExampleSensorModel::hasShareableParameters");
   Error csmErr;
   bool ret = true;
   cout 
     << "  ExampleSensorModel::hasShareableParameters called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}


//*****************************************************************************
// ExampleSensorModel::getVersion
//*****************************************************************************
//This method returns the CSM API version that the plug-in was written to.
//
Version ExampleSensorModel::getVersion() const
{
   string myname("ExampleSensorModel::getVersion");
#ifdef TESTAPIVERSION
   Version version = CURRENT_CSM_VERSIONp1;
#else
   Version version = CURRENT_CSM_VERSION;
#endif

   return version;
}

ImageCoord ExampleSensorModel::getImageStart() const
{
   string myname("ExampleSensorModel::getImageStart");
   Error csmErr;
   ImageCoord ret;
   cout 
     << "  ExampleSensorModel::getImageStart called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

string ExampleSensorModel::getModelType() const
{
   string myname("ExampleSensorModel::getModelType");
   Error csmErr;
   string ret;
   cout 
     << "  ExampleSensorModel::getModelType called."
     << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;

   return ret;
}

//CorrelationModel* ExampleSensorModel::getCovarianceModel() const 
CorrelationModel& ExampleSensorModel::getCorrelationModel() const 
{
	CorrelationModel* retCovM = NULL;
	retCovM = (CorrelationModel*)covM;
	return *retCovM;
}

std::vector<GeometricModel::Parameter> ExampleSensorModel::getParameters(param::Set pSet) const
{
   std::vector<GeometricModel::Parameter> params;
   string myname("ExampleSensorModel::getParameters");
   Error csmErr;
   cout      << "  ExampleSensorModel::getParameters called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
   return params;
}

std::vector<int> ExampleSensorModel::getParameterSetIndices(param::Set pSet) const
{
   std::vector<int> indices;
   string myname("ExampleSensorModel::getParameterSetIndices");
   Error csmErr;
   cout      << "  ExampleSensorModel::getParameterSetIndices called." << endl;

   csmErr.setError (
	 Error::UNSUPPORTED_FUNCTION,
	 "Function not supported in ExampleSensorModel",
	 myname);
   throw csmErr;
   return indices;
}
