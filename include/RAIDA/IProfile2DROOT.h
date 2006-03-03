// -*- C++ -*-
#ifndef AIDA_IPROFILE2DROOT_H
#define AIDA_IPROFILE2DROOT_H 1


#include "AIDA/IProfile2D.h"
#include <AIDA/IAxis.h>

#include <TH2D.h>
#include <TProfile2D.h>

namespace AIDA {

  // class IAxis;

/**
 * User level interface to a 2-dimensional profile histogram
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */

class IProfile2DROOT : public IProfile2D {

public: 
    /// Destructor.
    virtual ~IProfile2DROOT() { /* nop */; }

  /// constructor
  IProfile2DROOT(const std::string & name,
		 const std::string & title,
		 int nBinsX,
		 double lowerEdgeX,
		 double upperEdgeX,
		 int nBinsY,
		 double lowerEdgeY,
		 double upperEdgeY,
		 const std::string & options = "");

  IProfile2DROOT() { /* nop */; }

    /**
     * Fill the IProfile2D.
     *
     */
    virtual bool fill(double x, double y, double z, double weight = 1) ;

    /**
     * The weighted mean along x of a given bin. 
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return       The mean of the corresponding bin along the x axis.
     *
     */
    virtual double binMeanX(int indexX, int indexY) const ;

    /**
     * The weighted mean along y of a given bin. 
     * @param indexX The x bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @param indexY The y bin number (0...N-1) or OVERFLOW or UNDERFLOW.
     * @return       The mean of the corresponding bin along the x axis.
     *
     */
    virtual double binMeanY(int indexX, int indexY) const ;

    /**
     * The number of entries (ie the number of times fill was called for this bin).
     * @param indexX the x bin number (0...Nx-1) or OVERFLOW or UNDERFLOW.
     * @param indexY the y bin number (0...Ny-1) or OVERFLOW or UNDERFLOW.
     *
     */
    virtual int binEntries(int indexX, int indexY) const ;

    /**
     * Equivalent to <tt>projectionX().binEntries(indexX)</tt>.
     *
     */
    virtual int binEntriesX(int indexX) const ;

    /**
     * Equivalent to <tt>projectionY().binEntries(indexY)</tt>.
     *
     */
    virtual int binEntriesY(int indexY) const ;

    /**
     * Total height of the corresponding bin (ie the sum of the weights in this bin).
     * @param indexX the x bin number (0...Nx-1) or OVERFLOW or UNDERFLOW.
     * @param indexY the y bin number (0...Ny-1) or OVERFLOW or UNDERFLOW.
     *
     */
    virtual double binHeight(int indexX, int indexY) const ;

    /**
     * Equivalent to <tt>projectionX().binHeight(indexX)</tt>.
     *
     */
    virtual double binHeightX(int indexX) const ;

    /**
     * Equivalent to <tt>projectionY().binHeight(indexY)</tt>.
     *
     */
    virtual double binHeightY(int indexY) const ;

    /**
     * The error on this bin.
     * @param indexX the x bin number (0...Nx-1) or OVERFLOW or UNDERFLOW.
     * @param indexY the y bin number (0...Ny-1) or OVERFLOW or UNDERFLOW.
     *
     */
    virtual double binError(int indexX, int indexY) const ;

    /**
     * The spread (RMS) of this bin.
     * @param indexX the x bin number (0...Nx-1) or OVERFLOW or UNDERFLOW.
     * @param indexY the y bin number (0...Ny-1) or OVERFLOW or UNDERFLOW.
     *
     */
    virtual double binRms(int indexX, int indexY) const ;

    /**
     * Returns the mean of the profile, as calculated on filling-time projected on the X axis.
     *
     */
    virtual double meanX() const ;

    /**
     * Returns the mean of the profile, as calculated on filling-time projected on the Y axis.
     *
     */
    virtual double meanY() const ;

    /**
     * Returns the rms of the profile as calculated on filling-time projected on the X axis.
     *
     */
    virtual double rmsX() const ;

    /**
     * Returns the rms of the profile as calculated on filling-time projected on the Y axis.
     *
     */
    virtual double rmsY() const ;

    /**
     * Return the X axis.
     *
     */
  virtual const IAxis & xAxis() const ;

    /**
     * Return the Y axis.
     *
     */
  virtual const IAxis & yAxis() const ;

    /**
     * Convenience method, equivalent to <tt>xAxis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     *
     */
    virtual int coordToIndexX(double coordX) const ;

    /**
     * Convenience method, equivalent to <tt>yAxis().coordToIndex(coord)</tt>.
     * @see IAxis#coordToIndex(double)
     *
     */
    virtual int coordToIndexY(double coordY) const ;

    /**
     * Modifies this profile by adding the contents of profile to it.
     *
     * @param profile The IProfile2D to be added to this IProfile2D
     * @return false if the profile binnings are incompatible
     *
     */
  /// virtual bool add(const IProfile2D & h) ;

// ----------------------------------------------------------------------------
//  Functions from IProfile.h
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

  TProfile2D* _profile;
  TH2D*     _histogram;
  TH2D*     _histogramAIDA;
  TH2D*     _histogramAIDABinMeanX;
  TH2D*     _histogramAIDABinMeanY;
  IAxis *_xAxis;
  IAxis *_yAxis;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IPROFILE2DROOT_H */
