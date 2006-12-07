#include <RAIDA/ILineStyleROOT.h>
#include <string>
#include <vector>


using namespace AIDA ;

std::vector<std::string> ILineStyleROOT::availableLineTypes() const 
{
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

std::string ILineStyleROOT::lineType() const 
{
  return std::string("");
}

int ILineStyleROOT::thickness() const 
{
  return 0;
}

bool ILineStyleROOT::setLineType(const std::string & newLineType) 
{
  return true;
}

bool ILineStyleROOT::setThickness(int newThickness) 
{
  return true;
}
