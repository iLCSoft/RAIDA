/// #include <RAIDA/AIDA_createAnalysisFactory.h>
#include <RAIDA/IAnalysisFactoryROOT.h>

using namespace std ;
using namespace AIDA ;

IAnalysisFactory* AIDA_createAnalysisFactory(void)
{
  static IAnalysisFactory * newFactory = 0;

  if (newFactory == 0) 
    {
      newFactory = new IAnalysisFactoryROOT;
    }

  return newFactory;
}

