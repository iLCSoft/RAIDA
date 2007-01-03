// -*- C++ -*-
#include <RAIDA/IFitResultROOT.h>
#include <RAIDA/IFitParameterSettingsROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/NotYetImplementedException.h>

#include <string>
#include <vector>

using namespace AIDA ;

bool IFitResultROOT::isValid() 
{
  throw(NotYetImplementedException("isValid()","IFitResult"));
  return true;
}

int IFitResultROOT::fitStatus() 
{
  throw(NotYetImplementedException("fitStatus()","IFitResult"));
  return 0;
}

IFunction & IFitResultROOT::fittedFunction() 
{
  throw(NotYetImplementedException("fittedFunction()","IFitResult"));
  IFunction *x = new IFunctionROOT;
  return *x;
}

double IFitResultROOT::quality() 
{
  throw(NotYetImplementedException("quality()","IFitResult"));
  return 0.;
}

int IFitResultROOT::ndf() 
{
  throw(NotYetImplementedException("ndf()","IFitResult"));
  return 0;
}

double IFitResultROOT::covMatrixElement(int i, int j) 
{
  throw(NotYetImplementedException("covMatrixElement()","IFitResult"));
  return 0.;
}

std::string IFitResultROOT::fitMethodName() 
{
  throw(NotYetImplementedException("fitMethodName()","IFitResult"));
  return std::string("");
}

std::string IFitResultROOT::engineName() 
{
  throw(NotYetImplementedException("engineName()","IFitResult"));
  return std::string("");
}

std::string IFitResultROOT::dataDescription() 
{
  throw(NotYetImplementedException("dataDescription()","IFitResult"));
  return std::string("");
}

std::vector<std::string> IFitResultROOT::constraints() 
{
  throw(NotYetImplementedException("constraints()","IFitResult"));
  std::vector<std::string> x;
  return x;
}

IFitParameterSettings * IFitResultROOT::fitParameterSettings(const std::string & name) 
{
  throw(NotYetImplementedException("fitParameterSettings()","IFitResult"));
  IFitParameterSettings *x = new IFitParameterSettingsROOT; 
  return x;
}

const std::vector<double> & IFitResultROOT::fittedParameters() const 
{
  throw(NotYetImplementedException("fittedParameters()","IFitResult"));
  std::vector<double> *x = new std::vector<double>;
  return *x;
}

std::vector<std::string> IFitResultROOT::fittedParameterNames() const 
{
  throw(NotYetImplementedException("fittedParameterNames()","IFitResult"));
  std::vector<std::string> x;
  return x;
}

double IFitResultROOT::fittedParameter(const std::string & name) 
{
  throw(NotYetImplementedException("fittedParameter()","IFitResult"));
  return 0.;
}

const std::vector<double> & IFitResultROOT::errors() const 
{
  throw(NotYetImplementedException("errors()","IFitResult"));
  std::vector<double> *x = new std::vector<double>;
  return *x;
}

const std::vector<double>  & IFitResultROOT::errorsPlus() const 
{
  throw(NotYetImplementedException("errorsPlus()","IFitResult"));
  std::vector<double> *x = new std::vector<double>;
  return *x;
}

const std::vector<double>  & IFitResultROOT::errorsMinus() const 
{
  throw(NotYetImplementedException("errorsMinus()","IFitResult"));
  std::vector<double> *x = new std::vector<double>;
  return *x;
}
