// -*- C++ -*-
#ifndef AIDA_IFITPARAMETERSETTINGSROOT_H
#define AIDA_IFITPARAMETERSETTINGSROOT_H 1

#include <AIDA/IFitParameterSettings.h>
#include <string>

namespace AIDA {

/** Dummy implementation of IFitParameterSettings.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFitParameterSettingsROOT.h,v 1.1 2007-01-03 14:20:02 tkraemer Exp $
 */

class IFitParameterSettingsROOT : public IFitParameterSettings {

public: 
    /// Destructor.
    virtual ~IFitParameterSettingsROOT() { /* nop */; }

  IFitParameterSettingsROOT() { /* nop */; }

  /// Name of the parameter to which settings apply.
  virtual std::string name() const ;

  /// Step size allows to control the "sensitivity" of the change of the parameter
  /// when fitters looks for the optimal parameter value. Default is 1.0.
  virtual double stepSize() const ;

  /// Bounds.
  virtual double upperBound() const ;

  virtual double lowerBound() const ;

  /// Shortcut for lowerBound() == -INF && upperBound() == +INF.
  virtual bool isBound() const ;

  /// Value of the parameter cannot change if isFixed() == true.
  /// Parameter can be fixed independently from setting the bounds.
  virtual bool isFixed() const ;

  /// Set the step size for the fitter.
  virtual void setStepSize(double step) ;

  /// Set bounds. If bounds not set, then default bound is (-INF,+INF).
  virtual void setBounds(double lo, double up) ;

  /// Shortcut for setBounds(-INF,+INF).
  virtual void removeBounds() ;

  /// Fix/unfix parameter.
  virtual void setFixed(bool isFixed) ;

  /**
   * Set the lower bound. When this method is
   * invoked any previous bound is reset. The new bounds
   * are (lowerBound, +INF).
   * @param lowerBound The lower bound.
   */
  virtual void setLowerBound(double lowerBound) ;

  /**
   * Set the upper bound. When this method is
   * invoked any previous bound is reset. The new bounds
   * are (-INF, upperBound).
   * @param upperBound The upper bound.
   */
  virtual void setUpperBound(double upperBound) ;

  /// Reset all settings to the default values (remove bounds, step size = 1.0, no fix).
  virtual void reset() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFITPARAMETERSETTINGSROOT_H */
