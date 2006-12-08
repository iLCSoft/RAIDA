// -*- C++ -*-
#ifndef AIDA_IDATAPOINTSETROOT_H
#define AIDA_IDATAPOINTSETROOT_H 1

#include <string>
#include <vector>

#include <AIDA/IDataPointSet.h>

namespace AIDA {

class IAnnotation;
class IDataPoint;

/**
 * Basic user-level interface class for holding and managing
 * a single set of "data points".
 *
 * @author T. Kraemer, DESY
 * @version $Id: IDataPointSetROOT.h,v 1.1 2006-12-08 10:58:59 tkraemer Exp $
 */

class IDataPointSetROOT : public IDataPointSet {

public: 
    /// Destructor.
  virtual ~IDataPointSetROOT() { /* nop */; }

  IDataPointSetROOT() { /* nop */; }

    /**
     * Get the IAnnotation of the IDataPointSet.
     * @return The IAnnotation.
     *
     */
  virtual IAnnotation & annotation() ;

  virtual const IAnnotation & annotation() const;

    /**
     * Get the title of the IDataPointSet.
     * @return The title.
     *
     */
  virtual std::string title() const ;

    /**
     * Set the title of the IDataPointSet.
     * @param title The new title.
     * @return false If the title cannot be set.
     *
     */
  virtual bool setTitle(const std::string & title) ;

    /**
     * Get the dimension of the IDataPoints that can be stored in the set.
     * @return The dimension of the IDataPoints storable in the set.
     *
     */
  virtual int dimension() const ;

    /**
     * Remove all the IDataPoints in the set.
     * After this the IDataPointSet is as just created.
     *
     */
  virtual void clear() ;

    /**
     * Get the current size of the IDataPointSet, i.e. the number
     * of IDataPoints contained in the set.
     * @return The size of the IDataPointSet.
     *
     */
  virtual int size() const ;

    /**
     * Get the IDataPoint at a give index in the set.
     * @param index The IDataPoint index.
     * @return      The corresponding IDataPoint.
     *
     */
  virtual IDataPoint * point(int index) ;

    /**
     * Set the values and errors of a given coordinate all at once.
     * If this method is called on an empty IDataPointSet, a number of points equal
     * to the size of the arrays provided is created; if the IDataPointSet is not empty
     * the dimension of the array must match with the size of the IDataPointSet.
     * @param coord The coordinate's index
     * @param val   The array of the values for the given coordinate
     * @param err   The array with the symmetric errors.
     * @return false if an illegal coordinate is provided or if
     *              there is a mismatch between the size of the array and the size of the IDataPointSet.
     *
     */
  virtual bool setCoordinate(int coord, 
			     const std::vector<double>  & val, 
			     const std::vector<double>  & err) ;

    /**
     * Set the values and errors of a given coordinate all at once.
     * If this method is called on an empty IDataPointSet, a number of points equal
     * to the size of the arrays provided is created; if the IDataPointSet is not empty
     * the dimension of the array must match with the size of the IDataPointSet.
     * @param coord The coordinate's index
     * @param val   The array of the values for the given coordinate
     * @param errp  The array with the plus errors.
     * @param errm  The array with the minus errors.
     * @return false if an illegal coordinate is provided or if
     *              there is a mismatch between the size of the array and the size of the IDataPointSet.
     *
     */
  virtual bool setCoordinate(int coord, 
			     const std::vector<double>  & val, 
			     const std::vector<double>  & errp, 
			     const std::vector<double>  & errm) ;

  virtual const IDataPoint * point(int index) const ;

    /**
     * Add a new empty IDataPoint at the end of the set.
     * @return The newly added point.
     *
     */
  virtual IDataPoint * addPoint() ;

    /**
     * Add a copy of an IDataPoint at the end of the set.
     * @param point The IDataPoint to be added.
     * @return false If the point has the wrong dimension or
     *                                       if the point cannot be added.
     *
     */
  virtual bool addPoint(const IDataPoint & point) ;

    /**
     * Remove the IDataPoint at a given index.
     * @param index The index of the IDataPoint to be removed.
     * @return false If the index is < 0 or >= size().
     *
     */
  virtual bool removePoint(int index) ;

    /**
     * Get the lower value for a give axis.
     * @param coord The coordinate of the axis.
     * @return      The lower edge of the corresponding axis.
     *              If coord < 0 or coord >= dimension(), or if the set is empty NaN is returned.
     *
     */
  virtual double lowerExtent(int coord) const ;

    /**
     * Get the upper value for a give axis.
     * @param coord The coordinate of the axis.
     * @return      The upper edge of the corresponding axis.
     *              If coord < 0 or coord >= dimension(), or if the set is empty NaN is returned.
     *
     */
  virtual double upperExtent(int coord) const ;

    /**
     * Scales the values and the errors of all the measurements
     * of each point by a given factor.
     * @param scaleFactor The scale factor.
     * @return false If an illegal scaleFactor is provided.
     *
     */
  virtual bool scale(double scaleFactor) ;

    /**
     * Scales the values of all the measurements
     * of each point by a given factor.
     * @param scaleFactor The scale factor.
     * @return false If an illegal scaleFactor is provided.
     *
     */
  virtual bool scaleValues(double scaleFactor) ;

    /**
     * Scales the errors of all the measurements
     * of each point by a given factor.
     * @param scaleFactor The scale factor.
     * @return false If an illegal scaleFactor is provided.
     *
     */
  virtual bool scaleErrors(double scaleFactor) ;

    /**
     *  See IManagedObject for a description.
     * @param className The name of the class to cast on.
     * @return The right pointer. Return 0 if failure.
     */ 
  virtual void * cast(const std::string & className) const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IDATAPOINTSETROOT_H */
