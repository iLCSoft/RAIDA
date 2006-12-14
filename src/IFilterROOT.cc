#include <RAIDA/IFilterROOT.h>
#include <string>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

bool IFilterROOT::initialize(ITuple & tuple) 
{
  throw(NotYetImplementedException("initialize()","IFilter"));
  return true;
}

bool IFilterROOT::accept() const 
{
  throw(NotYetImplementedException("accept()","IFilter"));
  return true;
}

std::string IFilterROOT::expression() const 
{
  throw(NotYetImplementedException("expression()","IFilter"));
  return std::string("");
}
