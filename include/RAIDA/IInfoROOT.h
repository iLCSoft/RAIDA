// -*- C++ -*-
#ifndef AIDA_IINFOROOT_H
#define AIDA_IINFOROOT_H 1

#include <AIDA/IInfo.h>
#include <string>

namespace AIDA {

class IFillStyle;
class ILineStyle;
class IMarkerStyle;

/**
 * The info class permits to access the info area of a region.
 * Through it legends, statistics, text could be displayed.
 * A legend is an association of a graphical marker and a text.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IInfoROOT.h,v 1.1 2006-12-14 10:16:15 tkraemer Exp $
 */

class IInfoROOT : public IInfo {

public: 
    /// Destructor.
  virtual ~IInfoROOT() { /* nop */; }

  IInfoROOT() { /* nop */; }

  /**
   * Clear the info area.
   */
  virtual void clear() ;

  /**
   * Add a text. The text is appended to existing info elements.
   */
  virtual void addText(const std::string & text) ;

  /**
   * Add a marker, line or fill area legend.
   * The legend is appended to existing elements.
   */
  virtual void addLegend(const IMarkerStyle & style, 
			 const std::string & description) ;

  virtual void addLegend(const ILineStyle & style, 
			 const std::string & description) ;

  virtual void addLegend(const IFillStyle & style, 
			 const std::string & description) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IINFOROOT_H */
