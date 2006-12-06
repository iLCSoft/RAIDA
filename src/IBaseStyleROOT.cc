#include <RAIDA/IBaseStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>


using namespace AIDA;

void IBaseStyleROOT::reset() 
{
  throw(NotYetImplementedException("reset()","IBaseStyle"));
}

bool IBaseStyleROOT::setParameter(const std::string & paramName,
				  const std::string & options) 
{
  throw(NotYetImplementedException("setParameter()","IBaseStyle"));
  return true;
}

std::string IBaseStyleROOT::parameterValue(const std::string & parameter) const
{
  throw(NotYetImplementedException("parameterValue()","IBaseStyle"));
  return std::string("");
}

std::vector<std::string>  IBaseStyleROOT::availableParameters() const 
{
  throw(NotYetImplementedException("availableParameters()","IBaseStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::vector<std::string> IBaseStyleROOT::availableParameterOptions(const std::string & paramName) const 
{
  throw(NotYetImplementedException("availableParameterOptions(","IBaseStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}
