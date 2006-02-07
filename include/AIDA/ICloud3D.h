// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef AIDA_ICLOUD3D_H
#define AIDA_ICLOUD3D_H 1

//  This file is part of the AIDA library
//  Copyright (C) 2002 by the AIDA team.  All rights reserved.
//  This library is free software and under the terms of the
//  GNU Library General Public License described in the LGPL.txt 

#include <vector>

#include "AIDA/ICloud.h"

namespace AIDA {

class IHistogram3D;

/**
 * User level interface to a 3D Cloud.
 * 
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */

class ICloud3D : virtual public ICloud {

public: 
    /// Destructor.
    virtual ~ICloud3D() { /* nop */; }

    /**
     * Fill the ICloud3D with a triplet of values and a corresponding weight.
     * @param x      The x value.
     * @param y      The y value.
     * @param z      The z value.
     * @param weight The corresponding weight. By default it is 1.
     * @return false If the ICloud3D is full, if the weight's value is
     *                                  is not between 0 and 1.
     *
     */
    virtual bool fill(double x, double y, double z, double weight = 1.) = 0;

    /**
     * Get the lower edge of the ICloud3D along the x axis.
     * @return The lower edge along the x axis.
     *
     */
    virtual double lowerEdgeX() const = 0;

    /**
     * Get the lower edge of the ICloud3D along the y axis.
     * @return The lower edge along the y axis.
     *
     */
    virtual double lowerEdgeY() const = 0;

    /**
     * Get the lower edge of the ICloud3D along the z axis.
     * @return The lower edge along the z axis.
     *
     */
    virtual double lowerEdgeZ() const = 0;

    /**
     * Get the upper edge of the ICloud3D along the x axis.
     * @return The upper edge along the x axis.
     *
     */
    virtual double upperEdgeX() const = 0;

    /**
     * Get the upper edge of the ICloud3D along the y axis.
     * @return The upper edge along the y axis.
     *
     */
    virtual double upperEdgeY() const = 0;

    /**
     * Get the upper edge of the ICloud3D along the z axis.
     * @return The upper edge along the z axis.
     *
     */
    virtual double upperEdgeZ() const = 0;

    /**
     * Get the x value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The x value of the index-th entry.
     *              If the ICloud3D has already been converted, 0 is returned. 
     *
     */
      
           
       
                                                      
                                      
                                                      
                                                                                         
      
       
      
    virtual double valueX(int index) const = 0;

    /**
     * Get the y value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The y value of the index-th entry.
     *              If the ICloud3D has already been converted, 0 is returned.
     *
     */
      
           
       
                                                      
                                      
                                                      
                                                                                         
      
       
      
    virtual double valueY(int index) const = 0;

    /**
     * Get the z value corresponding to a given entry.
     * @param index The entry's index.
     * @return      The z value of the index-th entry.
     *              If the ICloud3D has already been converted, 0 is returned.
     *
     */
      
           
       
                                                      
                                      
                                                      
                                                                                         
      
       
      
    virtual double valueZ(int index) const = 0;

    /**
     * Get the weight corresponding to a given entry.
     * @param index The entry's index.
     * @return      The weight of the index-th entry.
     *              If the ICloud3D has already been converted, 0 is returned.
     *
     */
      
           
       
                                                     
                                      
                                                     
                                                                                       
      
       
      
    virtual double weight(int index) const = 0;

    /**
     * Get the mean of the ICloud3D along the x axis.
     * @return The mean along the x axis.
     *
     */
    virtual double meanX() const = 0;

    /**
     * Get the mean of the ICloud3D along the y axis.
     * @return The mean along the y axis.
     *
     */
    virtual double meanY() const = 0;

    /**
     * Get the mean of the ICloud3D along the z axis.
     * @return The mean along the z axis.
     *
     */
    virtual double meanZ() const = 0;

    /**
     * Get the RMS of the ICloud3D along the x axis.
     * @return The RMS along the x axis.
     *
     */
    virtual double rmsX() const = 0;

    /**
     * Get the RMS of the ICloud3D along the y axis.
     * @return The RMS along the y axis.
     *
     */
    virtual double rmsY() const = 0;

    /**
     * Get the RMS of the ICloud3D along the z axis.
     * @return The RMS along the z axis.
     *
     */
    virtual double rmsZ() const = 0;

    /**
     * Convert internally the ICloud3D to an IHistogram3D 
     * with given number of bins, upper edge and lower edge.
     * @param nBinsX     The number of bins of the x axis.
     * @param lowerEdgeX The lower edge of bins of the x axis.
     * @param upperEdgeX The upper edge of bins of the x axis.
     * @param nBinsY     The number of bins of the y axis.
     * @param lowerEdgeY The lower edge of bins of the y axis.
     * @param upperEdgeY The upper edge of bins of the y axis.
     * @param nBinsZ     The number of bins of the z axis.
     * @param lowerEdgeZ The lower edge of bins of the z axis.
     * @param upperEdgeZ The upper edge of bins of the z axis.
     * @return false If the ICloud3D has already been converted.
     *
     */
    virtual bool convert(int nBinsX, double lowerEdgeX, double upperEdgeX, int nBinsY, double lowerEdgeY, double upperEdgeY, int nBinsZ, double lowerEdgeZ, double upperEdgeZ) = 0;

    /**
     * Convert internally the ICloud3D to an IHistogram3D 
     * with given bin edges.
     * @param binEdgesX The bins edges of the x axis.
     * @param binEdgesY The bins edges of the y axis.
     * @param binEdgesZ The bins edges of the z axis.
     * @return false If the ICloud3D has already been converted.
     *
     */
  /// virtual bool convert(const std::vector<double>  & binEdgesX, const std::vector<double>  & binEdgesY, const std::vector<double>  & binEdgesZ) = 0;

    /**     
     * Get the internal IHistogram3D in which the ICloud3D converted to.
     * @return The histogram.
     *                          or because of a convert() method invocation.
     *
     */
    virtual const IHistogram3D & histogram() const = 0;

    /**
     * Project the ICloud3D on an IHistogram3D.
     * @param hist The IHistogram3D to be filled.
     * @return false If the ICloud3D is already converted.
     *
     */
    virtual bool fillHistogram(IHistogram3D & hist) const = 0;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ICLOUD3D_H */
