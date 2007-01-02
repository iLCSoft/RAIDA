// -*- C++ -*-
#ifndef AIDA_IFUNCTIONROOT_H
#define AIDA_IFUNCTIONROOT_H 1

#include <AIDA/IFunction.h>
#include <string>
#include <vector>

namespace AIDA {

class IAnnotation;

/** @interface IFunction
 *
 * Principal user-level function interface. Function is a self
 * contained object, which remembers the current value of its parameters
 * which are simple doubles. IFunction may be directly plotted or fitted.
 *
 * The standard convention of referring to variables by name:
 * "x[0]" corresponds to variable number 0 etc.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFunctionROOT.h,v 1.2 2007-01-02 16:20:45 tkraemer Exp $
 */
 
class IFunctionROOT : public IFunction {

public: 
  /// Destructor.
  virtual ~IFunctionROOT() { /* nop */; }

  IFunctionROOT() { /* nop */; }

  /**
   * Get the Function's title.
   * @return The Function's title.
   *
   */
  virtual std::string title() const ;

  /**
   * Set	 the histogram title.
   * @param title The title.
   * @return false If title cannot be changed.
   *
   */
  virtual bool setTitle(const std::string & title) ;

  /**
   * Scalar value of the function.
   */
  virtual double value(const std::vector<double>  & x) const ;

  /**
   * Dimensionality of the domain space.
   */
  virtual int dimension() const ;

  /**
   * Compare if functions are the same.
   * PENDING: define exactly what it means ;)
   */
  virtual bool isEqual(const IFunction & f) const ;

  /**
   * Gradient of the function.
   * The result is valid only if providesGradient()==true.
   * Otherwise the result is some default (empty) vector.
   */
  virtual const std::vector<double>  & gradient(const std::vector<double>  & x) const ;

  /**
   * Determine whether function is able to compute gradient.
   */
  virtual bool providesGradient() const ;

  /**
   * Get the symbolic name of i-th variable.
   */
  virtual std::string variableName(int i) const ;

  /**
   * Get all the names in a vector.
   */
  virtual std::vector<std::string>  variableNames() const ;

  /**
   * Set new vector of parameters.
   */
  virtual bool setParameters(const std::vector<double>  & params) ;

  /**
   * Retrieve current vector of parameters.
   */
  virtual const std::vector<double>  & parameters() const ;

  /**
   * Number of parameters.
   */
  virtual int numberOfParameters() const ;

  /**
   * Names of paramaters.
   * Names should be unique. Case-insensitive for comparison.
   * Case-sensitive for storage and output.
   * All or several names may be left blank "" if the implementation
   * does not want to provide them.
   */
  virtual std::vector<std::string>  parameterNames() const ;

  /**
   * Set parameter's value by name.
   * @param name The name of the parameter.
   * @param x    The new value of the parameter.
   * @return false If name does not correspond to a parameter.
   *
   */
  virtual bool setParameter(const std::string & name, double x) ;

  virtual double parameter(const std::string & name) const ;

  /**
   * Return -1 if parameter not found (name undefined).
   * Leave it because there are use cases - some users prefer to use numbers.
   */
  virtual int indexOfParameter(const std::string & name) const ;

  virtual IAnnotation & annotation() ;

  virtual const IAnnotation & annotation() const ;

  /**
   * String describing the metatype and implementation of the function.
   *
   * Generic format of the string:
   *
   * codelet:TYPE:LOCATION
   *
   * TYPE part contains only a 'typename' string
   * which is a metatype identifier (used in plugins and catalogues)
   *
   * LOCATION may be: 'file', 'verbatim', or 'catalogue'
   *
   * Detailed description:
   *
   * codelet:typename - no location specified (using 'catalogue')
   *
   * codelet:typename:file:/filename.cpp    -  a c++ source file
   * codelet:typename:file:/filename.py     -  a python source file
   * codelet:typename:file:/filename.so     -  a shared library
   *
   * codelet:typename:catalogue        - entry in a catalogue repository
   *
   * codelet:typename:verbatim:cpp \n  - c++ source file included verbatim
   *                                     after \n
   *
   * codelet:typename:verbatim:py  \n  - python source file included
   *                                     verbatim aftern \n
   *
   *
   * Comments:
   *
   * file:/filename is a relative path to $AIDA_FUNCTION_DEFAULT_DIR
   * file://filename is an absolute path
   *
   * Examples:
   *
   * codelet:G:catalogue
   * codelet:userSinus:verbatim:cpp \n { return sin(x); }
   */
  virtual std::string codeletString() const ;

  /**
   *  See IManagedObject for a description.
   * @param className The name of the class to cast on.
   * @return The right pointer. Return 0 if failure.
   */ 
  virtual void * cast(const std::string & className) const ;

    /** @link aggregation */
    /*#  IAnnotation lnkIAnnotation; */
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFUNCTIONROOT_H */
