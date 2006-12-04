// -*- C++ -*-
#ifndef AIDA_IMEASUREMENTROOT_H
#define AIDA_IMEASUREMENTROOT_H 1

#include <AIDA/IMeasurement.h>

namespace AIDA {

/**
 * Basic user-level interface class for holding a single "measurement"
 * with positive and negative errors (to allow for asymmetric errors).
 * "IMeasurement" = "value" + "errorPlus" - "errorMinus"
 *
 * @author T. Kraemer, DESY
 * @version $Id: IMeasurementROOT.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
 */
 
class IMeasurementROOT : public IMeasurement {

public: 
    /// Destructor.
    virtual ~IMeasurementROOT() { /* nop */; }

  /// Constructor
  IMeasurementROOT();
  IMeasurementROOT(double value,double error);
  IMeasurementROOT(double value,double errorPlus,double errorMinus);

    /**
     * Get the value of the IMeasurement.
     * @return The value of the IMeasurement.
     *
     */
    virtual double value() const ;

    /**
     * Get the plus error of the IMeasurement.
     * @return The plus error.
     *
     */
    virtual double errorPlus() const ;

    /**
     * Get the minus error of the IMeasurement.
     * @return The minus error.
     *
     */
    virtual double errorMinus() const ;

    /**
     * Set the value of the IMeasurement.
     * @param value The new value of the IMeasurement.
     * @return false If the value cannot be set.
     *
     */
    virtual bool setValue(double value) ;

    /**
     * Set the plus error of the IMeasurement.
     * @param value The new plus error of the IMeasurement.
     * @return false If the error cannot be set or it is negative.
     *
     */
    virtual bool setErrorPlus(double errorPlus) ;

    /**
     * Set the minus error of the IMeasurement.
     * @param value The new minus error of the IMeasurement.
     * @return false If the error cannot be set or it is negative.
     *
     */
    virtual bool setErrorMinus(double errorMinus) ;

    virtual bool setErrorPlusMinus(double error);

    virtual bool setErrorPlusMinus(double errorPlus,double errorMinus);

private:


}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IMEASUREMENTROOT_H */
