// -*- C++ -*-
#ifndef AIDA_IFILTERROOT_H
#define AIDA_IFILTERROOT_H 1

#include <AIDA/IFilter.h>
#include <string>

namespace AIDA {

class ITuple;

/**
 * User's level interface of an IFilter.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFilterROOT.h,v 1.1 2006-12-14 09:55:23 tkraemer Exp $
 */

class IFilterROOT : public IFilter {

public: 
    /// Destructor.
  virtual ~IFilterROOT() { /* nop */; }

  IFilterROOT() { /* nop */; }

  /**
   * Initialize the IFilter and associate it to an ITuple.
   * @param tuple The ITuple to which the IFilter is sssociated.
   * @return false If the IFilter and 
   *              the ITuple are not compatible.
   */ 
  virtual bool initialize(ITuple & tuple) ;

  /**
   * Check if the IFilter accepts or not the data in the 
   * current row of the ITuple it is associated to.
   * @return <code>true</code> if the current data is accepted.
   */ 
  virtual bool accept() const ;

   /**
    * Get the expression that defined the IFilter.
    * @return The expression.
    */
  virtual std::string expression() const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFILTERROOT_H */
