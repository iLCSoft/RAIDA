#include <RAIDA/IDataStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

ILineStyle & IDataStyleROOT::lineStyle()
{
  throw(NotYetImplementedException("lineStyle()","IDataStyle"));
}

IMarkerStyle & IDataStyleROOT::markerStyle() 
{
  throw(NotYetImplementedException("markerStyle()","IDataStyle"));
}

IFillStyle & IDataStyleROOT::fillStyle() 
{
  throw(NotYetImplementedException("fillStyle()","IDataStyle"));
}

bool IDataStyleROOT::setLineStyle(const ILineStyle & lineStyle)
{
  throw(NotYetImplementedException("setLineStyle()","IDataStyle"));
}

bool IDataStyleROOT::setMarkerStyle(const IMarkerStyle & markerStyle) 
{
  throw(NotYetImplementedException("setMarkerStyle()","IDataStyle"));
}

bool IDataStyleROOT::setFillStyle(const IFillStyle & fillStyle) 
{
  throw(NotYetImplementedException("setFillStyle()","IDataStyle"));
}
