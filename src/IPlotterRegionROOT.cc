// -*- C++ -*-
#include <RAIDA/IPlotterRegionROOT.h>
#include <RAIDA/IDataPointSetROOT.h>
#include <RAIDA/IFunctionROOT.h>
#include <RAIDA/ICloud1DROOT.h>
#include <RAIDA/ICloud2DROOT.h>
#include <RAIDA/ICloud3DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/IProfile1DROOT.h>
#include <RAIDA/IProfile2DROOT.h>
#include <RAIDA/IInfoROOT.h>
#include <RAIDA/IPlotterLayoutROOT.h>
#include <RAIDA/IPlotterStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

#include <string>
#include <vector>

using namespace AIDA ;


bool IPlotterRegionROOT::plot(const IBaseHistogram & histogram, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::plot(const IBaseHistogram & histogram, 
			      const IPlotterStyle & style, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::plot(const IFunction & function, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::plot(const IFunction & function, 
			      const IPlotterStyle & style, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::plot(const IDataPointSet & dataPointSet, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::plot(const IDataPointSet & dataPointSet, 
			      const IPlotterStyle & style, 
			      const std::string & options) 
{
  throw(NotYetImplementedException("plot()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::remove(const IBaseHistogram & histogram) 
{
  throw(NotYetImplementedException("remove()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::remove(const IFunction & function) 
{
  throw(NotYetImplementedException("remove()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::remove(const IDataPointSet & dataPointSet) 
{
  throw(NotYetImplementedException("remove()","IPlotterRegion"));
  return true;
}

void IPlotterRegionROOT::clear() 
{
  throw(NotYetImplementedException("clear()","IPlotterRegion"));
}

bool IPlotterRegionROOT::setParameter(const std::string & parameter, 
				      const std::string & options) 
{
  throw(NotYetImplementedException("setParameter()","IPlotterRegion"));
  return true;
}

std::string IPlotterRegionROOT::parameterValue(const std::string & parameter) const 
{
  throw(NotYetImplementedException("parameterValue()","IPlotterRegion"));
  return std::string("");
}

std::vector<std::string> IPlotterRegionROOT::availableParameterOptions(const std::string & parameter) const 
{
  throw(NotYetImplementedException("availableParameterOptions()","IPlotterRegion"));
  std::vector<std::string> x;
  return x;
}

std::vector<std::string> IPlotterRegionROOT::availableParameters() const 
{
  throw(NotYetImplementedException("availableParameters()","IPlotterRegion"));
  std::vector<std::string> x;
  return x;
}

IPlotterStyle & IPlotterRegionROOT::style() 
{
  throw(NotYetImplementedException("style()","IPlotterRegion"));
  IPlotterStyle *x = new IPlotterStyleROOT;
  return *x;
}

bool IPlotterRegionROOT::setStyle(const IPlotterStyle & style) 
{
  throw(NotYetImplementedException("setStyle()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::applyStyle(const IPlotterStyle & style) 
{
  throw(NotYetImplementedException("applyStyle()","IPlotterRegion"));
  return true;
}

void IPlotterRegionROOT::setTitle(const std::string & title) 
{
  throw(NotYetImplementedException("setTitle()","IPlotterRegion"));
}

bool IPlotterRegionROOT::setXLimits(double min, double max) 
{
  throw(NotYetImplementedException("setXLimits()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::setYLimits(double min, double max) 
{
  throw(NotYetImplementedException("setYLimits()","IPlotterRegion"));
  return true;
}

bool IPlotterRegionROOT::setZLimits(double min, double max) 
{
  throw(NotYetImplementedException("setZLimits()","IPlotterRegion"));
  return true;
}

IPlotterLayout & IPlotterRegionROOT::layout() 
{
  throw(NotYetImplementedException("layout()","IPlotterRegion"));
  IPlotterLayout *x = new IPlotterLayoutROOT;
  return *x;
}

bool IPlotterRegionROOT::setLayout(const IPlotterLayout & layout) 
{
  throw(NotYetImplementedException("setLayout()","IPlotterRegion"));
  return true;
}

IInfo & IPlotterRegionROOT::info() 
{
  throw(NotYetImplementedException("info()","IPlotterRegion"));
  IInfo *x = new IInfoROOT;
  return *x;
}
