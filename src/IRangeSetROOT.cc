#include <RAIDA/IRangeSetROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <vector>

using namespace AIDA ;

const std::vector<double>  & IRangeSetROOT::lowerBounds() 
{
  throw(NotYetImplementedException("lowerBounds()","IRangeSet"));
  std::vector<double> x;
  return x;
}

const std::vector<double>  & IRangeSetROOT::upperBounds() 
{
  throw(NotYetImplementedException("upperBounds()","IRangeSet"));
  std::vector<double> x;
  return x;
}

void IRangeSetROOT::include(double xMin, double xMax) 
{
  throw(NotYetImplementedException("include()","IRangeSet"));
}

void IRangeSetROOT::exclude(double xMin, double xMax)
{
  throw(NotYetImplementedException("exclude()","IRangeSet"));
}

void IRangeSetROOT::includeAll() 
{
  throw(NotYetImplementedException("includeAll()","IRangeSet"));
}

void IRangeSetROOT::excludeAll() 
{
  throw(NotYetImplementedException("excludeAll()","IRangeSet"));
}

bool IRangeSetROOT::isInRange(double point) 
{
  throw(NotYetImplementedException("isInRange()","IRangeSet"));
  return true;
}

int IRangeSetROOT::size() 
{
  throw(NotYetImplementedException("size()","IRangeSet"));
  return 0;
}

double IRangeSetROOT::PLUS_INF() 
{
  throw(NotYetImplementedException("PLUS_INF()","IRangeSet"));
  return 0.;
}

double IRangeSetROOT::MINUS_INF() 
{
  throw(NotYetImplementedException("MINUS_INF()","IRangeSet"));
  return 0.;
}
