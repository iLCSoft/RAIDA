// -*- C++ -*-
#ifndef AIDA_IAXISSTYLEROOT_H
#define AIDA_IAXISSTYLEROOT_H 1

#include <string>

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/IAxisStyle.h>

namespace AIDA {

class ILineStyle;
class ITextStyle;

/**
 * Style for the part of the scene representing the data
 * (then histograms, functions, data point sets).
 *
 * @author T. Kraemer, DESY
 * @version $Id: IAxisStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IAxisStyleROOT : public IBaseStyleROOT, public IAxisStyle {

public: 
    /// Destructor.
  virtual ~IAxisStyleROOT() { /* nop */; }

  IAxisStyleROOT() { /* nop */; }

  virtual ILineStyle & lineStyle() ;

  virtual ITextStyle & tickLabelStyle() ;

  virtual ITextStyle & labelStyle() ;

  virtual bool setlineStyle(const ILineStyle & lineStyle) ;

  virtual bool setTickLabelStyle(const ITextStyle & tickLabelStyle) ;

  virtual bool setLabelStyle(const ITextStyle & labelStyle) ;

  virtual void setLabel(const std::string & label) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IAXISSTYLEROOT_H */
