/// #include <RAIDA/AIDA_createAnalysisFactory.h>
#include <RAIDA/IAnalysisFactoryROOT.h>
#include <RAIDA/AIDAHistogramsInROOT.h>
#include <stdlib.h>
#include <string>

namespace AIDA {
bool AIDAHistogramsInROOT = false;
}

using namespace std ;
using namespace AIDA ;

IAnalysisFactory* AIDA_createAnalysisFactory(void)
{
  static IAnalysisFactory * newFactory = 0;

  if (newFactory == 0) 
    {
      newFactory = new IAnalysisFactoryROOT;
    }

  // decide, if the additional Histograms are written to the ROOT file:
  string name = "AIDA_HISTOGRAMS_IN_ROOT";
  char *res = getenv( name.c_str() );
  string envResult = "";
  if (res) envResult = res;
  if (envResult == "1") AIDAHistogramsInROOT = true;

  return newFactory;
}

