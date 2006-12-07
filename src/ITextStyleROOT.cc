#include <RAIDA/ITextStyleROOT.h>
#include <string>
#include <vector>

using namespace AIDA ;

std::vector<std::string> ITextStyleROOT::availableFonts() const 
{
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

double ITextStyleROOT::fontSize() const
{
  return 0.;
}

bool ITextStyleROOT::setFontSize(double size)
{
  return true;
}

std::string ITextStyleROOT::font() const 
{
  return std::string("");
}

bool ITextStyleROOT::setFont(const std::string & font) 
{
  return true;
}

bool ITextStyleROOT::isBold() const 
{
  return true;
}

bool ITextStyleROOT::isItalic() const 
{
  return true;
}

bool ITextStyleROOT::isUnderlined() const 
{
  return true;
}

bool ITextStyleROOT::setBold(bool bold)
{
  return true;
} 

bool ITextStyleROOT::setItalic(bool italic) 
{
  return true;
}

bool ITextStyleROOT::setUnderlined(bool underlined) 
{
  return true;
}
