#include <RAIDA/IPlotterLayoutROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>

using namespace AIDA ;

void IPlotterLayoutROOT::reset()
{
  throw(NotYetImplementedException("reset()","IPlotterLayout"));
}

bool IPlotterLayoutROOT::setParameter(const std::string & paramName, 
				      double paramValue) 
{
  throw(NotYetImplementedException("setParameter()","IPlotterLayout"));
  return true;
}

double IPlotterLayoutROOT::parameterValue(const std::string & paramName) 
{
  throw(NotYetImplementedException("parameterValue()","IPlotterLayout"));
  return 0.;
}

std::vector<std::string> IPlotterLayoutROOT::availableParameters() const 
{
  throw(NotYetImplementedException("availableParameters()","IPlotterLayout"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}
