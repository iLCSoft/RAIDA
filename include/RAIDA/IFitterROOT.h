// -*- C++ -*-
#ifndef AIDA_IFITTERROOT_H
#define AIDA_IFITTERROOT_H 1

#include <AIDA/IFitter.h>
#include <string>
#include <vector>

namespace AIDA {

class IBaseHistogram;
class IDataPointSet;
class IFitData;
class IFitParameterSettings;
class IFitResult;
class IFunction;

/** Dummy implementation of the class "IFitter".
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFitterROOT.h,v 1.1 2007-01-03 17:03:20 tkraemer Exp $
 */

class IFitterROOT : public IFitter {

public: 
  /// Destructor.
  virtual ~IFitterROOT() { /* nop */; }

  IFitterROOT() { /* nop */; }

  /**
   * Fit an IFunction to an IFitData.
   * The result of the fit is an IFitResult.
   * @param fitData The IFitData to be fitted.
   * @param func    The IFunction to fit on the data.
   * @return        The IFitResult containing the results of the fit.
   */
  virtual IFitResult * fit(IFitData & fitData, IFunction & func) ;

  /**
   * Shortcut to fit an IBaseHistogram directly with an IFunction. 
   * The dimension of the IBaseHistogram must match the dimension of the IFunction.
   * IHistograms and IProfiles are for binned fits only, IClouds only for unbinned fits.
   * @param hist The IBaseHistogram to be fitted.
   * @param func The IFunction to fit on the data.
   * @return     The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IBaseHistogram & hist, IFunction & func) ;

  /**
   * Shortcut to fit an IBaseHistogram directly with an IFunction. 
   * The dimension of the IBaseHistogram must match the dimension of the IFunction.
   * IHistograms and IProfiles are for binned fits only, IClouds only for unbinned fits.
   * @param hist  The IBaseHistogram to be fitted.
   * @param model The string defining the function to be used.
   * @return      The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IBaseHistogram & hist, 
			   const std::string & model) ;

  /**
   * Shortcut to fit an IBaseHistogram directly with an IFunction. 
   * The dimension of the IBaseHistogram must match the dimension of the IFunction.
   * IHistograms and IProfiles are for binned fits only, IClouds only for unbinned fits.
   * @param hist              The IBaseHistogram to be fitted.
   * @param model             The string defining the function to be used.
   * @param initialParameters The array of the initial parameter values; its size must match the number of
   *                          parameters in the function.
   * @return                  The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IBaseHistogram & hist, 
			   const std::string & model, 
			   const std::vector<double>  & initialParameters) ;

  /**
   * Shortcut to fit an IDataPointSet directly with an IFunction. 
   * The dimension of the IDataPointSet must be equal the dimension of the IFunction + 1.
   * This are binned fits only; the last coordinate of the IDataPointSet is used as
   * the "height" in a fit to an IBaseHistogram.
   * @param dataPointSet The IDataPointSet to be fitted.
   * @param func         The IFunction to fit on the data.
   * @return             The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IDataPointSet & dataPointSet, 
			   IFunction & f) ;

  /**
   * Shortcut to fit an IDataPointSet directly with an IFunction. 
   * The dimension of the IDataPointSet must be equal the dimension of the IFunction + 1.
   * This are binned fits only; the last coordinate of the IDataPointSet is used as
   * the "height" in a fit to an IBaseHistogram.
   * @param dataPointSet The IDataPointSet to be fitted.
   * @param model        The string defining the function to be used.
   * @return             The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IDataPointSet & dataPointSet, 
			   const std::string & model) ;

  /**
   * Shortcut to fit an IDataPointSet directly with an IFunction. 
   * The dimension of the IDataPointSet must be equal the dimension of the IFunction + 1.
   * This are binned fits only; the last coordinate of the IDataPointSet is used as
   * the "height" in a fit to an IBaseHistogram.
   * @param dataPointSet      The IDataPointSet to be fitted.
   * @param model             The string defining the function to be used.
   * @param initialParameters The array of the initial parameter values; its size must match the number of
   *                          parameters in the function.
   * @return                  The IFitResult containing the result of the fit.
   */
  virtual IFitResult * fit(IDataPointSet & dataPointSet, 
			   const std::string & model, 
			   const std::vector<double>  & initialParameters) ;

  /// Shortcut for the predefined models.
  virtual IFitResult * fit(IFitData & d, const std::string & model) ;

  virtual IFitResult * fit(IFitData & d, 
			   const std::string & model, 
			   const std::vector<double>  & initialParameters) ;

  /**
   * Set the optimization engine which is used internally for fitting.
   * @param name The name of the optimizer engine.
   *             Examples of predefined engines: "minuit". The engine name is case-insensitive.
   *             Different engines are provided by different implementations.
   * @return false If the name does not correspond to a valid engine.
   */
  virtual bool setEngine(const std::string & name) ;

  /**
   * Get the name of the engine currently in use.
   * @return The name of the optimizer engine used by the IFitter.
   */
  virtual std::string engineName() ;

  /**
   * Access to fit parameter settings. FitParameterSettings object belongs to
   * and is managed by the fitter. Fitter implementation takes care that the
   * returned reference is valid thru the lifetime of fitter.
   * User can set the settings of the parameters independently of the
   * parameters of the fitted function.
   * Setting for parameters unknown in the function and set in the
   * fitter are ignored in the fit.
   * If settings are not explicitly set in the fitter, their default
   * values are attached to function parameters during the fit.
   */
  virtual IFitParameterSettings & fitParameterSettings(const std::string & name) ;

  /**
   * Get a vector of names of all parameter settings defined in the fitter.
   */
  virtual std::vector<std::string>  listParameterSettings() ;

  /**
   * Reset all parameter settings which fitter remebers.
   */
  virtual void resetParameterSettings() ;

  /**
   * Set a general constraint in the parameter space. The constraint
   * is a parsed expression. PENDING: The syntax to be fixed.
   */
  virtual bool setConstraint(const std::string & expr) ;

  /// Get the list of all constraints.
  virtual std::vector<std::string>  constraints() ;

  /**
   * Reset all the constraints.
   */
  virtual void resetConstraints() ;

  /**
   * Set the fit method type. Examples of pre-defined methods: "chi2", "ml".
   * The method names are case-insensitive.
   * @param name The name of the fit method.
   * @return false If the name does not correspond to a valid fit method.
   */
  virtual bool setFitMethod(const std::string & name) ;

  /**
   * Get the name of the fit method currently in use.
   * @return The name of the fit method.
   */
  virtual std::string fitMethodName() ;

  /// Create a 1D scan of the fit quality for given parameter 'par' of
  /// the function.
  /// User must make sure that the returned vector is properly deleted
  /// after use.
  /// The vector containes 'npts' points which are evenly sampled in the
  /// interval ('pmin','pmax').
  virtual IDataPointSet * createScan1D(IFitData & d, 
				       IFunction & f, 
				       const std::string & par, 
				       int npts, double pmin, double pmax) ;

  /// Create a 2D contour spanned on 'par1' and 'par2',
  /// with given number of npts points. Contour is create using previously
  /// obtained fit results. Argument 'up' tells the vertical distance of
  /// the contour plane above the minimal fit quality value.
  virtual IDataPointSet * createContour(IFitData & d, 
					IFitResult & r, 
					const std::string & par1, 
					const std::string & par2, 
					int npts, double up) ;

  /**
   * Choose between using or not using the
   * analytical derivatives if provided by the function.
   * @param useGrad If <code>true</code> the IFitter will use the
   *                analytical derivatives if provided by the IFunction.
   */
  virtual void setUseFunctionGradient(bool useGrad) ;

  /**
   * Check if the IFitter is set to use the analytical derivatives provided
   * by the IFunction.
   * @return <code>true</code> if the IFitter uses the analytical derivatives.
   */
  virtual bool useFunctionGradient() ;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFITTERROOT_H */
