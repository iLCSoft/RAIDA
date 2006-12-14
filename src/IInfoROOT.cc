#include <RAIDA/IInfoROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>

using namespace AIDA ;

void IInfoROOT::clear() 
{
  throw(NotYetImplementedException("clear()","IInfo"));
}

void IInfoROOT::addText(const std::string & text) 
{
  throw(NotYetImplementedException("addText()","IInfo"));
}

void IInfoROOT::addLegend(const IMarkerStyle & style, 
			  const std::string & description) 
{
  throw(NotYetImplementedException("addLegend()","IInfo"));
}

void IInfoROOT::addLegend(const ILineStyle & style, 
			  const std::string & description) 
{
  throw(NotYetImplementedException("addLegend()","IInfo"));
}

void IInfoROOT::addLegend(const IFillStyle & style, 
			  const std::string & description) 
{
  throw(NotYetImplementedException("addLegend()","IInfo"));
}
