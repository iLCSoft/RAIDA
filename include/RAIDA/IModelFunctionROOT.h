// -*- C++ -*-
#ifndef AIDA_IMODELFUNCTIONROOT_H
#define AIDA_IMODELFUNCTIONROOT_H 1

#include <vector>

#include <RAIDA/IFunctionROOT.h>
#include <AIDA/IModelFunction.h>

namespace AIDA {

class IRangeSet;

/** @interface IModelFunction
 *
 * Interface of model function for fitting (for advanced users).
 *
 * OPEN QUESTIONS:
 *
 * How to treat normalization at user level? Two possibilities:
 * - we have "Gauss" and "NormalizedGauss", the first one user cannot
 *   use for ML fit
 * - we have only one "Gauss" function, but it's smart and when normalized,
 *   gets rid of one of its parameters
 *
 * Normalization range might be set directly on the function by the user?
 * Now we set it in the data pipe, Victor thinks that it is not very clear
 * and should be on the function ;)
 *
 * @author T. Kraemer, DESY
 * @version $Id: IModelFunctionROOT.h,v 1.2 2007-01-02 16:20:45 tkraemer Exp $
 */

class IModelFunctionROOT : public IFunctionROOT, virtual public IModelFunction {

public: 
  /// Destructor.
  virtual ~IModelFunctionROOT() { /* nop */; }

  IModelFunctionROOT() { /* nop */; }

  /// Return false if function does not provide the normalization capability.
  virtual bool providesNormalization() const ;

  /**
   * Normalize by internally adjusting some of the parameters.
   * When normalization is on then integral of the function in
   * the normalization range equals to 1.
   */
  virtual void normalize(bool on) ;

  /**
   * Return true if normalization is currently switched on.
   */
  virtual bool isNormalized() const ;

  /**
   * Compute gradient with respect to parameters.
   */
  virtual const std::vector<double> & parameterGradient(const std::vector<double>  & x) const ;

  /**
   * Return true if provides parameter gradient.
   */
  virtual bool providesParameterGradient() const ;

  /**
   * Set the normalization range from -inf to +inf in the i-th
   * axis (dimension).
   *
   * Full range is the default if not set otherwise.
   * It is still possible to evaluate function outside of the
   * normalization range.
   *
   * PENDING: no methods to retrieve current range!
   */
  virtual IRangeSet & normalizationRange(int iAxis) ;

  /**
   * Set full range in all axes.
   */
  virtual void includeNormalizationAll() ;

  /**
   * Set empty range in all axes.
   */
  virtual void excludeNormalizationAll() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IMODELFUNCTIONROOT_H */
