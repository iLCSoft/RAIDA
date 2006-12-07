#include <RAIDA/IFillStyleROOT.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> IFillStyleROOT::availablePatterns() const
{
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string IFillStyleROOT::pattern() const 
{
  return std::string("");
}

bool IFillStyleROOT::setPattern(const std::string & pattern) 
{
  return true;
}
