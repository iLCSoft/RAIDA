// -*- C++ -*-
#include <RAIDA/IFitFactoryROOT.h>
#include <RAIDA/IFitDataROOT.h>
#include <RAIDA/IFitterROOT.h>
#include <RAIDA/NotYetImplementedException.h>

#include <string>

using namespace AIDA ;

IFitData * IFitFactoryROOT::createFitData() 
{
  throw(NotYetImplementedException("createFitData()","IFitFactory"));
  IFitData *x = new IFitDataROOT;
  return x;
}

IFitter * IFitFactoryROOT::createFitter(const std::string & fitterType, 
					const std::string & engineType, 
					const std::string & options) 
{
  throw(NotYetImplementedException("createFitter()","IFitFactory"));
  IFitter *x = new IFitterROOT;
  return x;
}
