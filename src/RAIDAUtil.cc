// -*- C++ -*-
#include <RAIDA/RAIDAUtil.h>
#include <AIDA/IAxis.h>
#include <iostream>

using namespace std ;
using namespace AIDA ;

int RAIDAUtil::binIndexAIDA2ROOT(int index, int nBins)
{
  // Bin numbering transformation from AIDA to ROOT conventions
  int indexROOT = 0;
  if (index <= IAxis::UNDERFLOW_BIN)
    indexROOT = 0;
  else if (index >= nBins )
    indexROOT = nBins+1;
  else if (index == IAxis::OVERFLOW_BIN)
    indexROOT = nBins+1; 
  else
    indexROOT = index + 1;

  return indexROOT;
}

int RAIDAUtil::binIndexROOT2AIDA(int index, int nBins)
{
  // Bin numbering transformation from ROOT to AIDA conventions
  int indexAIDA = 0;
  if (index <= 0)
    indexAIDA = IAxis::UNDERFLOW_BIN;
  else if (index >= nBins+1)
    indexAIDA = IAxis::OVERFLOW_BIN;
  else 
    indexAIDA = index - 1;

  return indexAIDA;
}
