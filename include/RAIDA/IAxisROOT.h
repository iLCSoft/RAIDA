// -*- C++ -*-
#ifndef AIDA_IAXISROOT_H
#define AIDA_IAXISROOT_H 1

#include <AIDA/IAxis.h>
#include <TAxis.h>

namespace AIDA {

/**
 * An IAxis represents a binned histogram axis. A 1D Histogram would have
 * one Axis representing the X axis, while a 2D Histogram would have two
 * axes representing the X and Y Axis.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IAxisROOT.h,v 1.3 2006-12-04 17:24:06 tkraemer Exp $
 */

class IAxisROOT : public IAxis {

public: 
    /// Destructor.
    virtual ~IAxisROOT() { /* nop */; }

  /// Constructor: you need to have a pointer to a ROOT TAxis object to construct!
  IAxisROOT(TAxis* axis); 
  void setFixedBinning() ;
  void setVariableBinning() ;

  /**
   * Check if the IAxis has fixed binning, i.e. if all the bins have the same width.
   * @return <code>true</code> if the binning is fixed, <code>false</code> otherwise.
   *
   */
    virtual bool isFixedBinning() const ;

  /**
   * Get the lower edge of the IAxis.
   * @return The IAxis's lower edge.
   *
   */
    virtual double lowerEdge() const ;

  /**
   * Get the upper edge of the IAxis.
   * @return The IAxis's upper edge.
   *
   */
    virtual double upperEdge() const ;

  /** 
   * The number of bins (excluding underflow and overflow) on the IAxis.
   * @return The IAxis's number of bins.
   *
   */
    virtual int bins() const ;

  /**
   * Get the lower edge of the specified bin.
   * @param index The bin number: 0 to bins()-1 for the in-range bins or OVERFLOW or UNDERFLOW.
   * @return      The lower edge of the corresponding bin; for the underflow bin this is <tt>Double.NEGATIVE_INFINITY</tt>.
   *
   */
    virtual double binLowerEdge(int index) const ;

  /**
   * Get the upper edge of the specified bin.
   * @param index The bin number: 0 to bins()-1 for the in-range bins or OVERFLOW or UNDERFLOW.
   * @return      The upper edge of the corresponding bin; for the overflow bin this is <tt>Double.POSITIVE_INFINITY</tt>.
   *
   */ 
    virtual double binUpperEdge(int index) const ;

  /**
   * Get the width of the specified bin.
   * @param index The bin number: 0 to bins()-1) for the in-range bins or OVERFLOW or UNDERFLOW.
   * @return      The width of the corresponding bin.
   *
   */ 
    virtual double binWidth(int index) const ;

  /**
   * Convert a coordinate on the axis to a bin number.
   * If the coordinate is less than the lowerEdge UNDERFLOW is returned; if the coordinate is greater or
   * equal to the upperEdge OVERFLOW is returned.
   * @param coord The coordinate to be converted.
   * @return      The corresponding bin number.
   *
   */
    virtual int coordToIndex(double coord) const ;

  /**
   * Constants specifying the underflow and the overflow bin.
   * They can be passed to any method accepting a bin number.
   *
   */
    enum { UNDERFLOW_BIN = -2, OVERFLOW_BIN = -1 };

protected:

  TAxis *_axis;
  bool _fixedBinning; 

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IAXISROOT_H */
