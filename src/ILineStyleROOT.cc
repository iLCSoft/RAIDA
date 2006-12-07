#include <RAIDA/ILineStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> ILineStyleROOT::availableLineTypes() const 
{
  throw(NotYetImplementedException("availableLineTypes()","ILineStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string ILineStyleROOT::lineType() const 
{
  throw(NotYetImplementedException("lineType()","ILineStyle"));
  return std::string("");
}

int ILineStyleROOT::thickness() const 
{
  throw(NotYetImplementedException("thickness()","ILineStyle"));
  return 0;
}

bool ILineStyleROOT::setLineType(const std::string & newLineType) 
{
  throw(NotYetImplementedException("setLineType()","ILineStyle"));
  return true;
}

bool ILineStyleROOT::setThickness(int newThickness) 
{
  throw(NotYetImplementedException("setThickness()","ILineStyle"));
  return true;
}
