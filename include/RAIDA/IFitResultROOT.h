// -*- C++ -*-
#ifndef AIDA_IFITRESULTROOT_H
#define AIDA_IFITRESULTROOT_H 1

#include <AIDA/IFitResult.h>
#include <string>
#include <vector>

namespace AIDA {

class IFitParameterSettings;
class IFunction;

/** Dummy implementation of the IFitResult class. 
 * *
 * @author T. Kraemer, DESY
 * @version $Id: IFitResultROOT.h,v 1.1 2007-01-03 16:07:03 tkraemer Exp $
 */
 
class IFitResultROOT : public IFitResult {

public: 
  /// Destructor.
  virtual ~IFitResultROOT() { /* nop */; }

  IFitResultROOT() { /* nop */; }

  /// True if fit successful, otherwise false.
  virtual bool isValid() ;

  /// Status of the fit. PENDING: what are the suggested values?
  virtual int fitStatus() ;

  /// Fitted function. The parameters hold the results of the fit.
  virtual IFunction & fittedFunction() ;

  /// Quality of the fit. Depending on the fit method this may be the value
  /// of Chi2 or Maximu Likelihood.
  virtual double quality() ;

  /// Number of degrees of freedom.
  virtual int ndf() ;

  /// Covariance matrix. PENDING: interface for matrix to be defined.
  virtual double covMatrixElement(int i, int j) ;

  /// Fit method name as set in the fitter.
  virtual std::string fitMethodName() ;

  /// Engine used to do fitting.
  virtual std::string engineName() ;

  /// Textual description of data - this is a hint for the user how to find
  /// the data in the tree if he wanted to repeat the fit later and lost
  /// the pointer to his orignal data object.
  /// PENDING: the contents and format of this string to be defined.
  /// PENDING: XML? stor name and path? ranges of DataPipe?
  virtual std::string dataDescription() ;

  /// Vector of constraints.
  virtual std::vector<std::string>  constraints() ;

  /// Access to applied parameter settings.
  virtual IFitParameterSettings * fitParameterSettings(const std::string & name) ;

  /**
   * Get the array of the fitted parameter values (including fixed and constrained ones).
   * @return The array containing the fitted values.
   */
  virtual const std::vector<double>  & fittedParameters() const ;

  /**
   * Get the names of the fitted parameters (including fixed and constrained ones).
   * @return The array containing the names of the fitted parameters.
   */
  virtual std::vector<std::string>  fittedParameterNames() const ;

  /**
   * Get the value of a fitted parameter by name.
   * @return The value.
   */
  virtual double fittedParameter(const std::string & name) ;

  /**
   * Get the parabolic errors on the fitted parameters. If a parameter was fixed
   * or constrained the error is zero.
   * @return The parabolic errors on the fitted parameters.
   */
  virtual const std::vector<double>  & errors() const ;

  /**
   * Get the positive part of the asymmetric errors on the fitted parameters. If a parameter was fixed
   * or constrained the error is zero.
   * @return The positive part of the asymmetric errors on the fitted parameters.
   */
  virtual const std::vector<double>  & errorsPlus() const ;

  /**
   * Get the negative part of the asymmetric errors on the fitted parameters. If a parameter was fixed
   * or constrained the error is zero.
   * @return The negative part of the asymmetric errors on the fitted parameters.
   */
  virtual const std::vector<double>  & errorsMinus() const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFITRESULTROOT_H */
