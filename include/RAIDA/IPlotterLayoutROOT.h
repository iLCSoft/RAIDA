// -*- C++ -*-
#ifndef AIDA_IPLOTTERLAYOUTROOT_H
#define AIDA_IPLOTTERLAYOUTROOT_H 1

#include <AIDA/IPlotterLayout.h>
#include <string>
#include <vector>

namespace AIDA {

/**
 * Interface to permit customization of the layout
 * of scene objects.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IPlotterLayoutROOT.h,v 1.1 2006-12-18 10:29:24 tkraemer Exp $
 */

class IPlotterLayoutROOT : public IPlotterLayout {

public: 
  /// Destructor.
  virtual ~IPlotterLayoutROOT() { /* nop */; }

  IPlotterLayoutROOT() { /* nop */; }

  /**
   * Return to original (construction time) state. Explicitly 
   * set parameters will be set to defaults and may be overridden 
   */
  virtual void reset() ;

  /**
   * Set a parameter. 
   * @param paramName Name of the parameter.
   * @param options String of options.
   * @return false if parameter (or its options) unknown or invalid.
   */
  virtual bool setParameter(const std::string & paramName, 
			    double paramValue) ;

  /** 
   * Get parameter value.
   */
  virtual double parameterValue(const std::string & paramName) ;

  /**
   * Get list of the available parameters (implementation-dependent)
   */
  virtual std::vector<std::string>  availableParameters() const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPLOTTERLAYOUTROOT_H */
