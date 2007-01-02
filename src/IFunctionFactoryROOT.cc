// -*- C++ -*-
#include <RAIDA/IFunctionFactoryROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/IFunctionCatalogROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>

using namespace AIDA ;

IFunction * IFunctionFactoryROOT::createFunctionByName(const std::string & path, 
						       const std::string & model)
{
  throw(NotYetImplementedException("createFunctionByName()","IFunctionFactory"));
  IFunction *x = new IFunctionROOT ;
  return x;
}

IFunction * IFunctionFactoryROOT::createFunctionFromScript(const std::string & name, 
							   int dim, 
							   const std::string & valexpr, 
							   const std::string & parameters,
							   const std::string & description,
							   const std::string & gradexpr) 
{
  throw(NotYetImplementedException("createFunctionFromScript()","IFunctionFactory"));
  IFunction *x = new IFunctionROOT ;
  return x;
}

IFunction * IFunctionFactoryROOT::cloneFunction(const std::string & path, IFunction & f) 
{
  throw(NotYetImplementedException("cloneFunction()","IFunctionFactory"));
  IFunction *x = new IFunctionROOT ;
  return x;
}

IFunctionCatalog * IFunctionFactoryROOT::catalog() 
{
  throw(NotYetImplementedException("catalog()","IFunctionFactory"));
  IFunctionCatalog *x = new IFunctionCatalogROOT ;
  return x;
}
