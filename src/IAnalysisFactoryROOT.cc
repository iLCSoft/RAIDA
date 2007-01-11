#include <RAIDA/IAnalysisFactoryROOT.h>
#include <RAIDA/ITreeFactoryROOT.h>
#include <RAIDA/ITreeROOT.h>
#include <RAIDA/IHistogramFactoryROOT.h>
#include <RAIDA/ITupleFactoryROOT.h>
#include <RAIDA/IDataPointSetFactoryROOT.h>
#include <RAIDA/IFunctionFactoryROOT.h>
#include <RAIDA/IPlotterFactoryROOT.h>
#include <RAIDA/IFitFactoryROOT.h>


#include <RAIDA/NotYetImplementedException.h>

using namespace AIDA ;
using namespace std;

ITreeFactory * IAnalysisFactoryROOT::createTreeFactory()
{
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "IAnalysisFactoryROOT::createTreeFactory()" 
       << ": " 
       << "Create the TreeFactory" << endl;
#endif
  return new ITreeFactoryROOT;
}

IHistogramFactory * IAnalysisFactoryROOT::createHistogramFactory(ITree & tree)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "IAnalysisFactoryROOT::createHistogramFactory(ITree & tree)" 
       << ": " 
       << "Create HistogramFactory connected to store (file): "  
       << tree.storeName() << endl;
#endif
  return new IHistogramFactoryROOT(tree);
}

ITupleFactory * IAnalysisFactoryROOT::createTupleFactory(ITree & tree)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "IAnalysisFactoryROOT::createTupleFactory(ITree & tree)" 
       << ": " 
       << "Create TupleFactory connected to store (file): "  
       << tree.storeName() << endl;
#endif
  return new ITupleFactoryROOT(tree);
}

IDataPointSetFactory * IAnalysisFactoryROOT::createDataPointSetFactory(ITree & tree)
{
  //throw(NotYetImplementedException("IDataPointSetFactory"));
  // fg: return an empty dummy object to allow Marlin to use RAIDA
  // as Marlin::AIDAProcessor instantiates an IDataPointSetFactory...
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "IAnalysisFactoryROOT::createDataPointSetFactory(ITree & tree)" 
       << ": " 
       << "Create DataPointSetFactory connected to store (file): "  
       << tree.storeName() << endl;
#endif
  return new IDataPointSetFactoryROOT(tree);
}

IFunctionFactory * IAnalysisFactoryROOT::createFunctionFactory(ITree & tree)
{
  throw(NotYetImplementedException("IFunctionFactory"));
  return new IFunctionFactoryROOT;
}

IPlotterFactory * IAnalysisFactoryROOT::createPlotterFactory(int argc,
							     char * * args,
							     const std::string & imp,
							     const std::string & lib)
{
  throw(NotYetImplementedException("IPlotterFactory"));
  return new IPlotterFactoryROOT;
}

IFitFactory * IAnalysisFactoryROOT::createFitFactory()
{
  throw(NotYetImplementedException("IFitFactory"));
  return new IFitFactoryROOT;
}
