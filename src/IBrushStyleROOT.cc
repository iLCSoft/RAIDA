#include <RAIDA/IBrushStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>

using namespace AIDA ;

std::vector<std::string> IBrushStyleROOT::availableColors() const
{
  throw(NotYetImplementedException("availableColors()","IBrushStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string IBrushStyleROOT::color() const
{
  throw(NotYetImplementedException("color()","IBrushStyle"));
  return std::string("");
}

double IBrushStyleROOT::opacity() const 
{
  throw(NotYetImplementedException("opacity()","IBrushStyle"));
  return 0.;
}

bool IBrushStyleROOT::setColor(const std::string & newColor) 
{
  throw(NotYetImplementedException("setColor()","IBrushStyle"));
  return true;
}

bool IBrushStyleROOT::setOpacity(double newOpacity)
{
  throw(NotYetImplementedException("setOpacity()","IBrushStyle"));
  return true;
}
