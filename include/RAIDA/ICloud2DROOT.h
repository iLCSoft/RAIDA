// -*- C++ -*-
#ifndef AIDA_ICLOUD2DROOT_H
#define AIDA_ICLOUD2DROOT_H 1

#include <vector>
#include <TH2D.h>
#include <TTree.h>
#include "AIDA/ICloud.h"
#include "AIDA/ICloud2D.h"
#include <AIDA/ITree.h>
#include <RAIDA/PathName.h>

namespace AIDA {

class IHistogram2D;

/**
 * User level interface to a 2D Cloud.
 * 
 * @author T. Kraemer, DESY
 * @version $Id: ICloud2DROOT.h,v 1.3 2006-12-04 17:24:06 tkraemer Exp $
 */
 
class ICloud2DROOT : public ICloud2D {

public: 
    /// Destructor.
    virtual ~ICloud2DROOT() { /* nop */; }

  /// Constructor
  ICloud2DROOT(const std::string & path,
               const std::string & title,
               int nMax,
	       ITree* usedTree,
               const std::string & options = "");

  ICloud2DROOT(const std::string & path,
               ITree* usedTree,
               const ICloud2DROOT & cloud) ;


    /**
     * Fill the ICloud2D with a couple of values and a corresponding weight.
     * @param x      The x value.
     * @param y      The y value.
     * @param weight The corresponding weight. By default it is 1.
     * @return false If the ICloud2D is full, if the weight's value is
     *                                  is not between 0 and 1.
     *
     */
    virtual bool fill(double x, double y, double weight = 1.) ;

    /**
     * Get the lower edge of the ICloud2D along the x axis.
     * @return The lower edge along the x axis.
     *
     */
    virtual double lowerEdgeX() const ;

    /**
     * Get the lower edge of the ICloud2D along the y axis.
     * @return The lower edge along the y axis.
     *
     */
    virtual double lowerEdgeY() const ;

    /**
     * Get the upper edge of the ICloud2D along the x axis.
     * @return The upper edge along the x axis.
     *
     */
    virtual double upperEdgeX() const ;

    /**
     * Get the upper edge of the ICloud2D along the y axis.
     * @return The upper edge along the y axis.
     *
     */
    virtual double upperEdgeY() const ;

    /**
     * Get the x value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The x value of the index-th entry.
     *              If the ICloud2D has already been converted, 0 is returned. 
     *
     */
    virtual double valueX(int index) const ;

    /**
     * Get the y value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The y value of the index-th entry.
     *              If the ICloud2D has already been converted, 0 is returned. 
     *
     */
    virtual double valueY(int index) const ;

    /**
     * Get the weight corresponding to a given entry.
     * @param index The entry's index.
     * @return      The weight of the index-th entry.
     *              If the ICloud2D has already been converted, 0 is returned. 
     *
     */
    virtual double weight(int index) const ;

    /**
     * Get the mean of the ICloud2D along the x axis.
     * @return The mean along the x axis.
     *
     */
    virtual double meanX() const ;

    /**
     * Get the mean of the ICloud2D along the y axis.
     * @return The mean along the y axis.
     *
     */
    virtual double meanY() const ;

    /**
     * Get the RMS of the ICloud2D along the x axis.
     * @return The RMS along the x axis.
     *
     */
    virtual double rmsX() const ;

    /**
     * Get the RMS of the ICloud2D along the y axis.
     * @return The RMS along the y axis.
     *
     */
    virtual double rmsY() const ;

    /**
     * Convert internally the ICloud2D to an IHistogram2D 
     * with given number of bins, upper edge and lower edge.
     * @param nBinsX     The number of bins of the x axis.
     * @param lowerEdgeX The lower edge of bins of the x axis.
     * @param upperEdgeX The upper edge of bins of the x axis.
     * @param nBinsY     The number of bins of the y axis.
     * @param lowerEdgeY The lower edge of bins of the y axis.
     * @param upperEdgeY The upper edge of bins of the y axis.
     * @return false If the ICloud2D has already been converted.
     *
     */
    virtual bool convert(int nBinsX, 
                         double lowerEdgeX, 
                         double upperEdgeX, 
                         int nBinsY, 
                         double lowerEdgeY, 
                         double upperEdgeY) ;

  virtual bool myConvert(int nBinsX,
			 double lowerEdgeX,
			 double upperEdgeX,
			 int nBinsY,
			 double lowerEdgeY,
			 double upperEdgeY) const ;

    /**
     * Convert internally the ICloud2D to an IHistogram2D 
     * with given bin edges.
     * @param binEdgesX The bins edges of the x axis.
     * @param binEdgesY The bins edges of the y axis.
     * @return false If the ICloud2D has already been converted.
     *
     */
  virtual bool convert(const std::vector<double>  & binEdgesX, const std::vector<double>  & binEdgesY) { throw std::runtime_error("Not implemented"); }

    /**     
     * Get the internal IHistogram2D in which the ICloud2D converted to.
     * @return The histogram.
     *                          or because of a convert() method invocation.
     *
     */
    virtual const IHistogram2D & histogram() const ;

    /**
     * Project the ICloud2D on an IHistogram2D.
     * @param hist The IHistogram2D to be filled.
     * @return false If the ICloud2D is already converted.
     *
     */
    virtual bool fillHistogram(IHistogram2D & hist) const ;

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
    virtual bool convertToHistogram() ;
    virtual bool myConvertToHistogram() const ;

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
  virtual IAnnotation & annotation() { throw std::runtime_error("Not implemented"); }

  virtual const IAnnotation & annotation() const { throw std::runtime_error("Not implemented"); }

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
  virtual void * cast(const std::string & className) const { throw std::runtime_error("Not implemented"); }

private:

  PathName _path;
  ITree* _usedTree;
  mutable IHistogram2D *_AIDAHistogram;

  mutable bool _isConverted;
  static const int _nBinsDefault = 100;
  int _nMax;
  mutable TTree *_ROOTTree;

  Double_t _xValue;
  Double_t _yValue;
  Double_t _zValue;

  mutable double _histoLowerEdgeX;
  mutable double _histoUpperEdgeX;
  mutable double _histoLowerEdgeY;
  mutable double _histoUpperEdgeY;

}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ICLOUD2DROOT_H */
