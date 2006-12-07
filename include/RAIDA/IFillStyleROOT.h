// -*- C++ -*-
#ifndef AIDA_IFILLSTYLEROOT_H
#define AIDA_IFILLSTYLEROOT_H 1

#include <string>
#include <vector>

#include <RAIDA/IBrushStyleROOT.h>
#include <AIDA/IFillStyle.h>

namespace AIDA {

/**
 * Style for all filled areas (boxes, regions, histograms, etc.)
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFillStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IFillStyleROOT : public IBrushStyleROOT, public IFillStyle {

public: 
    /// Destructor.
    virtual ~IFillStyleROOT() { /* nop */; }

  IFillStyleROOT() { /* nop */; }

  /**
   * Get a list of patterns available in this implementation.
   */
  virtual std::vector<std::string>  availablePatterns() const ;

  /** 
   * Get name of current pattern.
   */
  virtual std::string pattern() const ;

  /**
   * Set current pattern, e.g. "crossHatch", "solid".
   * @return false if pattern not known to this implementation.
   */
  virtual bool setPattern(const std::string & pattern) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFILLSTYLEROOT_H */
