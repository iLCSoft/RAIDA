// -*- C++ -*-
#ifndef AIDA_IDATASTYLEROOT_H
#define AIDA_IDATASTYLEROOT_H 1

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/IDataStyle.h>

namespace AIDA {

class IFillStyle;
class ILineStyle;
class IMarkerStyle;

/**
 * Style for the part of the scene representing the data
 * (then histograms, functions, data point sets).
 *
 * @author T. Kraemer, DESY
 * @version $Id: IDataStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IDataStyleROOT : public IBaseStyleROOT, public IDataStyle {

public: 
    /// Destructor.
  virtual ~IDataStyleROOT() { /* nop */; }

  IDataStyleROOT() { /* nop */; }

  /**
   * Return various styles that may be used to 
   * customize the data representation.
   */
  virtual ILineStyle & lineStyle() ;

  virtual IMarkerStyle & markerStyle() ;

  virtual IFillStyle & fillStyle() ;

  /**
   * Set various basic style on the data style.
   */
  virtual bool setLineStyle(const ILineStyle & lineStyle) ;

  virtual bool setMarkerStyle(const IMarkerStyle & markerStyle) ;

  virtual bool setFillStyle(const IFillStyle & fillStyle) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IDATASTYLEROOT_H */
