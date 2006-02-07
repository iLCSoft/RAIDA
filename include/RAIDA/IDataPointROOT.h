// -*- C++ -*-
#ifndef AIDA_IDATAPOINTROOT_H
#define AIDA_IDATAPOINTROOT_H 1

#include <AIDA/IDataPoint.h>

namespace AIDA {

class IMeasurement;

/**
 * Basic user-level interface class for holding and managing
 * a single set of "measurements".
 * 
 * @author The AIDA team (http://aida.freehep.org/)
 *
 */

class IDataPointROOT : public IDataPoint {

public: 

  /// Constructor
  IDataPointROOT();
  IDataPointROOT(int dimension);

    /// Destructor.
    virtual ~IDataPointROOT() { /* nop */; }

    /**
     * Get the dimension of the IDataPoint, i.e. the number
     * of coordinates the point has.
     * @return The dimension.
     *
     */
    virtual int dimension() const ;

    /**
     * Get the IMeasurement for a given coordinate.
     * @param coord The coordinate.
     * @return      The corresponding IMeasurement.
     *
     */
    virtual IMeasurement * coordinate(int coord) ;

    virtual const IMeasurement * coordinate(int coord) const ;

private:


}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IDATAPOINT_H */
