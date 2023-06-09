// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef AIDA_IBASEHISTOGRAM_H
#define AIDA_IBASEHISTOGRAM_H 1

//  This file is part of the AIDA library
//  Copyright (C) 2002 by the AIDA team.  All rights reserved.
//  This library is free software and under the terms of the
//  GNU Library General Public License described in the LGPL.txt 

#include <string>

namespace AIDA {

class IAnnotation;

/**
 * User level interface to Histogram.
 * Provides the common functionality of the histogram-like classes.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */
 
class IBaseHistogram {

public: 
    /// Destructor.
    virtual ~IBaseHistogram() { /* nop */; }

  /**
   * Get the Histogram's title.
   * @return The Histogram's title.
   *
   */
  virtual std::string title() const = 0;

  /**
   * Set the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   *
   */
  virtual bool setTitle(const std::string & title) = 0;

  /**
   * Get the IAnnotation associated with the Histogram.
   * @return The IAnnotation.
   *
   */
  /// virtual IAnnotation & annotation() = 0;

  /// virtual const IAnnotation & annotation() const = 0;

  /**
   * Get the Histogram's dimension.
   * @return The Histogram's dimension.
   *
   */ 
  virtual int dimension() const = 0;

  /**
   * Reset the Histogram; as if just created.
   * @return false If something goes wrong.
   *
   */
  virtual bool reset() = 0;

  /**
   * Get the number of in-range entries in the Histogram.
   * @return The number of in-range entries.
   *
   */ 
  virtual int entries() const = 0;

  /**
   *  See IManagedObject for a description.
   * @param className The name of the class to cast on.
   * @return The right pointer. Return 0 if failure.
   */ 
    virtual void * cast(const std::string & className) const = 0;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IBASEHISTOGRAM_H */
