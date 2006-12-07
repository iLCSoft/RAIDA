#include <RAIDA/ITitleStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

ITextStyle & ITitleStyleROOT::textStyle() 
{
  throw(NotYetImplementedException("textStyle()","ITitleStyle"));
}

bool ITitleStyleROOT::setTextStyle(const ITextStyle & textStyle)
{
  throw(NotYetImplementedException("setTextStyle(","ITitleStyle"));
  return true;
}
