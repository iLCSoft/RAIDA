// -*- C++ -*-
#ifndef AIDA_IPLOTTERREGIONROOT_H
#define AIDA_IPLOTTERREGIONROOT_H 1

#include <AIDA/IPlotterRegion.h>
#include <string>
#include <vector>

namespace AIDA {

class IBaseHistogram;
class IDataPointSet;
class IFunction;
class IInfo;
class IPlotterLayout;
class IPlotterStyle;

/** Dummy implementation of thc class "IPlotterRegion".
 *
 * @author T. Kraemer, DESY
 * @version $Id: IPlotterRegionROOT.h,v 1.2 2007-01-04 16:24:17 tkraemer Exp $
 */

class IPlotterRegionROOT : public IPlotterRegion {

public: 
  /// Destructor.
  virtual ~IPlotterRegionROOT() { /* nop */; }

  IPlotterRegionROOT() { /* nop */; }

  /**
   * Add a data analysis object (histogram, function, cloud,...)
   * in the list of things to plot in the region.
   * Activate the underlying graphic toolkit in order to bring
   * something in the screen window(s) attached to the plotter.
   * It assumes that the plotter had been mapped on the
   * screen with its show method.
   */
  virtual bool plot(const IBaseHistogram & histogram, 
		    const std::string & options = "") ;

  virtual bool plot(const IBaseHistogram & histogram, 
		    const IPlotterStyle & style, 
		    const std::string & options = "") ;

  virtual bool plot(const IFunction & function, 
		    const std::string & options = "") ;

  virtual bool plot(const IFunction & function, 
		    const IPlotterStyle & style, 
		    const std::string & options = "") ;

  virtual bool plot(const IDataPointSet & dataPointSet, 
		    const std::string & options = "") ;

  virtual bool plot(const IDataPointSet & dataPointSet, 
		    const IPlotterStyle & style, 
		    const std::string & options = "") ;

  /**
   *  Remove a data analysis object in the list of things to plot in the region.
   *  Activate the graphic layer to update the screen window.
   */
  virtual bool remove(const IBaseHistogram & histogram) ;

  virtual bool remove(const IFunction & function) ;

  virtual bool remove(const IDataPointSet & dataPointSet) ;

  /**
   * Clear the list of things to plot in the region.
   * Clear the corresponding area on screen window(s).
   */
  virtual void clear() ;

  /**
   * Set various plotting paramters for the region.
   * Activate the graphic layer and update the screen window(s)
   * if needed.
   */
  virtual bool setParameter(const std::string & parameter, 
			    const std::string & options = "") ;

  /**
   * Get value of a parameter. 
   * @param paramName Name of the parameter.
   * @return the value.
   */
  virtual std::string parameterValue(const std::string & parameter) const ;

  virtual std::vector<std::string> availableParameterOptions(const std::string & parameter) const ;

  virtual std::vector<std::string>  availableParameters() const ;

  /**
   * Get the style of the region.
   */
  virtual IPlotterStyle & style() ;

  /**
   * Set the style of a region.
   */
  virtual bool setStyle(const IPlotterStyle & style) ;

  /**
   * Set the style of a region and apply it to scene objects.
   */
  virtual bool applyStyle(const IPlotterStyle & style) ;

  /**
   * Set the title of a region.
   */
  virtual void setTitle(const std::string & title) ;

  /**
   * Set limit of an axis representation the region area.
   */
  virtual bool setXLimits(double min = 0, double max = 0) ;

  virtual bool setYLimits(double min = 0, double max = 0) ;

  virtual bool setZLimits(double min = 0, double max = 0) ;

  /**
   * To customize axis position,etc...
   * Change object position in the scence.
   */
  virtual IPlotterLayout & layout() ;

  virtual bool setLayout(const IPlotterLayout & layout) ;

  /**
   * Return an IInfo object describing the info area.
   */
  virtual IInfo & info() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPLOTTERREGIONROOT_H */
