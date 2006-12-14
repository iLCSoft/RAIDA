// -*- C++ -*-
#ifndef AIDA_ITUPLEENTRYROOT_R_H
#define AIDA_ITUPLEENTRYROOT_H 1
#include <AIDA/ITupleEntry.h>

namespace AIDA {

/**
 * Style for the part of the scene representing the data
 * (then histograms, functions, data point sets).
 *
 * @author T. Kraemer, DESY
 * @version $Id: ITupleEntryROOT.h,v 1.1 2006-12-14 10:29:40 tkraemer Exp $
 */

class ITupleEntryROOT : public ITupleEntry {

public: 
    /// Destructor.
  virtual ~ITupleEntryROOT() { /* nop */; }
  ITupleEntryROOT() { /* nop */; }
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITUPLEENTRYROOT_H */
