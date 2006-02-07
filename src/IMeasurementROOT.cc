#include <RAIDA/IMeasurementROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;
using namespace std ;


IMeasurementROOT::IMeasurementROOT() 
{
}

IMeasurementROOT::IMeasurementROOT(double value,double error)
{
}

IMeasurementROOT::IMeasurementROOT(double value,double errorPlus,double errorMinus)
{
}

double IMeasurementROOT::value() const
{
  throw( NotYetImplementedException("IMeasurement","value()") );
  return (double)0;
}

double IMeasurementROOT::errorPlus() const
{
  throw(NotYetImplementedException("IMeasurement","errorPlus()"));
  return (double)0;
}

double IMeasurementROOT::errorMinus() const
{
  throw(NotYetImplementedException("IMeasurement","errorMinus()"));
  return 0.;
}

bool IMeasurementROOT::setValue(double value)
{
  throw(NotYetImplementedException("IMeasurement","setValue(double)"));
  return false;
}

bool IMeasurementROOT::setErrorPlus(double errorPlus)
{
  throw(NotYetImplementedException("IMeasurement","setErrorPlus(double)"));
  return false;
}

bool IMeasurementROOT::setErrorMinus(double errorMinus)
{
  throw(NotYetImplementedException("IMeasurement","setErrorMinus(double)"));
  return false;
}

bool IMeasurementROOT::setErrorPlusMinus(double error)
{
  throw(NotYetImplementedException("IMeasurement","setErrorPlusMinus(double)"));
  return false;
}

bool IMeasurementROOT::setErrorPlusMinus(double errorPlus,double errorMinus)
{
  throw(NotYetImplementedException("IMeasurement","setErrorPlusMinus(double , double )"));
  return false;
}

