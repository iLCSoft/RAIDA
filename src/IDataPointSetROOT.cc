#include <RAIDA/IDataPointSetROOT.h>
#include <string>
#include <vector>


using namespace AIDA ;

IAnnotation & IDataPointSetROOT::annotation() 
{
}

const IAnnotation & IDataPointSetROOT::annotation() const
{
}

std::string IDataPointSetROOT::title() const 
{
  return std::string("");
}

bool IDataPointSetROOT::setTitle(const std::string & title) 
{
  return true;
}

int IDataPointSetROOT::dimension() const 
{
  return 0;
}

void IDataPointSetROOT::clear() 
{
}

int IDataPointSetROOT::size() const 
{
  return 0;
}

IDataPoint * IDataPointSetROOT::point(int index) 
{
}

bool IDataPointSetROOT::setCoordinate(int coord, 
				      const std::vector<double>  & val, 
				      const std::vector<double>  & err) 
{
}

bool IDataPointSetROOT::setCoordinate(int coord, 
				      const std::vector<double>  & val, 
				      const std::vector<double>  & errp, 
				      const std::vector<double>  & errm) 
{
}

const IDataPoint * IDataPointSetROOT::point(int index) const 
{
}

IDataPoint * IDataPointSetROOT::addPoint() 
{
}

bool IDataPointSetROOT::addPoint(const IDataPoint & point) 
{
}

bool IDataPointSetROOT::removePoint(int index) 
{
  return true;
}

double IDataPointSetROOT::lowerExtent(int coord) const 
{
  return 0.;
}

double IDataPointSetROOT::upperExtent(int coord) const 
{
  return 0.;
}

bool IDataPointSetROOT::scale(double scaleFactor) 
{
  return true;
}

bool IDataPointSetROOT::scaleValues(double scaleFactor) 
{
  return true;
}

bool IDataPointSetROOT::scaleErrors(double scaleFactor) 
{
  return true;
}

void * IDataPointSetROOT::cast(const std::string & className) const 
{
  return 0;
}
