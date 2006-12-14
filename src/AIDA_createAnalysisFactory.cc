/// #include <RAIDA/AIDA_createAnalysisFactory.h>
#include <RAIDA/IAnalysisFactoryROOT.h>
#include <RAIDA/AIDAHistogramsInROOT.h>
#include <RAIDA/Revision.h>
#include <AIDA/IConstants.h>

#include <RVersion.h>

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
  else
    {
      cout << "*******************************************************************************" << endl;
      cout << "***                    RAIDA has already been initialised                   ***" << endl;
      cout << "*******************************************************************************" << endl;
    }

  // decide, if the additional Histograms are written to the ROOT file:
  string name = "AIDA_HISTOGRAMS_IN_ROOT";
  char *res = getenv( name.c_str() );
  string envResult = "";
  if (res) envResult = res;
  if (envResult == "1") AIDAHistogramsInROOT = true;

  cout << "---------------------------------- R A I D A ----------------------------------" << endl;
  cout << "ROOT Implementation of the Abstract Interfaces for Data Analysis (AIDA v" << AIDA_VERSION << ")" << endl;
  cout << endl;
  if (Revision::getName() != "")
    cout << "RAIDA Version: " << Revision::getName() << endl;
  else
    cout << "RAIDA Version: Experimental" << endl;
  cout << endl;
  if (envResult == "1")
    cout << "RAIDA creates additional histograms to write AIDA specific info to disk" << endl;
  else
    cout << "RAIDA only creates simple ROOT histograms" << endl;
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "Used ROOT Release: " << ROOT_RELEASE << endl; 
#endif
  cout << "-------------------------------------------------------------------------------" << endl;
  cout << endl;

  return newFactory;
}

