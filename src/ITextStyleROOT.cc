#include <RAIDA/ITextStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>

using namespace AIDA ;

std::vector<std::string> ITextStyleROOT::availableFonts() const 
{
  throw(NotYetImplementedException("availableFonts()","ITextStyle"));
  std::vector<std::string> x;
  std::string s;
  x.push_back(s);
  return x;
}

double ITextStyleROOT::fontSize() const
{
  throw(NotYetImplementedException("fontSize()","ITextStyle"));
  return 0.;
}

bool ITextStyleROOT::setFontSize(double size)
{
  throw(NotYetImplementedException("setFontSize()","ITextStyle"));
  return true;
}

std::string ITextStyleROOT::font() const 
{
  throw(NotYetImplementedException("font()","ITextStyle"));
  return std::string("");
}

bool ITextStyleROOT::setFont(const std::string & font) 
{
  throw(NotYetImplementedException("setFont()","ITextStyle"));
  return true;
}

bool ITextStyleROOT::isBold() const 
{
  throw(NotYetImplementedException("isBold()","ITextStyle"));
  return true;
}

bool ITextStyleROOT::isItalic() const 
{
  throw(NotYetImplementedException("isItalic()","ITextStyle"));
  return true;
}

bool ITextStyleROOT::isUnderlined() const 
{
  throw(NotYetImplementedException("isUnderlined()","ITextStyle"));
  return true;
}

bool ITextStyleROOT::setBold(bool bold)
{
  throw(NotYetImplementedException("setBold()","ITextStyle"));
  return true;
} 

bool ITextStyleROOT::setItalic(bool italic) 
{
  throw(NotYetImplementedException("setItalic()","ITextStyle"));
  return true;
}

bool ITextStyleROOT::setUnderlined(bool underlined) 
{
  throw(NotYetImplementedException("setUnderlined()","ITextStyle"));
  return true;
}
