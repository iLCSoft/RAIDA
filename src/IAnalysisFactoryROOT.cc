#include <RAIDA/IAnalysisFactoryROOT.h>
#include <RAIDA/ITreeFactoryROOT.h>
#include <RAIDA/ITreeROOT.h>
#include <RAIDA/IHistogramFactoryROOT.h>
#include <RAIDA/ITupleFactoryROOT.h>
#include <RAIDA/IDataPointSetFactoryROOT.h>
#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;
using namespace std;

ITreeFactory * IAnalysisFactoryROOT::createTreeFactory()
{
  return new ITreeFactoryROOT;
}

IHistogramFactory * IAnalysisFactoryROOT::createHistogramFactory(ITree & tree)
{
  return new IHistogramFactoryROOT(tree);
}

ITupleFactory * IAnalysisFactoryROOT::createTupleFactory(ITree & tree)
{
  return new ITupleFactoryROOT(tree);
}

IDataPointSetFactory * IAnalysisFactoryROOT::createDataPointSetFactory(ITree & tree)
{
  throw(NotYetImplementedException("IDataPointSetFactory"));
  //  return new IDataPointSetFactoryROOT(tree);
}

IFunctionFactory * IAnalysisFactoryROOT::createFunctionFactory(ITree & tree)
{
  throw(NotYetImplementedException("IFunctionFactory"));
}

IPlotterFactory * IAnalysisFactoryROOT::createPlotterFactory(int argc,
							     char * * args,
							     const std::string & imp,
							     const std::string & lib)
{
  throw(NotYetImplementedException("IPlotterFactory"));
}

IFitFactory * IAnalysisFactoryROOT::createFitFactory()
{
  throw(NotYetImplementedException("IFitFactory"));
}
