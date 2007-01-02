// -*- C++ -*-
#include <RAIDA/IFunctionCatalogROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>

using namespace AIDA ;

bool IFunctionCatalogROOT::add(std::string nameId, IFunction * f) 
{
  throw(NotYetImplementedException("add()","IFunctionCatalogROOT"));
  return true;
}

bool IFunctionCatalogROOT::add(std::string nameId, const std::string & codelet)
{
  throw(NotYetImplementedException("add()","IFunctionCatalogROOT"));
  return true;
}

std::vector<std::string> IFunctionCatalogROOT::list() 
{
  throw(NotYetImplementedException("list()","IFunctionCatalogROOT"));
  std::vector<std::string> x;
  return x;
}

void IFunctionCatalogROOT::remove(const std::string & nameId) 
{
  throw(NotYetImplementedException("remove()","IFunctionCatalogROOT"));
}

bool IFunctionCatalogROOT::storeAll(const std::string & nameOnDisk) 
{
  throw(NotYetImplementedException("storeAll()","IFunctionCatalogROOT"));
  return true;
}

bool IFunctionCatalogROOT::loadAll(const std::string & nameOnDisk) 
{
  throw(NotYetImplementedException("loadAll()","IFunctionCatalogROOT"));
  return true;
}
