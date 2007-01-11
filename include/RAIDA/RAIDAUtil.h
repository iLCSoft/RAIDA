// -*- C++ -*-
#ifndef AIDA_RAIDAUtil_H
#define AIDA_RAIDAUtil_H 1

#include <iostream>
#include <vector>
/**
 * Class holding utility functions for RAIDA.  
 * @author T. Kraemer, DESY
 * @version $Id: RAIDAUtil.h,v 1.3 2007-01-11 08:54:34 tkraemer Exp $
 */


namespace AIDA {
namespace RAIDAUtil {
  /// converts binindex from AIDA to ROOT conventions
  int binIndexAIDA2ROOT(int index, int nBins);

  /// converts binindex from AIDA to ROOT conventions
  int binIndexROOT2AIDA(int index, int nBins);

  /// Checks if a std::vector<double> is ordered according to the 
  /// magnitude of the values:
  /// x[i] < x[i+1] for all i \in {0,1,2,3...}  or
  /// x[i] > x[i+1] for all i \in {0,1,2,3...}  
  bool isOrdered(std::vector<double> x);

} // namespace RAIDAUtil
} // namespace AIDA
#endif /* ifndef AIDA_RAIDAUtil_H */
