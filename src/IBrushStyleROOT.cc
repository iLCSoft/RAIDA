#include <RAIDA/IBrushStyleROOT.h>
#include <string>
#include <vector>

using namespace AIDA ;

std::vector<std::string> IBrushStyleROOT::availableColors() const
{

}

std::string IBrushStyleROOT::color() const
{
  return std::string("");
}

double IBrushStyleROOT::opacity() const 
{
  return 0.;
}

bool IBrushStyleROOT::setColor(const std::string & newColor) 
{
  return true;
}

bool IBrushStyleROOT::setOpacity(double newOpacity)
{
  return true;
}
