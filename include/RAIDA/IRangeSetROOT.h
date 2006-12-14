// -*- C++ -*-
#ifndef AIDA_IRANGESETROOT_H
#define AIDA_IRANGESETROOT_H 1

#include <AIDA/IRangeSet.h>
#include <vector>

namespace AIDA {

/**
 * User level interface to RangeSet.
 *
 *
 * Proposed rules for ranges:
 *
 * - By default (no arguments) RangeSet object is created with 
 *   one valid range: (-infinity, +infinity).
 *
 * - size=0 means no valid ranges (isInRange(double point) will
 *   return false for any point). It also can be used to check if
 *   any range is set - RangeSet include valid interval only
 *   if size!=0.
 *
 * - RangeSet can be smart, e.g merge overlapping valid ranges.
 *   So size() does not always equal to the number of times
 *   user call include method. 
 *
 *
 * @author T. Kraemer, DESY
 * @version $Id: IRangeSetROOT.h,v 1.1 2006-12-14 10:52:46 tkraemer Exp $
 */

class IRangeSetROOT : public IRangeSet {

public: 
    /// Destructor.
  virtual ~IRangeSetROOT() { /* nop */; }

  IRangeSetROOT() { /* nop */; }

    /** 
     * Return array of lower Bounds for the current set of ranges
     * @return Array of lower bounds for all valid ranges
     */
  virtual const std::vector<double>  & lowerBounds() ;

    /** 
     * Return array of upper Bounds for the current set of ranges
     * @return Array of upper bounds for all valid ranges
     */
  virtual const std::vector<double>  & upperBounds() ;

    /**
     * Add [xMin, xMax] interval to existing set of valid ranges
     * @param xMin - lower bound of a new valid range
     * @param xMax - upper bound of a new valid range
     */  
  virtual void include(double xMin, double xMax) ;

    /**
     * Exclude [xMin, xMax] interval from the existing set of valid ranges
     * @param xMin - lower bound of range to be excluded 
     * @param xMax - upper bound of range to be excluded
     */  
  virtual void exclude(double xMin, double xMax) ;

    /**
     * Set full range (from MINUS_INF to PLUS_INF ).
     */
  virtual void includeAll() ;

    /**
     * Set empty range.
     */
  virtual void excludeAll() ;

    /*
     * @return Return true if the point is in range 
     */
  virtual bool isInRange(double point) ;

    /**
     * Return current number of disjoint ranges (non-overlapping intervals).
     * Note: it is not always equal to the number of times user set the range
     * @return Number of disjoint ranges
     */
  virtual int size() ;

    /*
     * Define +infinity according to specific implementation
     * @return Numeric definition for +infinity
     */
  virtual double PLUS_INF() ;

    /*
     * Define -infinity according to specific implementation
     * @return Numeric definition for -infinity
     */
  virtual double MINUS_INF() ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IRANGESETROOT_H */
