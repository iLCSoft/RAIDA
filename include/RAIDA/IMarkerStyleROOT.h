// -*- C++ -*-
#ifndef AIDA_IMARKERSTYLEROOT_H
#define AIDA_IMARKERSTYLEROOT_H 1

#include <string>
#include <vector>

#include <RAIDA/IBrushStyleROOT.h>
#include <AIDA/IMarkerStyleROOT.h>

namespace AIDA {

/**
 * Style for all markers (histo representation, legend box etc.)
 *
 * @author T. Kraemer, DESY
 * @version $Id: IMarkerStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IMarkerStyleROOT : public IBrushStyleROOT, public IMarkerStyle {

public: 
    /// Destructor.
    virtual ~IMarkerStyleROOT() { /* nop */; }

  IMarkerStyleROOT() { /* nop */; }

  /**
   * Get list of shapes available in this implementation.
   */
  virtual std::vector<std::string>  availableShapes() const ;

  /**
   * Get current marker shape.
   */
  virtual std::string shape() const ;

  /**
   * Set current marker shape, e.g. "openCircle". 
   * @return false if shape not available in this implementation.
   */
  virtual bool setShape(const std::string & shape) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IMARKERSTYLEROOT_H */
