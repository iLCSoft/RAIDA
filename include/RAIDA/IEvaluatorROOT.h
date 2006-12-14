// -*- C++ -*-
#ifndef AIDA_IEVALUATORROOT_H
#define AIDA_IEVALUATORROOT_H 1

#include <AIDA/IEvaluator.h>
#include <string>

namespace AIDA {

class ITuple;

/**
 * User's level interface of an IEvaluator.
 *
 * @author T. Kraemer, DESY
 * @version $Id: IEvaluatorROOT.h,v 1.1 2006-12-14 09:41:42 tkraemer Exp $
 */
 
class IEvaluatorROOT : public IEvaluator {

public: 
    /// Destructor.
    virtual ~IEvaluatorROOT() { /* nop */; }

  IEvaluatorROOT() { /* nop */; }

  /**
   * Initialize the IEvaluator and associate it to an ITuple.
   * @param tuple The ITuple to which the IEvaluator is sssociated.
   * @return false If the IEvaluator and 
   *              the ITuple are not compatible.
   */ 
  virtual bool initialize(ITuple & tuple) ;

  /**
   * Evaluate the IEvaluator from the data in the 
   * current row of the ITuple it is associated to.
   * @return The current value of the Evaluator.
   */ 
  virtual double evaluateDouble() const ;

   /**
    * Get the expression that defined the IEvaluator.
    * @return The expression.
    */
  virtual std::string expression() const ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IEVALUATORROOT_H */
