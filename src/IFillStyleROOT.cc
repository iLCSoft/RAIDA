#include <RAIDA/IFillStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> IFillStyleROOT::availablePatterns() const
{
  throw(NotYetImplementedException("availablePatterns()","IFillStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string IFillStyleROOT::pattern() const 
{
  throw(NotYetImplementedException("pattern()","IFillStyle"));
  return std::string("");
}

bool IFillStyleROOT::setPattern(const std::string & pattern) 
{
  throw(NotYetImplementedException("setPattern()","IFillStyle"));
  return true;
}
