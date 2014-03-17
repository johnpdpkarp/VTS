//#############################################################################
//
//    FILENAME:   ExampleSensorModel.h
//
//    DESCRIPTION:
//
//    Header for example plugin sensor model.
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
#ifndef __EXAMPLESENSORMODEL_H
#define __EXAMPLESENSORMODEL_H
#pragma warning( disable : 4290 )

#include <vector>

#include "RasterGM.h"
#include "Error.h"
#include "Warning.h"
#include "CorrelationModel.h"
#include "LinearDecayCorrelationModel.h"
using namespace csm;
using namespace std;

namespace ExampleSensor //----- Define a Namespace
{

class ExampleSensorModel : public RasterGM
{
public:

   //---
   // Constructors/Destructor
   //---

   ExampleSensorModel();

   virtual ~ExampleSensorModel();

   std::string getModelType() const;

   CorrelationModel& getCorrelationModel() const ;

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
   ImageCoord groundToImage(const EcefCoord& groundPt,
                                    double desired_precision = 0.001,
                                    double* achieved_precision = NULL,
                                    WarningList* warnings = NULL) const;
   //> The groundToImage() method converts x, y and z (meters) in
   //  ground space (ECEF) to line and sample (pixels) in image space.
   //<
   ImageCoordCovar groundToImage(const EcefCoordCovar& groundPt,
                                         double desired_precision = 0.001,
                                         double* achieved_precision = NULL,
                                         WarningList* warnings = NULL) const;
   //> This method converts a given ground point into line and sample
   //  (pixels) in image space and returns accuracy information
   //  associated with the image and ground coordinates.
   //<


   EcefCoord imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desired_precision = 0.001,
                                   double* achieved_precision = NULL,
                                   WarningList* warnings = NULL) const;
   
   //> This method converts a given line and sample (pixels) in image space
   //  to a ground point. 
   //<

   EcefCoordCovar imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desired_precision = 0.001,
                                        double* achieved_precision = NULL,
                                        WarningList* warnings = NULL) const;
   //> This method converts a given line and sample (pixels) in image space
   //  to a ground point and returns accuracy information associated with
   //  the image and ground coordinates. 
   //<

   EcefLocus imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const;
   //> The imageToProximateImagingLocus() method computes a proximate
   //  imaging locus, a vector approximation of the imaging locus for the
   //  given line and sample nearest the given x, y and z or at the given
   //  height. The precision of this calculation refers to the locus's 
   //  origin and does not refer to the locus's orientation.
   //<

   EcefLocus imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const;
   //> The imageToRemoteImagingLocus() method computes locus, a vector
   //  approximation of the imaging locus for the given line and sample.
   //  The precision of this calculation refers only to the origin of the
   //  locus vector and does not refer to the locus's orientation. For an
   //  explanation of the remote imaging locus, see the section at the 
   //  beginning of this document.
   //<

   //---
   // Uncertainty Propagation
   //---

   std::vector<double> computeGroundPartials(const EcefCoord& groundPt) const;
   //> The computeGroundPartials method calculates the partial
   //  derivatives (partials) of image position (both line and sample)
   //  with respect to ground coordinates at the given ground 
   //  position x, y, z.
   //  Upon successful completion, computeGroundPartials() produces the
   //  partial derivatives as follows:
   // 
   //  partials [0] = line wrt x
   //  partials [1] = line wrt y
   //  partials [2] = line wrt z
   //  partials [3] = sample wrt x
   //  partials [4] = sample wrt y
   //  partials [5] = sample wrt z
   //<
   
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
   //> The computeSensorPartials() method calculates the partial 
   //  derivatives of image position (both line and sample) with 
   //  respect to the given sensor parameter (index) at the given 
   //  ground position.
   //  Two versions of the method are provided. The first method,
   //  computeSensorPartials(), takes in only necessary information. 
   //  It performs groundToImage() on the ground coordinate and then 
   //  calls the second form of the method with the obtained line 
   //  and sample. If the calling function has already performed 
   //  groundToImage with the ground coordinate, it may call the second
   //  method directly since it may be significantly faster than the
   //  first. The results are unpredictable if the line and sample 
   //  provided do not correspond to the result of calling groundToImage()
   //  with the given ground position (x, y, and z).
   //<

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
   //> The computeAllSensorPartials() function calculates the
   //  partial derivatives of image position (both line and sample)
   //  with respect to each of the adjustable parameters at the
   //  given ground position.
   //>

   double getParameterCovariance(int index1, int index2) const ;
   void setParameterCovariance(int index1, int index2, double covariance);
   //> The first form of the ParameterCovariance() method 
   //  returns the covariance of the specified parameter pair 
   //  (index1, index2). The variance of the given parameter can be 
   //  obtained by using the same value for index1 and index2.
   //  The second form of ParameterCovariance() method is
   //  used to set the covariance value of the specified parameter pair.
   //<

   //---
   // Time and Trajectory
   //---

   std::string getTrajectoryIdentifier() const ;
   //> This method returns a unique identifer to indicate which 
   //  trajectory was used to acquire the image. This ID is unique for
   //  each sensor type on an individual path.
   //<

   std::string getReferenceDateAndTime() const;
   //> This method returns the time in seconds at which the specified
   //  pixel was imaged. The time provide is relative to the reference
   //  date and time given by the getReferenceDateAndTime() method and
   //  can be used to represent time offsets within the trajectory 
   //  associated with the given image.
   //<

   double getImageTime(const ImageCoord& pt) const ;
   //> The getImageTime() method returns the time in seconds at which
   //  the pixel specified by line and sample was imaged. The time
   //  provided is relative to the reference date and time given by
   //  getReferenceDateAndTime.
   //<

   EcefCoord getSensorPosition(const ImageCoord& pt) const ;
   //> The getSensorPosition() method returns the position of
   //  the physical sensor at the given position in the image.
   //<

   EcefCoord getSensorPosition(double time) const ;
   //> The getSensorPosition() method returns the position of
   //  the physical sensor at the given time of imaging.
   //<

   EcefVector getSensorVelocity(const ImageCoord& pt) const ;
   //> The getSensorVelocity() method returns the velocity
   //  of the physical sensor at the given position in the image.
   //<

   EcefVector getSensorVelocity(double time) const ;
   //> The getSensorVelocity() method returns the velocity
   //  the physical sensor at the given time of imaging.
   //<

   //---
   // Sensor Model Parameters
   //---

   void setParameterValue(int index, double value);
   //> setParameterValue() is used to set the 
   //  value of the adjustable parameter indicated by index.
   //<

   double getParameterValue(int index) const ;
   //> getParameterValue()returns the value
   //  of the adjustable parameter given by index.
   //<

   std::string getParameterName(int index) const ;
   //> This method returns the name for the sensor model parameter
   //  indicated by the given index.
   //<

   int getNumParameters() const ;
   //> This method returns the number of sensor model parameters.
   //<

   param::Type getParameterType(int index) const ;
   //> The getParameterType() method returns the 
   //  type of the parameter given by index. 
   //<

   void setParameterType(int index, param::Type pType);
   //> The setParameterType() method sets the  
   //  type of the parameter for the given by index. 
   //<

   //---
   // Sensor Model Information
   //---

   void replaceModelState(const std::string& argState);

   std::string getPedigree() const;
   //> The getPedigree() method returns a character string that
   //  identifies the sensor, the model type, its mode of acquisition
   //  and processing path. For example, an image that could produce
   //  either an optical sensor model or a cubic rational polynomial
   //  model would produce different pedigrees for each case.
   //<

   std::string getImageIdentifier() const;
   //> This method returns the unique identifier to indicate the imaging 
   //  operation associated with this sensor model.
   //<

   void setImageIdentifier(const std::string& imageId, WarningList* warnings = NULL);
   //> This method sets the unique identifier for the image to which the
   //  sensor model pertains.
   //<

   std::string getSensorIdentifier() const;
   //> The getSensorIdentifier() method returns sensorId to indicate
   //  which sensor was used to acquire the image. This sensorId is 
   //  meant to uniquely identify the sensor used to make the image.
   //<

   std::string getPlatformIdentifier() const;
   //> The getPlatformIdentifier() method returns platformId to indicate
   //  which platform was used to acquire the image. This platformId
   //  is meant to uniquely identify the platform used to collect the image.
   //<

   void setReferencePoint(const EcefCoord& groundPt);
   //> This method sets the ground point indicating the general location
   //  of the image.
   //<

   EcefCoord getReferencePoint() const;
   //> This method returns the ground point indicating the general location
   //  of the image.
   //<

   std::string getModelName() const;
   //> This method returns the name of the sensor model.
   //<

   ImageCoord getImageStart() const;

   ImageVector getImageSize() const;
   //> This method returns the number of lines and samples in the imaging
   //  operation.
   //<

   //---
   // Sensor Model State
   //---

   std::string getModelState() const;
   //> This method returns the current state of the model in an 
   //  intermediate form. This intermediate form can then processed,
   //  for example, by saving to file so that this model 
   //  can be instantiated at a later date. The derived RasterGM 
   //  is responsible for saving all information needed to restore 
   //  itself to its current state from this intermediate form.
   //  A NULL pointer is returned if it is not possible to save the
   //  current state.
   //<

   //---
   //  Monoscopic Mensuration
   //---

   std::pair<double,double> getValidHeightRange() const;
   //> The validHeightRange() method returns the minimum and maximum
   //  heights that describe the range of validity of the model. For
   //  example, the model may not be valid at heights above the height
   //  of the sensor for physical models. 
   //<

   std::pair<ImageCoord,ImageCoord> getValidImageRange() const;
   //> The validImageRange() method returns the minimum and maximum
   //  values for image position (row and column) that describe the
   //  range of validity of the model. This range may not always match
   //  the physical size of the image.  This method is used in
   //  conjunction with getValidHeightRange() to determine the full
   //  range of applicability of the sensor model.
   //<

   EcefVector getIlluminationDirection(const EcefCoord& gndPt) const;
   //> The getIlluminationDirection() method calculates the direction of 
   //  illumination at the given ground position x, y, z.
   //<


   //---
   //  Error Correction
   //---

   int getNumGeometricCorrectionSwitches() const ;
   //> The numGeometricCorrections() method returns the number
   //  of geometric corrections defined for the sensor model.
   //<

   std::string getGeometricCorrectionName(int index) const ;
   //> This method returns the name for the sensor model parameter
   //  indicated by the given index.
   //<

   void setGeometricCorrectionSwitch(int index, bool value, param::Type pType);

   bool getGeometricCorrectionSwitch(int index) const ;
   //> The first form of GeometricCorrectionSwitch() is
   //  used to set the switch of the geometric correction
   //  indicated by index.
   //
   //  The second form of GeometricCorrectionSwitch()
   //  returns the value of the geometric correction switch
   //  given by index.
   //<

   std::vector<double> getCrossCovarianceMatrix(
          const GeometricModel& comparisonModel,
          param::Set pSet = csm::param::VALID,
          const GeometricModelList& otherModels = GeometricModelList()) const;

   //> The getCurrentCovarianceMatrix() function returns a matrix
   //  containing all elements of the error cross covariance matrix
   //  between the instantiated sensor model and a specified second
   //  sensor model (SM2). This data supplies the data to compute
   //  cross covariance between images. Images may be correlated
   //  because they are taken by the same sensor or from sensors on
   //  the same platform. Images may also be correlated due to post
   //  processing of the sensor models. The data returned here may
   //  need to be supplemented with the single image covariance from
   //  getParameterCovariance() and getUnmodeledError().
   //<

   std::vector<double> getUnmodeledError(const ImageCoord& pt) const ;
   //> The getUnmodeledError() function gives a sensor specific   
   //  error for the given input image point. The error is reported 
   //  as the four terms of a 2x2 covariance mensuration error 
   //  matrix. This error term is meant to map error terms that are
   //  not modeled in the sensor model to image space for inclusion 
   //  in error propagation. The extra error is added to the 
   //  mensuration error that may already be in the matrix.
   //<

   std::vector<double> getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const ;
   //> The getUnmodeledCrossCovariance function gives the cross 
   //  covariance for unmodeled error between two image points on 
   //  the same image. The error is reported as the four terms of 
   //  a 2x2 matrix. The unmodeled cross covariance is added to 
   //  any values that may already be in the cross covariance matrix.
   //<

   std::string getCollectionIdentifier() const;
   //> This method returns a unique identifer that uniquely identifies       
   //  a collection activity by a sensor platform. This ID will vary
   //  depending on the sensor type and platform.
   //<

   bool isParameterShareable(int index) const ;
   //> This method returns a flag to indicate whether or not a sensor 
   //  model parameter adjustments are shareable across images for the
   //  sensor model adjustable parameter referenced by index.
   //<

   csm::SharingCriteria getParameterSharingCriteria(int index) const ;
   //> This method returns a flag to indicate whether or not a sensor 
   //  ...
   //<
   string getParameterUnits(int index) const;
   string getSensorType() const;
   string getSensorMode() const;
   bool hasShareableParameters() const;

   GeometricModel::Parameter getParameter(int index) const;
      //> This method returns the Parameter indicated by the given index.
      //  If the index is out of range, a csm::Error may be thrown.
      //<
   void setParameter(int index, const Parameter& parameter);
     //>  This method sets all of the properties of the Parameter indicated by
     //   the given index to those of the given Parameter.
     //   If the index is out of range, a csm::Error may be thrown.
     //<

std::vector<GeometricModel::Parameter> getParameters(param::Set pSet) const;
std::vector<int> getParameterSetIndices(param::Set pSet) const;

   Version getVersion() const;
   LinearDecayCorrelationModel* covM;

};

}; //----- End of Namespace

#endif // __EXAMPLESENSORMODEL_H
