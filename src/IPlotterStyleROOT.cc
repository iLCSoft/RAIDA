#include <RAIDA/IPlotterStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

IDataStyle & IPlotterStyleROOT::dataStyle() 
{
  throw(NotYetImplementedException("dataStyle()","IPlotterStyle"));
}

IAxisStyle & IPlotterStyleROOT::xAxisStyle() 
{
  throw(NotYetImplementedException("xAxisStyle()","IPlotterStyle"));
}

IAxisStyle & IPlotterStyleROOT::yAxisStyle() 
{
  throw(NotYetImplementedException("yAxisStyle()","IPlotterStyle"));
}

IAxisStyle & IPlotterStyleROOT::zAxisStyle()
{
  throw(NotYetImplementedException("zAxisStyle()","IPlotterStyle"));
}

ITitleStyle & IPlotterStyleROOT::titleStyle()
{
  throw(NotYetImplementedException("titleStyle()","IPlotterStyle"));
}

IInfoStyle & IPlotterStyleROOT::infoStyle()
{
  throw(NotYetImplementedException("infoStyle()","IPlotterStyle"));
}

bool IPlotterStyleROOT::setDataStyle(const IDataStyle & dataStyle) 
{
  throw(NotYetImplementedException("setDataStyle()","IPlotterStyle"));
  return true;
}

bool IPlotterStyleROOT::setAxisStyleX(const IAxisStyle & xAxisStyle)
{
  throw(NotYetImplementedException("setAxisStyleX()","IPlotterStyle"));
  return true;
}

bool IPlotterStyleROOT::setAxisStyleY(const IAxisStyle & yAxisStyle)
{
  throw(NotYetImplementedException("setAxisStyleY()","IPlotterStyle"));
  return true;
}

bool IPlotterStyleROOT::setAxisStyleZ(const IAxisStyle & zAxisStyle) 
{
  throw(NotYetImplementedException("setAxisStyleZ()","IPlotterStyle"));
  return true;
}

bool IPlotterStyleROOT::setTitleStyle(const ITitleStyle & textStyle) 
{
  throw(NotYetImplementedException("setTitleStyle()","IPlotterStyle"));
  return true;
}

bool IPlotterStyleROOT::setInfoStyle(const IInfoStyle & infoStyle) 
{
  throw(NotYetImplementedException("setInfoStyle()","IPlotterStyle"));
  return true;
}
