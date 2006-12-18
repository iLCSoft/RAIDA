// -*- C++ -*-
#ifndef AIDA_IPLOTTERFACTORYROOT_H
#define AIDA_IPLOTTERFACTORYROOT_H 1

#include <AIDA/IPlotterFactory.h>
#include <string>

namespace AIDA {

class IAxisStyle;
class IDataStyle;
class IFillStyle;
class ILineStyle;
class IMarkerStyle;
class IPlotter;
class IPlotterStyle;
class ITextStyle;
class ITitleStyle;

/**
 * Factory for plotter and styles.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IPlotterFactoryROOT.h,v 1.1 2006-12-18 09:49:56 tkraemer Exp $
 */

class IPlotterFactoryROOT : public IPlotterFactory {

public: 
    /// Destructor.
    virtual ~IPlotterFactoryROOT() { /* nop */; }

  IPlotterFactoryROOT() { /* nop */; }

   /** 
     * @param name  A string identifier. 
                    A plotter is in general managed by a GUI.
                    The "name" of the plotter could be used as 
                    the string identifier for the GUI plotter widget.
                    If "" is passed, some default plotter is used.
    */

  virtual IPlotter * create(const std::string & name = "") ;

   /** 
    * Create various basic styles. 
    * The returned styles are not managed by the plotter.
    * A user have to delete these objects.
    */
  virtual IMarkerStyle * createMarkerStyle() ;

  virtual ITextStyle * createTextStyle() ;

  virtual ILineStyle * createLineStyle() ;

  virtual IFillStyle * createFillStyle() ;

   /**
    * Create various "scene part" styles.
    * The returned styles are not managed by the plotter.
    */ 
  virtual IDataStyle * createDataStyle() ;

  virtual IAxisStyle * createAxisStyle() ;

  virtual ITitleStyle * createTitleStyle() ;

   /**
    * Create a global plotter style.
    * The returned style is not managed by the plotter.
    */ 
  virtual IPlotterStyle * createPlotterStyle() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPLOTTERFACTORYROOT_H */
