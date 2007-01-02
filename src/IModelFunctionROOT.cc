// -*- C++ -*-
#include <RAIDA/IModelFunctionROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <vector>
#include <RAIDA/IRangeSetROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <AIDA/IModelFunction.h>

using namespace AIDA ;

bool IModelFunctionROOT::providesNormalization() const 
{
  throw(NotYetImplementedException("providesNormalization()","IModelFunction"));
  return true;
}

void IModelFunctionROOT::normalize(bool on) 
{
  throw(NotYetImplementedException("normalize()","IModelFunction"));
}

bool IModelFunctionROOT::isNormalized() const 
{
  throw(NotYetImplementedException("isNormalized()","IModelFunction"));
  return true;
}

const std::vector<double> & IModelFunctionROOT::parameterGradient(const std::vector<double>  & x) const 
{
  throw(NotYetImplementedException("parameterGradient()","IModelFunction"));
  std::vector<double> y;
  return y;
}

bool IModelFunctionROOT::providesParameterGradient() const 
{
  throw(NotYetImplementedException("providesParameterGradient()","IModelFunction"));
  return true;
}

IRangeSet & IModelFunctionROOT::normalizationRange(int iAxis) 
{
  throw(NotYetImplementedException("normalizationRange()","IModelFunction"));
  IRangeSet *x = new IRangeSetROOT;
  return *x;
}

void IModelFunctionROOT::includeNormalizationAll() 
{
  throw(NotYetImplementedException("includeNormalizationAll()","IModelFunction"));
}

void IModelFunctionROOT::excludeNormalizationAll() 
{
  throw(NotYetImplementedException("excludeNormalizationAll()","IModelFunction"));
}
