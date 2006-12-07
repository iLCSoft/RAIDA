#include <RAIDA/IInfoStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

ITextStyle & IInfoStyleROOT::textStyle()
{
  throw(NotYetImplementedException("textStyle()","IInfoStyle"));
}

bool IInfoStyleROOT::setTextStyle(const ITextStyle & textStyle)
{
  throw(NotYetImplementedException("setTextStyle()","IInfoStyle"));
  return true;
}
