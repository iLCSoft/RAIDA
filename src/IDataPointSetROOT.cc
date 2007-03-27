#include <RAIDA/IDataPointSetROOT.h>
#include <RAIDA/IAnnotationROOT.h>
#include <string>
#include <vector>


using namespace AIDA ;

IAnnotation & IDataPointSetROOT::annotation() 
{
  return *(new IAnnotationROOT);
}

const IAnnotation & IDataPointSetROOT::annotation() const
{
  return *(new IAnnotationROOT);
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
  return 0; 
}

bool IDataPointSetROOT::setCoordinate(int coord, 
				      const std::vector<double>  & val, 
				      const std::vector<double>  & err) 
{
  return true; 
}

bool IDataPointSetROOT::setCoordinate(int coord, 
				      const std::vector<double>  & val, 
				      const std::vector<double>  & errp, 
				      const std::vector<double>  & errm) 
{
  return true; 
}

const IDataPoint * IDataPointSetROOT::point(int index) const 
{
  return 0;
}

IDataPoint * IDataPointSetROOT::addPoint() 
{
  return 0;
}

bool IDataPointSetROOT::addPoint(const IDataPoint & point) 
{
  return true;
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
