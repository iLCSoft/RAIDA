// -*- C++ -*-
#ifndef AIDA_IBASESTYLEROOT_H
#define AIDA_IBASESTYLEROOT_H 1

#include <AIDA/IBaseStyle.h>
#include <string>
#include <vector>

namespace AIDA {

/**
 * Superclass for all styles in AIDA Plotting package.
 * All styles can be reset to their original values at construction 
 * time. In the case of styles which 'contain' other styles (like IStyle 
 * or IAxisStyle), reset() calls reset() on the aggregated styles too.
 * All styles are hierarchical, so the plotter's current style is overridden by the
 * region's current style, which is overridden by any 'associated' style 
 * which is overwritten by any style passed in explicitly at plotting time.
 * Parameters and options which have been explicitly set to 
 * non-default (or default!) values are 'sticky'. For example, if a style
 * has the default 'red' and this has been set explicitly to 'blue' at the 
 * Plotter level, then it will override the default 'red' at the Region level.
 * IF the user explicitly sets the region to 'green' (or 'red'!) then it will
 * not be overridden by the 'parent' style.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IBaseStyleROOT.h,v 1.2 2006-12-18 09:49:56 tkraemer Exp $
 */

class IBaseStyleROOT : virtual public IBaseStyle {

public: 
    /// Destructor.
    virtual ~IBaseStyleROOT() { /* nop */; }

  /**
   * Return to original (construction time) state. Explicitly 
   * set parameters will be set to defaults and may be overridden 
   */
    virtual void reset();

  /**
   * Set a parameter. 
   * @param paramName Name of the parameter.
   * @param options String of options.
   * @return false if parameter (or its options) unknown or invalid.
   */
    virtual bool setParameter(const std::string & paramName, 
			      const std::string & options = "") ;

  /**
   * Get value of a parameter. 
   * @param paramName Name of the parameter.
   * @return the value.
   */
    virtual std::string parameterValue(const std::string & parameter) const ;

  /**
   * Get list of the available parameters (implementation-dependent)
   */
    virtual std::vector<std::string>  availableParameters() const;

  /** 
   * Get list of the available options for a given parameter 
   * (implementation-dependent).
   */
    virtual std::vector<std::string>  availableParameterOptions(const std::string & paramName) const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IBASESTYLEROOT_H */
