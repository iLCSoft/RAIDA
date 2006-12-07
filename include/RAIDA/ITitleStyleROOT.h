// -*- C++ -*-
#ifndef AIDA_ITITLESTYLEROOT_H
#define AIDA_ITITLESTYLEROOT_H 1

#include <RAIDA/IBaseStyleROOT.h>
#include <AIDA/ITitleStyle.h>

namespace AIDA {

class ITextStyle;

/**
 * Style for the "title scene part" of a plotting region or
 * for the global title of a plotting page.
 *
 * @author T. Kraemer, DESY
 * @version $Id: ITitleStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class ITitleStyleROOT : public IBaseStyleROOT, public ITitleStyle {

public: 
    /// Destructor.
  virtual ~ITitleStyleROOT() { /* nop */; }

  ITitleStyleROOT() { /* nop */; }

  virtual ITextStyle & textStyle() ;

  virtual bool setTextStyle(const ITextStyle & textStyle) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITITLESTYLEROOT_H */
