#ifndef AIDA_AIDAHistogramsInROOT_H
#define AIDA_AIDAHistogramsInROOT_H 1

namespace AIDA {
  // This variable decides, if the additional histograms are written to the 
  // ROOT output file:
  // AIDAHistogramsInROOT = false : the additional histograms are not written 
  // AIDAHistogramsInROOT = true  : the additional histograms are written 
  // Author: T. Kraemer, DESY
  // version: $Id: AIDAHistogramsInROOT.h,v 1.2 2006-12-04 17:24:06 tkraemer Exp $

  extern bool AIDAHistogramsInROOT;
} // namespace AIDA

#endif /* ifndef AIDA_AIDAHistogramsInROOT_H */
