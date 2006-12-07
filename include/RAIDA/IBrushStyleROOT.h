// -*- C++ -*-
#ifndef AIDA_IBRUSHSTYLEROOT_H
#define AIDA_IBRUSHSTYLEROOT_H 1

#include <string>
#include <vector>

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/IBrushStyle.h>

namespace AIDA {

/**
 * Superclass for anything which can be drawn in different 
 * colours and with (possibly) transparent/opaque/translucent effect.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IBrushStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IBrushStyleROOT : public IBaseStyleROOT, public IBrushStyle {

public: 
    /// Destructor.
  virtual ~IBrushStyleROOT() { /* nop */; }

  IBrushStyleROOT() { /* nop */; }

  /**
   * Get a list of the colours supported by this implementation.
   */
  virtual std::vector<std::string>  availableColors() const ;

  /** 
   * Current colour of this brush style.
   */
  virtual std::string color() const ;

  /** 
   * Current opacity (alpha) of this brush style.
   */
  virtual double opacity() const ;

  /** 
   * Set current colour, e.g. "darkGreen"
   * @return false if colour not recognised by the implementation.
   */
  virtual bool setColor(const std::string & newColor) ;

  /**
   * Set opacity (alpha), e.g. 0 (transparent), 
   * 1 (opaque), 0.5 (halfway).
   * @return false if value not supported by the implementation.
   */
  virtual bool setOpacity(double newOpacity) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IBRUSHSTYLEROOT_H */
