//#############################################################################
//
//    FILENAME:   StubSensorModel.h
//
//    DESCRIPTION:
//
//    Header for stub plugin sensor model.
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
//      28 Jan 2013  DSL   VTS_VERSION CSM3.0.1.0
//
//#############################################################################
#ifndef __STUBSENSORMODEL_H
#define __STUBSENSORMODEL_H
#ifdef _WIN32
#pragma warning( disable : 4290 )
#endif

#include <vector>

#include "RasterGM.h"
#include "FourParameterCorrelationModel.h"
using namespace csm;
using namespace std;

namespace StubSensor  //----- Create a Namespace
{

enum switchType
{
  STUBNONE,
  STUBWARN,
  STUBERROR,
  STUBNULL
};
class StubSensorModel : public RasterGM
{
public:

   //---
   // Constructors/Destructor
   //---

   StubSensorModel();

   virtual ~StubSensorModel();



   Version getVersion() const;

   std::string getModelType() const;

   std::string getModelName() const;

   std::string getPedigree() const;

/////////////////////////
   std::string getImageIdentifier() const;
   void setImageIdentifier(const std::string& imageId,
                                   WarningList* warnings = NULL);
   std::string getSensorIdentifier() const;
   std::string getPlatformIdentifier() const;
   std::string getCollectionIdentifier() const;

   std::string getSensorType() const;
   std::string getSensorMode() const;
   std::string getParameterUnits(int index) const;
   bool hasShareableParameters() const;
   GeometricModel::Parameter getParameter(int index) const;
      //> This method returns the Parameter indicated by the given index.
      //  If the index is out of range, a csm::Error may be thrown.
      //<
//   void setParameter(int index, const GeometricModel::Parameter& parameter);
     //>  This method sets all of the properties of the Parameter indicated by
     //   the given index to those of the given Parameter.
     //   If the index is out of range, a csm::Error may be thrown.
     //<

   void setParameterValue(int index, double value);

//   string getFamily() const;
   EcefCoord getReferencePoint() const;
   void setReferencePoint(const EcefCoord& groundPt);
   std::string getReferenceDateAndTime() const;
   std::string getModelState() const;
/////////////////////////


   ImageCoord groundToImage(const EcefCoord& groundPt,
                                    double desired_precision = 0.001,
                                    double* achieved_precision = NULL,
                                    WarningList* warnings = NULL) const;

   ImageCoordCovar groundToImage(const EcefCoordCovar& groundPt,
                                         double desired_precision = 0.001,
                                         double* achieved_precision = NULL,
                                         WarningList* warnings = NULL) const;
   
   EcefCoord imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desired_precision = 0.001,
                                   double* achieved_precision = NULL,
                                   WarningList* warnings = NULL) const;
   
   EcefCoordCovar imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desired_precision = 0.001,
                                        double* achieved_precision = NULL,
                                        WarningList* warnings = NULL) const;
   
   EcefLocus imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const;

   EcefLocus imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const;

   ImageCoord getImageStart() const;
   ImageVector getImageSize() const;
   std::pair<double,double> getValidHeightRange() const;
   std::pair<ImageCoord,ImageCoord> getValidImageRange() const;
   EcefVector getIlluminationDirection(const EcefCoord& gndPt) const;
   std::string getTrajectoryIdentifier() const ;
   double getImageTime(const ImageCoord& pt) const ;
   EcefCoord getSensorPosition(const ImageCoord& pt) const ;
   EcefCoord getSensorPosition(double time) const ;
   EcefVector getSensorVelocity(const ImageCoord& pt) const ;
   EcefVector getSensorVelocity(double time) const ;
   int getNumParameters() const ;
   std::string getParameterName(int index) const ;
   bool isParameterShareable(int index) const ;
   csm::SharingCriteria getParameterSharingCriteria(int index) const ;

   double getParameterValue(int index) const ;
   void setParameterType(int index, param::Type pType);
   param::Type getParameterType(int index) const ;
   std::vector<double> computeGroundPartials(const EcefCoord& groundPt) const;

   SensorPartials computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) const;

   SensorPartials computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) const;

   std::vector<SensorPartials> computeAllSensorPartials(
                const EcefCoord& groundPt,
                param::Set pSet             = csm::param::VALID,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) const;

   std::vector<SensorPartials> computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                param::Set pSet             = csm::param::VALID,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) const;

   double getParameterCovariance(int index1,
                                                int index2) const ;

   void setParameterCovariance(int index1,
                                              int index2,
                                              double covariance);

   int getNumGeometricCorrectionSwitches() const ;
   std::string getGeometricCorrectionName(int index) const ;
   void setGeometricCorrectionSwitch(int index,
                                                    bool value,
                                                    param::Type pType);

   void replaceModelState(const std::string& argState);

   bool getGeometricCorrectionSwitch(int index) const ;

   std::vector<double> getCrossCovarianceMatrix(
          const GeometricModel& comparisonModel,
          param::Set pSet,
          const GeometricModelList& otherModels = GeometricModelList()) const;

   CorrelationModel& getCorrelationModel() const ;

   std::vector<double> getUnmodeledError(const ImageCoord& pt) const ;

   std::vector<double> getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const ;
   
std::vector<GeometricModel::Parameter> getParameters(param::Set pSet) const;
std::vector<int> getParameterSetIndices(param::Set pSet) const;


   FourParameterCorrelationModel* covM;


};

};   //----- End of Namespace

#endif // __STUBSENSORMODEL_H
