// -*- C++ -*-
#ifndef AIDA_IPROFILE1DROOT_H
#define AIDA_IPROFILE1DROOT_H 1

#include "AIDA/IProfile1D.h"
#include <AIDA/IAxis.h>
#include <TH1D.h>
#include <TProfile.h>

namespace AIDA {

  // class IAxis;

/**
 * User level interface to a 1-dimensional profile histogram
 *
 * @author T. Kraemer, DESY
 * @version $Id: IProfile1DROOT.h,v 1.6 2006-12-04 17:24:06 tkraemer Exp $
 */
 
class IProfile1DROOT : public IProfile1D {

public: 
    /// Destructor.
    virtual ~IProfile1DROOT() { /* nop */; }

  /// constructor
  IProfile1DROOT() { /* nop */; }

  IProfile1DROOT(const std::string & name,
		 const std::string & title,
		 int nBins,
		 double lowerEdge,
		 double upperEdge,
		 const std::string & options = "");

  IProfile1DROOT(const std::string & name,
		 const std::string & title,
		 int nBins,
		 double lowerEdge,
		 double upperEdge,
		 double lowerValue,
		 double upperValue,
		 const std::string & options = "");

  IProfile1DROOT(const std::string & name,
		 const std::string & title,
		 const std::vector<double>  & binEdges,
		 const std::string & options = "");

  IProfile1DROOT(const std::string & name,
		 const std::string & title,
		 const std::vector<double>  & binEdges,
		 double lowerValue,
		 double upperValue,
		 const std::string & options = "");

  IProfile1DROOT(const std::string & name,
                   const IProfile1DROOT & profile) ;

    /**
     * Fill the IProfile1D.
     *
     */
    virtual bool fill(double x, double y, double weight = 1) ;

    /**
     * The weighted mean of the corresponding bin.
     * @param index the bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The mean of the corresponding bin along the x axis.
     *
     */
    virtual double binMean(int index) const ;

    /**
     * Number of entries in the corresponding bin (ie the number of times fill was called for this bin).
     * @param index the bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     */
    virtual int binEntries(int index) const ;

    /**
     * Total height of the corresponding bin (ie the sum of the weights in this bin).
     * @param index the bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     */
    virtual double binHeight(int index) const ;

    /**
     * The error on this bin.
     * @param index the bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     */
    virtual double binError(int index) const ;

    /**
     * The spread (RMS) of a bin.
     * @param index the bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     *
     */
    virtual double binRms(int index) const ;

    /**
     * Returns the mean of the whole profile as calculated on filling-time.
     */
    virtual double mean() const ;

    /**
     * Returns the rms of the whole profile as calculated on filling-time.
     */
    virtual double rms() const ;

    /**
     * Returns the X axis.
     */
  virtual const IAxis & axis() const ;

    /**
     * Convenience method, equivalent to <tt>axis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     */
    virtual int coordToIndex(double coord) const ;

    /**
     * Modifies this IProfile1D by adding the contents of profile to it.
     *
     * @param profile The IProfile1D to be added to this IProfile1D
     * @return false if profile binnings are incompatible
     */
  /// virtual bool add(const IProfile1D & profile) ;

// ----------------------------------------------------------------------------
//  Functions from IHistogram.h
// ----------------------------------------------------------------------------

    /**
     * Get the number or all the entries, both in range and 
     * underflow/overflow bins of the IProfile.
     * @return The sum of all the entries.
     *
     */
    virtual int allEntries() const ;

    /**
     * Get the number of entries in the underflow and overflow bins.
     * @return The numer of entries in the out-of-range bins.
     *
     */
    virtual int extraEntries() const ;

    /**
     * Get the sum of in range bin heights in the IProfile.
     * @return The sum of all the in-range bins heights.
     *
     */
    virtual double sumBinHeights() const ;

    /**
     * Get the sum of all the bins heights (including underflow and overflow bin).
     * @return The sum of all the bins heights.
     *
     */
    virtual double sumAllBinHeights() const ;

    /**
     * Get the sum of the underflow and overflow bin height.
     * @return The sum of the out-of-range bins heights.
     *
     */
    virtual double sumExtraBinHeights() const ;

    /**
     * Get the minimum height of the in-range bins.
     * @return The minimum height among the in-range bins.
     *
     */
    virtual double minBinHeight() const ;

    /**
     * Get the maximum height of the in-range bins.
     * @return The maximum height among the in-range bins.
     *
     */
  virtual double maxBinHeight() const ;
// ----------------------------------------------------------------------------
//  Functions from IBaseHistogram
// ----------------------------------------------------------------------------

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   *
   */
  virtual std::string title() const ;

  /**
   * Set the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   *
   */
  virtual bool setTitle(const std::string & title) ;

  /**
   * Get the IAnnotation associated with the Histogram.
   * @return The IAnnotation.
   *
   */
  /// virtual IAnnotation & annotation() ;

  /// virtual const IAnnotation & annotation() const ;

  /**
   * Get the Histogram's dimension.
   * @return The Histogram's dimension.
   *
   */ 
  virtual int dimension() const ;

  /**
   * Reset the Histogram; as if just created.
   * @return false If something goes wrong.
   *
   */
  virtual bool reset() ;

  /**
   * Get the number of in-range entries in the Histogram.
   * @return The number of in-range entries.
   *
   */ 
  virtual int entries() const ;

  /**
   *  See IManagedObject for a description.
   * @param className The name of the class to cast on.
   * @return The right pointer. Return 0 if failure.
   */ 
  /// virtual void * cast(const std::string & className) const ;

protected:


private:

  void Profile1DHistograms(const std::string & name,
			   const std::string & title,
			   int nBins,
			   double lowerEdge,
			   double upperEdge);
  void Profile1DHistograms(const std::string & name,
			   const std::string & title,
			   const std::vector<double>  & binEdges);

  TProfile* _profile;
  TH1D*     _histogram;
  TH1D*     _histogramAIDA;
  TH1D*     _histogramAIDABinMeanX;
  IAxis *_xAxis;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPROFILE1DROOT_H */
