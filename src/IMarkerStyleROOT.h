#include <RAIDA/IMarkerStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> IMarkerStyleROOT::availableShapes() const 
{
  throw(NotYetImplementedException("availableShapes()","IMarkerStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string IMarkerStyleROOT::shape() const
{
  throw(NotYetImplementedException("shape()","IMarkerStyle"));
  return std::string("");
}

bool IMarkerStyleROOT::setShape(const std::string & shape) 
{
  throw(NotYetImplementedException("setShape()","IMarkerStyle"));
  return true;
}
