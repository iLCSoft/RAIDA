#include <RAIDA/IPlotterFactoryROOT.h>
#include <RAIDA/IAxisStyleROOT.h>
#include <RAIDA/IDataStyleROOT.h>
#include <RAIDA/IFillStyleROOT.h>
#include <RAIDA/ILineStyleROOT.h>
#include <RAIDA/IMarkerStyleROOT.h>
#include <RAIDA/IPlotterROOT.h>
#include <RAIDA/IPlotterStyleROOT.h>
#include <RAIDA/ITextStyleROOT.h>
#include <RAIDA/ITitleStyleROOT.h>
#include <string>

using namespace AIDA ;

IPlotter * IPlotterFactoryROOT::create(const std::string & name) 
{
  IPlotter *plotter = new IPlotterROOT;
  return plotter; 
}

IMarkerStyle * IPlotterFactoryROOT::createMarkerStyle()
{
  IMarkerStyle *marker = new IMarkerStyleROOT;
  return marker;
}

ITextStyle * IPlotterFactoryROOT::createTextStyle()
{
  ITextStyle *text = new ITextStyleROOT;
  return text;
}

ILineStyle * IPlotterFactoryROOT::createLineStyle()
{
  ILineStyle *line = new ILineStyleROOT;
  return line;
}

IFillStyle * IPlotterFactoryROOT::createFillStyle()
{
  IFillStyle *fill = new IFillStyleROOT;
  return fill;
}

IDataStyle * IPlotterFactoryROOT::createDataStyle()
{
  IDataStyle *data = new IDataStyleROOT;
  return data;
}

IAxisStyle * IPlotterFactoryROOT::createAxisStyle()
{
  IAxisStyle *axis = new IAxisStyleROOT;
  return axis;
}

ITitleStyle * IPlotterFactoryROOT::createTitleStyle()
{
  ITitleStyle *title = new ITitleStyleROOT;
  return title;
}

IPlotterStyle * IPlotterFactoryROOT::createPlotterStyle()
{
  IPlotterStyle *plotter = new IPlotterStyleROOT;
  return plotter;
}
