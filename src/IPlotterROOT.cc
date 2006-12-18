#include <RAIDA/IPlotterROOT.h>
#include <RAIDA/IPlotterRegionROOT.h>
#include <RAIDA/ITitleStyleROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <string>
#include <vector>

using namespace AIDA ;

IPlotterRegion * IPlotterROOT::createRegion(double x, 
					    double y, 
					    double w, 
					    double h ) 
{
  throw(NotYetImplementedException("createRegion()","IPlotter"));
}

bool IPlotterROOT::createRegions(int columns, 
				 int rows, 
				 int index) 
{
  throw(NotYetImplementedException("createRegions()","IPlotter"));
  return true;
}

IPlotterRegion & IPlotterROOT::currentRegion() const 
{
  throw(NotYetImplementedException("currentRegion()","IPlotter"));
}

int IPlotterROOT::currentRegionNumber() const 
{
  throw(NotYetImplementedException("currentRegionNumber()","IPlotter"));
  return 0;
}

int IPlotterROOT::numberOfRegions() const 
{
  throw(NotYetImplementedException("numberOfRegions()","IPlotter"));
  return 0;
}

bool IPlotterROOT::setCurrentRegionNumber(int index) 
{
  throw(NotYetImplementedException("setCurrentRegionNumber()","IPlotter"));
  return true;
}

IPlotterRegion & IPlotterROOT::next() 
{
  throw(NotYetImplementedException("next()","IPlotter"));
}

IPlotterRegion * IPlotterROOT::region(int index) const 
{
  throw(NotYetImplementedException("region()","IPlotter"));
}

void IPlotterROOT::destroyRegions() 
{
  throw(NotYetImplementedException("destroyRegions()","IPlotter"));
}

void IPlotterROOT::clearRegions() 
{
  throw(NotYetImplementedException("clearRegions()","IPlotter"));
}

bool IPlotterROOT::setParameter(const std::string & parameter, 
				const std::string & options) 
{
  throw(NotYetImplementedException("setParameter()","IPlotter"));
  return true;
}

std::string IPlotterROOT::parameterValue(const std::string & parameter) const 
{
  throw(NotYetImplementedException("parameterValue()","IPlotter"));
  return std::string("");
}

std::vector<std::string> IPlotterROOT::availableParameterOptions(const std::string & parameter) const 
{
  throw(NotYetImplementedException("availableParameterOptions()","IPlotter"));
  std::vector<std::string> sv;
  return sv;
}

std::vector<std::string> IPlotterROOT::availableParameters() const 
{
  throw(NotYetImplementedException("availableParameters()","IPlotter"));
  std::vector<std::string> sv;
  return sv;
}

bool IPlotterROOT::show() 
{
  throw(NotYetImplementedException("show()","IPlotter"));
  return true;
}

bool IPlotterROOT::refresh() 
{
  throw(NotYetImplementedException("refresh()","IPlotter"));
  return true;
}

bool IPlotterROOT::hide() 
{
  throw(NotYetImplementedException("hide()","IPlotter"));
  return true;
}

bool IPlotterROOT::interact() 
{
  throw(NotYetImplementedException("interact()","IPlotter"));
  return true;
}

bool IPlotterROOT::writeToFile(const std::string & filename, 
			       const std::string & type) 
{
  throw(NotYetImplementedException("writeToFile()","IPlotter"));
  return true;
}

void IPlotterROOT::setTitle(const std::string & title) 
{
  throw(NotYetImplementedException("setTitle()","IPlotter"));
}

ITitleStyle & IPlotterROOT::titleStyle() 
{
  throw(NotYetImplementedException("titleStyle()","IPlotter"));
}

void IPlotterROOT::setTitleStyle(const ITitleStyle & style) 
{
  throw(NotYetImplementedException("setTitleStyle()","IPlotter"));
}
