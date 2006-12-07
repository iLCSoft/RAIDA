#include <RAIDA/IPlotterStyleROOT.h>

using namespace AIDA ;

IDataStyle & IPlotterStyleROOT::dataStyle() 
{

}

IAxisStyle & IPlotterStyleROOT::xAxisStyle() 
{

}

IAxisStyle & IPlotterStyleROOT::yAxisStyle() 
{

}

IAxisStyle & IPlotterStyleROOT::zAxisStyle()
{

}

ITitleStyle & IPlotterStyleROOT::titleStyle()
{

}

IInfoStyle & IPlotterStyleROOT::infoStyle()
{

}

bool IPlotterStyleROOT::setDataStyle(const IDataStyle & dataStyle) 
{
  return true;
}

bool IPlotterStyleROOT::setAxisStyleX(const IAxisStyle & xAxisStyle)
{
  return true;
}

bool IPlotterStyleROOT::setAxisStyleY(const IAxisStyle & yAxisStyle)
{
  return true;
}

bool IPlotterStyleROOT::setAxisStyleZ(const IAxisStyle & zAxisStyle) 
{
  return true;
}

bool IPlotterStyleROOT::setTitleStyle(const ITitleStyle & textStyle) 
{
  return true;
}

bool IPlotterStyleROOT::setInfoStyle(const IInfoStyle & infoStyle) 
{
  return true;
}
