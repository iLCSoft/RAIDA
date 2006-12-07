#include <RAIDA/IAxisStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>


using namespace AIDA ;

ILineStyle & IAxisStyleROOT::lineStyle()
{
  throw(NotYetImplementedException("lineStyle()","IAxisStyle"));
}

ITextStyle & IAxisStyleROOT::tickLabelStyle()
{
  throw(NotYetImplementedException("tickLabelStyle()","IAxisStyle"));
}

ITextStyle & IAxisStyleROOT::labelStyle()
{
  throw(NotYetImplementedException("labelStyle()","IAxisStyle"));
}

bool IAxisStyleROOT::setlineStyle(const ILineStyle & lineStyle)
{
  throw(NotYetImplementedException("setlineStyle()","IAxisStyle"));
}

bool IAxisStyleROOT::setTickLabelStyle(const ITextStyle & tickLabelStyle) 
{
  throw(NotYetImplementedException("setTickLabelStyle()","IAxisStyle"));
}

bool IAxisStyleROOT::setLabelStyle(const ITextStyle & labelStyle) 
{
  throw(NotYetImplementedException("setLabelStyle()","IAxisStyle"));
}

void IAxisStyleROOT::setLabel(const std::string & label) 
{
  throw(NotYetImplementedException("setLabel()","IAxisStyle"));
}
