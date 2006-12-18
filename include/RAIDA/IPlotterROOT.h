// -*- C++ -*-
#ifndef AIDA_IPLOTTERROOT_H
#define AIDA_IPLOTTERROOT_H 1

#include <AIDA/IPlotter.h>
#include <string>
#include <vector>

namespace AIDA {

class IPlotterRegion;
class ITitleStyle;

/**
 * User level interface to plotter.
 *
 * This IPlotter interface assumes the handling of
 * multiple plotting regions. Then the IPlotter should
 * be seen as a "page" managing multiple drawing region.
 * It assumes that a "current" region mechanism is used.
 * 
 * The keyword "region" is borrowed from the OpenInventor
 * terminology (viewing region).
 *
 * See also the IPlotterRegion for more comments.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IPlotterROOT.h,v 1.1 2006-12-18 09:49:56 tkraemer Exp $
 */
 
class IPlotterROOT : public IPlotter {

public: 
    /// Destructor.
  virtual ~IPlotterROOT() { /* nop */; }

  IPlotterROOT() { /* nop */; }

  /**
   * Region management methods.
   */

  /**
   * Create a new region.
   * @param x, y, w, h Position and size in normal coordinates
   *                   that is to say between 0 and 1.
   *                   Then a region with (x=0,y=0,w=1,h=1) maps
   *                   the full page. "x" goes left to right. "y" bottom
   *                   to top.
   * @return The newly created region. Return null in case not failure.
   *         Note that the plotter manages the regions ; user does not
   *         have to delete a region object directly.
   */
  virtual IPlotterRegion * createRegion(double x = 0, 
					double y = 0, 
					double w = 1.0, 
					double h = 1.0) ;

  /**
   * Create a grid of regions.
   * By default the current region is the top left one (with index 0).
   * Region are indexed from zero, with increasing order
   * left to right, top to bottom.
   * @param index Set the current region.
   */
  virtual bool createRegions(int columns = 1, 
			     int rows = 1, 
			     int index = 0) ;

  /**
   * @return The current region.
   */
  virtual IPlotterRegion & currentRegion() const ;

  /**
   * @return The current region index.
   */
  virtual int currentRegionNumber() const ;

  /**
   * @return The number of regions.
   */
  virtual int numberOfRegions() const ;

  /**
   * Set current region by giving its index [0,n-1]
   */
  virtual bool setCurrentRegionNumber(int index) ;

  /**
   * Set current region to be the "next" one.
   * If exceeding the number of regions,
   * the current region index return to 0.
   * @return The new current region.
   */
  virtual IPlotterRegion & next() ;

  /**
   * @return A region, knowing its index.
   */
  virtual IPlotterRegion * region(int index) const ;

  /**
   *  Destroy regions.
   */
  virtual void destroyRegions() ;

  /**
   * Clear all regions. It does not reset the number
   * and position of regions. This can be done through
   * a destroyRegions.
   */
  virtual void clearRegions() ;

  /*
   * Set various plotting paramters for the whole page.
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

  /*
   * GUI related methods :
   */

  /**
   * Map the plotter on the screen.
   */
  virtual bool show() ;

  /**
   * Refresh the screen window(s).
   * Used when a plotted data analysis object
   * received new data.
   */
  virtual bool refresh() ;

  /**
   * Unmap the plotter on the screen.
   */
  virtual bool hide() ;

  /**
   * Give control to the plotter GUI. The plotter must be able
   * to return from this function from a user action in its GUI.
   */
  virtual bool interact() ;

  /*
   * Other methods.
   */

  /**
   * Produce an output file.
   * @param type  A string to describe the type of the output :
   *  "PS"  or "PostScript" for PostScript, "JPEG" for JPEG.
   *  If nothing is given, the type is guessed
   *  from the given file name suffix (.ps for PostScript,
   *  .jpg for JPEG, etc...).
   */
  virtual bool writeToFile(const std::string & filename, 
			   const std::string & type = "") ;

  /**
   * Set the global title of the plotter (page).
   */
  virtual void setTitle(const std::string & title) ;

  /**
   * Get/set title style.
   */
  virtual ITitleStyle & titleStyle() ;

  virtual void setTitleStyle(const ITitleStyle & style) ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPLOTTERROOT_H */
