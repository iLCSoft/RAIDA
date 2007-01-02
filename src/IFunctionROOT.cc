#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <RAIDA/IAnnotationROOT.h>
#include <string>
#include <vector>

using namespace AIDA ;

std::string IFunctionROOT::title() const 
{
  throw(NotYetImplementedException("title()","IFunction"));
  return std::string("");
}

bool IFunctionROOT::setTitle(const std::string & title)
{
  throw(NotYetImplementedException("setTitle()","IFunction"));
  return true;
}

double IFunctionROOT::value(const std::vector<double>  & x) const 
{
  throw(NotYetImplementedException("value()","IFunction"));
  return 0.;
}

int IFunctionROOT::dimension() const 
{
  throw(NotYetImplementedException("dimension()","IFunction"));
  return 0;
}

bool IFunctionROOT::isEqual(const IFunction & f) const 
{
  throw(NotYetImplementedException("isEqual()","IFunction"));
  return true;
}

const std::vector<double>  & IFunctionROOT::gradient(const std::vector<double>  & x) const 
{
  throw(NotYetImplementedException("gradient()","IFunction"));
  std::vector<double> y;
  return y;
}

bool IFunctionROOT::providesGradient() const 
{
  throw(NotYetImplementedException("providesGradient()","IFunction"));
  return true;
}

std::string IFunctionROOT::variableName(int i) const 
{
  throw(NotYetImplementedException("variableName()","IFunction"));
  return std::string("");
}

std::vector<std::string>  IFunctionROOT::variableNames() const 
{
  throw(NotYetImplementedException("variableNames()","IFunction"));
  std::vector<std::string> x;
  return x;
}

bool IFunctionROOT::setParameters(const std::vector<double>  & params) 
{
  throw(NotYetImplementedException("setParameters()","IFunction"));
  return true;
}

const std::vector<double>  & IFunctionROOT::parameters() const 
{
  throw(NotYetImplementedException("parameters()","IFunction"));
  std::vector<double> x;
  return x;
}

int IFunctionROOT::numberOfParameters() const 
{
  throw(NotYetImplementedException("numberOfParameters()","IFunction"));
  return 0;
}

std::vector<std::string>  IFunctionROOT::parameterNames() const 
{
  throw(NotYetImplementedException("parameterNames()","IFunction"));
  std::vector<std::string> x;
  return x;
}

bool IFunctionROOT::setParameter(const std::string & name, double x) 
{
  throw(NotYetImplementedException("setParameter()","IFunction"));
  return true;
}

double IFunctionROOT::parameter(const std::string & name) const 
{
  throw(NotYetImplementedException("parameter()","IFunction"));
  return 0.;
}

int IFunctionROOT::indexOfParameter(const std::string & name) const 
{
  throw(NotYetImplementedException("indexOfParameter()","IFunction"));
  return 0;
}

IAnnotation & IFunctionROOT::annotation() 
{
  throw(NotYetImplementedException("annotation()","IFunction"));
  IAnnotation *x = new IAnnotationROOT ;
  return *x;
}

const IAnnotation & IFunctionROOT::annotation() const 
{
  throw(NotYetImplementedException("annotation()","IFunction"));
  IAnnotation *x = new IAnnotationROOT ;
  return *x;
}

std::string IFunctionROOT::codeletString() const 
{
  throw(NotYetImplementedException("codeletString()","IFunction"));
  return std::string("");
}

void * IFunctionROOT::cast(const std::string & className) const 
{
  throw(NotYetImplementedException("cast()","IFunction"));
  return 0;
}
