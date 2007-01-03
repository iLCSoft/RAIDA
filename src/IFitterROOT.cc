// -*- C++ -*-
#include <RAIDA/IFitterROOT.h>
#include <RAIDA/IDataPointSetROOT.h>
#include <RAIDA/IFitDataROOT.h>
#include <RAIDA/IFitParameterSettingsROOT.h>
#include <RAIDA/IFitResultROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/ICloud1DROOT.h>
#include <RAIDA/ICloud2DROOT.h>
#include <RAIDA/ICloud3DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/IProfile1DROOT.h>
#include <RAIDA/IProfile2DROOT.h>
#include <RAIDA/NotYetImplementedException.h>

#include <string>
#include <vector>

using namespace AIDA ;

IFitResult * IFitterROOT::fit(IFitData & fitData, IFunction & func) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IBaseHistogram & hist, IFunction & func) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IBaseHistogram & hist, 
			      const std::string & model) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IBaseHistogram & hist, 
			      const std::string & model, 
			      const std::vector<double>  & initialParameters) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IDataPointSet & dataPointSet, 
			      IFunction & f) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IDataPointSet & dataPointSet, 
			      const std::string & model) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IDataPointSet & dataPointSet, 
			      const std::string & model, 
			      const std::vector<double>  & initialParameters) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IFitData & d, const std::string & model) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

IFitResult * IFitterROOT::fit(IFitData & d, 
			      const std::string & model, 
			      const std::vector<double>  & initialParameters) 
{
  throw(NotYetImplementedException("fit()","IFitter"));
  IFitResult *x = new IFitResultROOT;
  return x;
}

bool IFitterROOT::setEngine(const std::string & name) 
{
  throw(NotYetImplementedException("setEngine()","IFitter"));
  return true ;
}

std::string IFitterROOT::engineName() 
{
  throw(NotYetImplementedException("engineName()","IFitter"));
  return std::string("");
}

IFitParameterSettings & IFitterROOT::fitParameterSettings(const std::string & name) 
{
  throw(NotYetImplementedException("fitParameterSettings()","IFitter"));
  IFitParameterSettings *x = new IFitParameterSettingsROOT;
  return *x;
}

std::vector<std::string>  IFitterROOT::listParameterSettings() 
{
  throw(NotYetImplementedException("listParameterSettings()","IFitter"));
  std::vector<std::string> x;
  return x;
}

void IFitterROOT::resetParameterSettings() 
{
  throw(NotYetImplementedException("resetParameterSettings()","IFitter"));
}

bool IFitterROOT::setConstraint(const std::string & expr) 
{
  throw(NotYetImplementedException("setConstraint()","IFitter"));
  return true;
}

std::vector<std::string>  IFitterROOT::constraints() 
{
  throw(NotYetImplementedException("constraints()","IFitter"));
  std::vector<std::string> x;
  return x;
}

void IFitterROOT::resetConstraints() 
{
  throw(NotYetImplementedException("resetConstraints()","IFitter"));
}

bool IFitterROOT::setFitMethod(const std::string & name) 
{
  throw(NotYetImplementedException("setFitMethod()","IFitter"));
  return true ;
}

std::string IFitterROOT::fitMethodName() 
{
  throw(NotYetImplementedException("fitMethodName()","IFitter"));
  return std::string("");
}

IDataPointSet * IFitterROOT::createScan1D(IFitData & d, 
					  IFunction & f, 
					  const std::string & par, 
					  int npts, double pmin, double pmax) 
{
  throw(NotYetImplementedException("createScan1D()","IFitter"));
  IDataPointSet *x = new IDataPointSetROOT;
  return x;
}

IDataPointSet * IFitterROOT::createContour(IFitData & d, 
					   IFitResult & r, 
					   const std::string & par1, 
					   const std::string & par2, 
					   int npts, double up) 
{
  throw(NotYetImplementedException("createContour()","IFitter"));
  IDataPointSet *x = new IDataPointSetROOT;
  return x;
}

void IFitterROOT::setUseFunctionGradient(bool useGrad) 
{
  throw(NotYetImplementedException("setUseFunctionGradient()","IFitter"));
}

bool IFitterROOT::useFunctionGradient() 
{
  throw(NotYetImplementedException("useFunctionGradient()","IFitter"));
  return true ;
}
