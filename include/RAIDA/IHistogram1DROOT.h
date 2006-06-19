// -*- C++ -*-
#ifndef AIDA_IHISTOGRAM1DROOT_H
#define AIDA_IHISTOGRAM1DROOT_H 1

#include <AIDA/IHistogram1D.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>


#include <TH1D.h>
#include <AIDA/IAxis.h>

namespace AIDA {

  /// class IAxis;

/**
 * User level interface to 1D Histogram.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */
 
class IHistogram1DROOT : public IHistogram1D {
friend class IHistogramFactoryROOT ;
public: 
    /// Destructor.
    virtual ~IHistogram1DROOT() { _histogram->Write(); }

  IHistogram1DROOT() { /* nop */; }

  IHistogram1DROOT(const std::string & name, 
                   const std::string & title, 
                   int nBins, 
                   double lowerEdge, 
                   double upperEdge, 
                   const std::string & options = "") ;

  IHistogram1DROOT(const std::string & name, 
                   const std::string & title, 
		   const std::vector<double>  & binEdges,
                   const std::string & options = "") ;

  IHistogram1DROOT(const std::string & name, 
		   const IHistogram1DROOT & hist) ;
  IHistogram1DROOT(const std::string & name, 
		   const IHistogram2DROOT & hist,
		   char axis,
		   int lowerBin = -2,
		   int upperBin = -1) ;

    /**
     * Fill the IHistogram1D with a value and the
     * corresponding weight.
     * @param x      The value to be filled in.
     * @param weight The corresponding weight (by default 1).
     * @return false If the weight is <0 or >1 (?).
     *
     */
  virtual bool fill(double x, double weight = 1.) ;

    /**
     * The weighted mean of a bin. 
     * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The mean of the corresponding bin.
     *
     */
  virtual double binMean(int index) const ;
  // +
// ---------------------------------------------------------------------------
// Functions from IBaseHistogram.h 
// ---------------------------------------------------------------------------

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   *
   */
  virtual std::string title() const;

  /**
   * Set the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   *
   */
  virtual bool setTitle(const std::string & title) ;
  virtual bool setName(const std::string & name) ;

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
  virtual bool reset();

  /**
   * Get the number of in-range entries in the Histogram.
   * @return The number of in-range entries.
   *
   */
  virtual int entries() const ;

// ---------------------------------------------------------------------------
// Functions from IHistogram.h 
// ---------------------------------------------------------------------------

  /**
   * Sum of the entries in all the IHistogram's bins,
   * i.e in-range bins, UNDERFLOW and OVERFLOW.
   * This is equivalent to the number of times the
   * method fill was invoked.
   * @return The sum of all the entries.
   *
   */
  virtual int allEntries() const ;

  /**
   * Number of entries in the UNDERFLOW and OVERFLOW bins.
   * @return The number of entries outside the range of the IHistogram.
   *
   */
  virtual int extraEntries() const ;


  /**
   * Sum of in-range bin heights in the IHistogram,
   * UNDERFLOW and OVERFLOW bins are excluded.
   * @return The sum of the in-range bins heights.
   *
   */
  virtual double sumBinHeights() const ;

  /**
   * Sum of the heights of all the IHistogram's bins,
   * i.e in-range bins, UNDERFLOW and OVERFLOW.
   * @return The sum of all the bins heights.
   *
   */
  virtual double sumAllBinHeights() const ;

  /**
   * Sum of heights in the UNDERFLOW and OVERFLOW bins.
   * @return The sum of the heights of the out-of-range bins.
   *
   */
  virtual double sumExtraBinHeights() const ;

  /**
   * Minimum height of the in-range bins,
   * i.e. not considering the UNDERFLOW and OVERFLOW bins.
   * @return The minimum height among the in-range bins.
   *
   */
  virtual double minBinHeight() const ;

  /**
   * Maximum height of the in-range bins,
   * i.e. not considering the UNDERFLOW and OVERFLOW bins.
   * @return The maximum height among the in-range bins.
   *
   */
  virtual double maxBinHeight() const ;

  /**
   * Scale the weights and the errors of all the IHistogram's bins
   * (in-range and out-of-range ones) by a given scale factor.
   * @param scaleFactor The scale factor.
   * @return false If the scale factor is negative.
   *
   */
  virtual bool scale(double scaleFactor) ;

// ---------------------------------------------------------------------------
// Functions from IHistogram1D.h 
// ---------------------------------------------------------------------------

  /**
   * The weighted mean of a bin.
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The mean of the corresponding bin.
   *
   */
  /// virtual double binMean(int index) const ;

  /**
   * Number of entries in the corresponding bin 
   * (ie the number of times fill was called for this bin).
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The number of entries in the corresponding bin.
   *
   */
  virtual int binEntries(int index) const ;
  // +
  /**
   * Total height of the corresponding bin (ie the sum of the weights in this
   * bin).
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The height of the corresponding bin.
   *
   */
  virtual double binHeight(int index) const ;
  // +
  /**
   * The error of a given bin.
   * @param index The bin number (0...N-1) or OVERFLOW or UNDERFLOW.
   * @return      The error on the corresponding bin.
   *
   */
  virtual double binError(int index) const ;
  // +
  /**
   * The mean of the whole IHistogram1D.
   * @return The mean of the IHistogram1D.
   *
   */
  virtual double mean() const ;

  /**
   * The RMS of the whole IHistogram1D.
   * @return The RMS if the IHistogram1D.
   *
   */
  virtual double rms() const ;

  /**
   * Get the x axis of the IHistogram1D.
   * @return The x coordinate IAxis.
   *
   */
  virtual const IAxis & axis() const ;

  /**
   * Get the bin number corresponding to a given coordinate along the x axis.
   * This is a convenience method, equivalent to 
   * <tt>axis().coordToIndex(coord)</tt>.
   * @see IAxis#coordToIndex(double)
   * @param coord The coordinalte along the x axis.
   * @return      The corresponding bin number.
   *
   */
  virtual int coordToIndex(double coord) const ;
  // +
  virtual bool add(const IHistogram1D & hist) ;
  virtual bool subtract(const IHistogram1D & hist) ;
  virtual bool multiply(const IHistogram1D & hist) ;
  virtual bool divide(const IHistogram1D & hist) ;


protected:


private:

  TH1D *_histogram;
  TH1D *_histogramAIDA;
  TH1D *_histogramAIDABinMean;
  IAxis *_xAxis;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IHISTOGRAM1DROOT_H */
