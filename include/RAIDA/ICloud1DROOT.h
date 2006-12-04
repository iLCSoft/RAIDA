// -*- C++ -*-
#ifndef AIDA_ICLOUD1DROOT_H
#define AIDA_ICLOUD1DROOT_H 1

#include <vector>
#include <TH1D.h>
#include <TTree.h>
#include "AIDA/ICloud.h"
#include "AIDA/ICloud1D.h"
#include <AIDA/ITree.h>
#include <RAIDA/PathName.h>
namespace AIDA {

class IHistogram1D;

/**
 * User level interface to a 1D Cloud.
 *
 * @author T. Kraemer, DESY
 * @version $Id: ICloud1DROOT.h,v 1.3 2006-12-04 17:24:06 tkraemer Exp $
 */
 
class ICloud1DROOT : public ICloud1D {

public: 
    /// Destructor.
    virtual ~ICloud1DROOT() { /* nop */; }

  /// Constructor
  ICloud1DROOT(const std::string & path,
	       const std::string & title,
	       int nMax,
	       ITree* usedTree,
	       const std::string & options = "");

  ICloud1DROOT(const std::string & path,
	       ITree* usedTree,
	       const ICloud1DROOT & cloud) ;

    /**
     * Fill the ICloud1D with a value and a corresponding weight.
     * @param x      The value.
     * @param weight The corresponding weight. By default it is 1.
     * @return false If the ICloud1D is full, if the weight's value is
     *                                  is not between 0 and 1.
     *
     */
    virtual bool fill(double x, double weight = 1.) ;

    /**
     * Get the lower edge of the ICloud1D.
     * @return The lower edge.
     *
     */
    virtual double lowerEdge() const ;

    /**
     * Get the upper edge of the ICloud1D.
     * @return The upper edge.
     *
     */
    virtual double upperEdge() const ;

    /**
     * Get the value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The value of the index-th entry.
     *              If the ICloud1D has already been converted, 0 is returned.
     *
     */
    virtual double value(int index) const ;

    /**
     * Get the weight corresponding to a given entry.
     * @param index The entry's index.
     * @return      The weight of the index-th entry.
     *              If the ICloud1D has already been converted, 0 is returned.
     *
     */
    virtual double weight(int index) const ;

    /**
     * Get the mean of the ICloud1D.
     * @return The mean.
     *
     */
    virtual double mean() const ;

    /**
     * Get the RMS of the ICloud1D.
     * @return The RMS.
     *
     */
    virtual double rms() const ;

    /**
     * Convert internally the ICloud1D to an IHistogram1D
     * with given number of bins, upper edge and lower edge.
     * @param nBins     The number of bins.
     * @param lowerEdge The lower edge.
     * @param upperEdge The upper edge.
     * @return false If the ICloud1D has already been converted.
     *
     */
    virtual bool myConvert(int nBins, double lowerEdge, double upperEdge) const ;
    virtual bool convert(int nBins, double lowerEdge, double upperEdge) ;

    /**
     * Convert internally the ICloud1D to an IHistogram1D
     * with given bin edges.
     * @param binEdges The bins edges.
     * @return false If the ICloud1D has already been converted.
     *
     */
  /// virtual bool convert(const std::vector<double>  & binEdges) ;

    /**
     * Get the internal IHistogram1D in which the ICloud1D converted to.
     * @return The histogram.
     *                          or because of a convert() method invocation.
     *
     */
    virtual const IHistogram1D & histogram() const ;

    /**
     * Project the ICloud1D on an IHistogram1D.
     * @param hist The IHistogram1D to be filled.
     * @return false If the ICloud1D is already converted.
     *
     */
    virtual bool fillHistogram(IHistogram1D & hist) const ;

// ----------------------------------------------------------------------------
// Functions from ICloud 
// ----------------------------------------------------------------------------

   /**
     * Get the sum of weights of all the entries.
     * @return The sum of the weights of all the entries.
     *
     */
    virtual double sumOfWeights() const ;

    /**
     * Convert the ICloud to an IHistogram using the default number of bins.
     * @return false If the ICloud has already been converted.
     *
     */
    virtual bool myConvertToHistogram() const;
    virtual bool convertToHistogram() ;

    /**
     * Check if the ICloud has been converted to an IHistogram.
     * @return <code>true</code> if it has been converted.
     *
     */
    virtual bool isConverted() const ;

    /**
     * Get the number of entries after which the cloud will be converted to an IHistogram.
     * @return The number of entries.
     *
     */
    virtual int maxEntries() const ;

    /**
     * Scale the weights by a given factor.
     * @param scaleFactor The scale factor.
     * @return false If a non-positive scale factor is provided.
     *
     */
    virtual bool scale(double scaleFactor) ;

// ----------------------------------------------------------------------------
// Functions from IBaseHistogram 
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

private: 

  PathName _path;
  ITree* _usedTree;
  mutable IHistogram1D *_AIDAHistogram;

  mutable bool _isConverted;
  static const int _nBinsDefault = 100;
  int _nMax;
  mutable TTree *_ROOTTree; 

  Double_t _xValue;
  Double_t _yValue;

  mutable double _histoLowerEdge;
  mutable double _histoUpperEdge;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ICLOUD1DROOT_H */
