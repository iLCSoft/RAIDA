// -*- C++ -*-
#ifndef AIDA_ITEXTSTYLEROOT_H
#define AIDA_ITEXTSTYLEROOT_H 1

#include <string>
#include <vector>

#include <RAIDA/IBrushStyleROOT.h>
#include <AIDA/ITextStyle.h>

namespace AIDA {

/**
 * Style for all text (e.g. axis labels, legend box text etc.)
 *
 * @author T. Kraemer, DESY
 * @version $Id: ITextStyleROOT.h,v 1.1 2006-12-07 10:33:21 tkraemer Exp $
 */

class ITextStyleROOT : public IBrushStyleROOT, public ITextStyle {

public: 
    /// Destructor.
  virtual ~ITextStyleROOT() { /* nop */; }

  ITextStyleROOT() { /* nop */; }

  /** 
   * Get list of fonts available in this implementation.
   */
  virtual std::vector<std::string>  availableFonts() const ;

  /**
   * Get current font size.
   */
  virtual double fontSize() const ;

  /**
   * Set current font size.
   * @return false if size not supported by this implementation.
   */
  virtual bool setFontSize(double size) ;

  /**
   * Get name of current font.
   */
  virtual std::string font() const ;

  /**
   * Set current font, e.g. "timesNewRoman" or "courier".
   * @return false if font not supported by this implementation.
   */
  virtual bool setFont(const std::string & font) ;

  virtual bool isBold() const ;

  virtual bool isItalic() const ;

  virtual bool isUnderlined() const ;

  virtual bool setBold(bool bold = true) ;

  virtual bool setItalic(bool italic = true) ;

  virtual bool setUnderlined(bool underlined = true) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITEXTSTYLEROOT_H */
