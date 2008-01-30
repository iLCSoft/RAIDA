// -*- C++ -*-
#ifndef AIDA_IHISTOGRAM3DROOT_H
#define AIDA_IHISTOGRAM3DROOT_H 1

#include <AIDA/IHistogram3D.h>
#include <AIDA/IAxis.h>

#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <vector>

namespace AIDA {

  /// class IAxis;

/**
 * User level interface to 3D Histogram.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IHistogram3DROOT.h,v 1.11 2008-01-30 17:42:20 killenberg Exp $
 */

class IHistogram3DROOT : public IHistogram3D {
  friend class IHistogramFactoryROOT ;
  friend class IHistogram2DROOT ;

public: 
    /// Destructor.
    virtual ~IHistogram3DROOT();

  /// Constructor.
    IHistogram3DROOT();

  IHistogram3DROOT(const std::string & name,
                   const std::string & title,
                   int nBinsX,
                   double lowerEdgeX,
                   double upperEdgeX,
                   int nBinsY,
                   double lowerEdgeY,
                   double upperEdgeY,
                   int nBinsZ,
                   double lowerEdgeZ,
                   double upperEdgeZ,
                   const std::string & options = "") ;

  IHistogram3DROOT(const std::string & name,
                   const std::string & title,
		   const std::vector<double>  & binEdgesX,
                   const std::vector<double>  & binEdgesY,
                   const std::vector<double>  & binEdgesZ,
                   const std::string & options = "") ;

  IHistogram3DROOT(const std::string & name,
                   const IHistogram3DROOT & hist) ;

    /**
     * Fill the IHistogram3D with a triplet of values and the
     * corresponding weight.
     * @param x      The x value to be filled in.
     * @param y      The y value to be filled in.
     * @param z      The z value to be filled in.
     * @param weight The corresponding weight (by default 1).
     * @return false If the weight is <0 or >1 (?).
     *
     */
    virtual bool fill(double x, double y, double z, double weight = 1.) ;

    /**
     * The weighted mean along the x axis of a given bin.
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The mean of the corresponding bin along the x axis.
     *
     */
    virtual double binMeanX(int indexX, int indexY, int indexZ) const ;

    /**
     * The weighted mean the y axis of a given bin.
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The mean of the corresponding bin along the y axis.
     *
     */
    virtual double binMeanY(int indexX, int indexY, int indexZ) const ;

    /**
     * The weighted mean the z axis of a given bin. 
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The mean of the corresponding bin along the z axis.
     *
     */
    virtual double binMeanZ(int indexX, int indexY, int indexZ) const ;

    /**
     * Number of entries in the corresponding bin (ie the number of times fill was called for this bin).
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return       The number of entries in the corresponding bin. 
     *
     */
    virtual int binEntries(int indexX, int indexY, int indexZ) const ;

    /**
     * Sum of all the entries of the bins along a given x bin.
     * This is equivalent to <tt>projectionXY().binEntriesX(index)</tt>.
     * @param index The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The number of entries in the corresponding set of bins. 
     *
     */
    virtual int binEntriesX(int index) const ;

    /**
     * Sum of all the entries of the bins along a given y bin.
     * This is equivalent to <tt>projectionXY().binEntriesY(index)</tt>.
     * @param index The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The number of entries in the corresponding set of bins. 
     *
     */
    virtual int binEntriesY(int index) const ;

    /**
     * Sum of all the entries of the bins along a given z bin.
     * This is equivalent to <tt>projectionXZ().binEntriesZ(index)</tt>.
     * @param index The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The number of entries in the corresponding set of bins. 
     *
     */
    virtual int binEntriesZ(int index) const ;

    /**
     * Total height of a give bin (ie the sum of the weights in this bin).
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return       The height of the corresponding bin.
     *
     */
    virtual double binHeight(int indexX, int indexY, int indexZ) const ;

    /**
     * Sum of all the heights of the bins along a given x bin.
     * This is equivalent to <tt>projectionXY().binHeightX(index)</tt>.
     * @param index The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The sum of the heights in the corresponding set of bins. 
     *
     */
    virtual double binHeightX(int index) const ;

    /**
     * Sum of all the heights of the bins along a given y bin.
     * This is equivalent to <tt>projectionXY().binHeightY(index)</tt>.
     * @param index The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The sum of the heights in the corresponding set of bins. 
     *
     */
    virtual double binHeightY(int index) const ;

    /**
     * Sum of all the heights of the bins along a given z bin.
     * This is equivalent to <tt>projectionXZ().binHeightZ(index)</tt>.
     * @param index The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return      The sum of the heights in the corresponding set of bins. 
     *
     */
    virtual double binHeightZ(int index) const ;

    /**
     * The error of a given bin.
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexZ The z bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return       The error on the corresponding bin.
     *
     */
    virtual double binError(int indexX, int indexY, int indexZ) const ;

    /**
     * The mean of the IHistogram3D along the x axis.
     * @return The mean of the IHistogram3D along the x axis.
     *
     */
    virtual double meanX() const ;

    /**
     * The mean of the IHistogram3D along the y axis.
     * @return The mean of the IHistogram3D along the y axis.
     *
     */
    virtual double meanY() const ;

    /**
     * The mean of the IHistogram3D along the z axis.
     * @return The mean of the IHistogram3D along the z axis.
     *
     */
    virtual double meanZ() const ;

    /**
     * The RMS of the IHistogram3D along the x axis.
     * @return The RMS if the IHistogram3D along the x axis.
     *
     */
    virtual double rmsX() const ;

    /**
     * The RMS of the IHistogram3D along the y axis.
     * @return The RMS if the IHistogram3D along the y axis.
     *
     */
    virtual double rmsY() const ;

    /**
     * The RMS of the IHistogram3D along the z axis.
     * @return The RMS if the IHistogram3D along the z axis.
     *
     */
    virtual double rmsZ() const ;

    /**
     * Get the x axis of the IHistogram3D.
     * @return The x coordinate IAxis.
     *
     */
  virtual const IAxis & xAxis() const ;

    /**
     * Get the y axis of the IHistogram3D.
     * @return The y coordinate IAxis.
     *
     */
  virtual const IAxis & yAxis() const ;

    /**
     * Get the z axis of the IHistogram3D.
     * @return The z coordinate IAxis.
     *
     */
  virtual const IAxis & zAxis() const ;

    /**
     * Get the bin number corresponding to a given coordinate along the x axis.
     * This is a convenience method, equivalent to <tt>xAxis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     * @param coord The coordinalte along the x axis.
     * @return      The corresponding bin number.
     *
     */
    virtual int coordToIndexX(double coord) const ;

    /**
     * Get the bin number corresponding to a given coordinate along the y axis.
     * This is a convenience method, equivalent to <tt>yAxis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     * @param coord The coordinalte along the y axis.
     * @return      The corresponding bin number.
     *
     */
    virtual int coordToIndexY(double coord) const ;

    /**
     * Get the bin number corresponding to a given coordinate along the z axis.
     * This is a convenience method, equivalent to <tt>zAxis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     * @param coord The coordinalte along the z axis.
     * @return      The corresponding bin number.
     *
     */
    virtual int coordToIndexZ(double coord) const ;

    /**
     * Add to this IHistogram3D the contents of another IHistogram3D.
     * @param hist The IHistogram3D to be added to this IHistogram3D.
     * @return false If the IHistogram3Ds binnings are incompatible.
     *
     */
  virtual bool add(const IHistogram3D & hist) ;
  virtual bool subtract(const IHistogram3D & hist) ;
  virtual bool multiply(const IHistogram3D & hist) ;
  virtual bool divide(const IHistogram3D & hist) ;

// ---------------------------------------------------------------------------
// Functions from IBaseHistogram.h
// ---------------------------------------------------------------------------

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
  virtual bool setName(const std::string & name) ;

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
     * Number of equivalent entries, i.e. <tt>SUM[ weight ] ^ 2 / SUM[ weight^2 ]</tt>
     * @return The number of equivalent entries.
     *
     */
  /// virtual double equivalentBinEntries() const ;

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

  /** Print out the contents of a histogram to the screen.
   * This method is made for debugging purposes. It is not part of the
   * AIDA Interface!
   */
  virtual void printContents() const ;

protected:


private:

  TH3D *_histogram;
  TH3D *_histogramAIDA;
  TH3D *_histogramAIDABinMeanX;
  TH3D *_histogramAIDABinMeanY;
  TH3D *_histogramAIDABinMeanZ;

  IAxis *_xAxis;
  IAxis *_yAxis;
  IAxis *_zAxis;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IHISTOGRAM3DROOT_H */
