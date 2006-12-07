#include <RAIDA/IMarkerStyleROOT.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> IMarkerStyleROOT::availableShapes() const 
{
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string IMarkerStyleROOT::shape() const
{
  return std::string("");
}

bool IMarkerStyleROOT::setShape(const std::string & shape) 
{
  return true;
}
