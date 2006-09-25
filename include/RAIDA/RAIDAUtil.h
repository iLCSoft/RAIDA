// -*- C++ -*-
#ifndef AIDA_RAIDAUtil_H
#define AIDA_RAIDAUtil_H 1

#include <iostream>

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
