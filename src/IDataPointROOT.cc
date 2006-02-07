#include <RAIDA/IDataPointROOT.h>
#include <RAIDA/IMeasurementROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;
using namespace std ;


IDataPointROOT::IDataPointROOT()
{
}

IDataPointROOT::IDataPointROOT(int dimension)
{
}

int IDataPointROOT::dimension() const
{
  return 0;
}

IMeasurement * IDataPointROOT::coordinate(int coord) 
{
  return (IMeasurement*)0;
}

const IMeasurement * IDataPointROOT::coordinate(int coord) const
{
  return (IMeasurement*)0;
}



