// -*- C++ -*-
#ifndef AIDA_ILINESTYLEROOT_H
#define AIDA_ILINESTYLEROOT_H 1

#include <string>
#include <vector>

#include <RAIDA/IBrushStyleROOT.h>
#include <AIDA/ILineStyle.h>

namespace AIDA {

/**
 * Style for all lines (axis lines, legend box outlines, etc.)
 *
 * @author T. Kraemer, DESY
 * @version $Id: ILineStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class ILineStyleROOT : public IBrushStyleROOT, public ILineStyle {

public: 
    /// Destructor.
  virtual ~ILineStyleROOT() { /* nop */; }

  ILineStyleROOT() { /* nop */; }

  /**
   * Get list of line types supported by this implementation.
   */
  virtual std::vector<std::string>  availableLineTypes() const ;

  /**
   * Get line type currently in use.
   */
  virtual std::string lineType() const ;

  /**
   * Get current line thickness.
   */
  virtual int thickness() const ;

  /**
   * Set current line type e.g. "dotted".
   * @return false if line type not known to this implementation.
   */
  virtual bool setLineType(const std::string & newLineType) ;

  /**
   * Set thickness (exact meaning is implementation-dependent, 
   * but <0 means invisible).
   * @return false if value not supported by this implementation.
   */
  virtual bool setThickness(int newThickness) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ILINESTYLEROOT_H */
