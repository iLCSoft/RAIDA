#include <RAIDA/IEvaluatorROOT.h>
#include <string>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;

bool IEvaluatorROOT::initialize(ITuple & tuple) 
{
  throw(NotYetImplementedException("initialize()","IEvaluator"));
  return true;
}

double IEvaluatorROOT::evaluateDouble() const 
{
  throw(NotYetImplementedException("evaluateDouble()","IEvaluator"));
  return 0.;
}

std::string IEvaluatorROOT::expression() const 
{
  throw(NotYetImplementedException("expression()","IEvaluator"));
  return std::string("");
}
