// -*- C++ -*-
#include <RAIDA/IFitParameterSettingsROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>

using namespace AIDA ;

std::string IFitParameterSettingsROOT::name() const 
{
  throw(NotYetImplementedException("name()","IFitParameterSettings"));
  return std::string("");
}

double IFitParameterSettingsROOT::stepSize() const 
{
  throw(NotYetImplementedException("stepSize()","IFitParameterSettings"));
  return 0.;
}

double IFitParameterSettingsROOT::upperBound() const 
{
  throw(NotYetImplementedException("upperBound()","IFitParameterSettings"));
  return 0.;
}

double IFitParameterSettingsROOT::lowerBound() const 
{
  throw(NotYetImplementedException("lowerBound()","IFitParameterSettings"));
  return 0.;
}

bool IFitParameterSettingsROOT::isBound() const 
{
  throw(NotYetImplementedException("isBound()","IFitParameterSettings"));
  return true;
}

bool IFitParameterSettingsROOT::isFixed() const 
{
  throw(NotYetImplementedException("isFixed()","IFitParameterSettings"));
  return true;
}

void IFitParameterSettingsROOT::setStepSize(double step) 
{
  throw(NotYetImplementedException("setStepSize()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::setBounds(double lo, double up) 
{
  throw(NotYetImplementedException("setBounds()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::removeBounds() 
{
  throw(NotYetImplementedException("removeBounds()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::setFixed(bool isFixed) 
{
  throw(NotYetImplementedException("setFixed()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::setLowerBound(double lowerBound) 
{
  throw(NotYetImplementedException("setLowerBound()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::setUpperBound(double upperBound) 
{
  throw(NotYetImplementedException("setUpperBound()","IFitParameterSettings"));
}

void IFitParameterSettingsROOT::reset() 
{
  throw(NotYetImplementedException("reset()","IFitParameterSettings"));
}
