// -*- C++ -*-
#ifndef AIDA_IPLOTTERSTYLEROOT_H
#define AIDA_IPLOTTERSTYLEROOT_H 1

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/IPlotterStyle.h>

namespace AIDA {

class IAxisStyle;
class IDataStyle;
class IInfoStyle;
class ITitleStyle;

/**
 * User level interface to plotter style.
 * A plotter style permit to customize various part
 * of the plotting "scene" (axes, titles, data 
 * representations, etc...)
 *
 * @author T. Kraemer, DESY
 * @version $Id: IPlotterStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IPlotterStyleROOT : public IBaseStyleROOT, public IPlotterStyle {

public: 
    /// Destructor.
  virtual ~IPlotterStyleROOT() { /* nop */; }

  IPlotterStyleROOT() { /* nop */; }

  /** 
   * Get style of various plotting scene parts.
   */
  virtual IDataStyle & dataStyle() ;

  virtual IAxisStyle & xAxisStyle() ;

  virtual IAxisStyle & yAxisStyle() ;

  virtual IAxisStyle & zAxisStyle() ;

  virtual ITitleStyle & titleStyle() ;

  virtual IInfoStyle & infoStyle() ;

  /** 
   * Set style of various plotting scene parts.
   */
  virtual bool setDataStyle(const IDataStyle & dataStyle) ;

  virtual bool setAxisStyleX(const IAxisStyle & xAxisStyle) ;

  virtual bool setAxisStyleY(const IAxisStyle & yAxisStyle) ;

  virtual bool setAxisStyleZ(const IAxisStyle & zAxisStyle) ;

  virtual bool setTitleStyle(const ITitleStyle & textStyle) ;

  virtual bool setInfoStyle(const IInfoStyle & infoStyle) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPLOTTERSTYLEROOT_H */
