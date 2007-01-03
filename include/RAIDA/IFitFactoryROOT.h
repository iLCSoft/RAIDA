// -*- C++ -*-
#ifndef AIDA_IFITFACTORYROOT_H
#define AIDA_IFITFACTORYROOT_H 1

#include <AIDA/IFitFactory.h>
#include <string>

namespace AIDA {

class IFitData;
class IFitter;

/** Dummy implementation of class  "IFitFactory".
 *
 * @author T. Kraemer, DESY
 * @version $Id: IFitFactoryROOT.h,v 1.1 2007-01-03 17:18:39 tkraemer Exp $
 */

class IFitFactoryROOT : public IFitFactory {

public: 
  /// Destructor.
  virtual ~IFitFactoryROOT() { /* nop */; }

  IFitFactoryROOT() { /* nop */; }

  virtual IFitData * createFitData() ;

  /**
   * Create a new IFitter.
   * @param fitterType The type of fitter. The supported types are:
   *                    - "CHI2" or "Chi2" or "ChiSquared" for chi squared fitter (this is the default),
   *                    - "ML" or "MaxLikelihood" for maximum likelihood fitter,
   *                    - "LS" or "LeastSquares" for Last Squares fitter.
   * @param engineType The type of optimization engine used by the fitter. The available types depend on the
   *                   specific implementation in use. The default is "" (the implementation specific default).
   * @param options    A string of options. The default is "".
   * @return           The IFitter.
   */
  virtual IFitter * createFitter(const std::string & fitterType = "Chi2", 
				 const std::string & engineType = "", 
				 const std::string & options = "") ;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_IFITFACTORYROOT_H */
