// -*- C++ -*-
#ifndef AIDA_RAIDAUtil_H
#define AIDA_RAIDAUtil_H 1

#include <iostream>

/**
 * Class holding utility functions for RAIDA.  
 * @author T. Kraemer, DESY
 * @version $Id: RAIDAUtil.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $
 */


using namespace std;

namespace AIDA {
namespace RAIDAUtil {
  /// converts binindex from AIDA to ROOT conventions
  int binIndexAIDA2ROOT(int index, int nBins);

  /// converts binindex from AIDA to ROOT conventions
  int binIndexROOT2AIDA(int index, int nBins);

} // namespace RAIDAUtil
} // namespace AIDA
#endif /* ifndef AIDA_RAIDAUtil_H */
