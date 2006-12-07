// -*- C++ -*-
#ifndef AIDA_IINFOSTYLEROOT_H
#define AIDA_IINFOSTYLEROOT_H 1

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/IInfoStyle.h>

namespace AIDA {

class ITextStyle;

/**
 * Style for the part of the scene representing the info area.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IInfoStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class IInfoStyleROOT : public IBaseStyleROOT, public IInfoStyle {

public: 
    /// Destructor.
  virtual ~IInfoStyleROOT() { /* nop */; }

  IInfoStyleROOT() { /* nop */; }

  virtual ITextStyle & textStyle() ;

  virtual bool setTextStyle(const ITextStyle & textStyle) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IINFOSTYLEROOT_H */
