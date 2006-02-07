// #include <RAIDA/utilROOT.h>
#include <RAIDA/LeafPoint.h>
#include <TH1F.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>


#include <iostream>
#include <string>
#include <vector>

#include <AIDA/IAnalysisFactory.h>
#include <AIDA/ITreeFactory.h>
#include <AIDA/ITree.h>
#include <AIDA/IHistogramFactory.h>
#include <AIDA/IHistogram1D.h>
#include <AIDA/IHistogram2D.h>
#include <AIDA/IHistogram3D.h>
#include <AIDA/ITupleFactory.h>
#include <AIDA/ITuple.h>
#include <AIDA/ICloud1D.h>
#include <AIDA/ICloud2D.h>
#include <AIDA/ICloud3D.h>

using namespace AIDA ;
using namespace std;

int main()
{
  IAnalysisFactory * myaida;
  ITreeFactory * mytreefactory;
  ITree * mytree;
  IHistogramFactory * myhistofactory;
  myaida = AIDA_createAnalysisFactory();
  mytreefactory = myaida->createTreeFactory();


  std::string storeName("aidaroot.root");
  std::string storeType("root");
  bool readOnly = false;
  bool createNew = false;
  std::string options("keine");
  mytree = mytreefactory->create(storeName,storeType,readOnly,createNew,options);

  ITupleFactory * mytuplefactory = myaida->createTupleFactory(*mytree);
  myhistofactory = myaida->createHistogramFactory(*mytree);

  mytree->mkdir("ich");
  mytree->mkdir("du");
  mytree->mkdir("er");
  IHistogram1D *myhisto = myhistofactory->createHistogram1D("/x1","hi1",5,0,1);
  ICloud3D *cl1, *cl2, *cl3, *cl4, *cl5;
  cl1 = myhistofactory->createCloud3D("/ich/cl1","mycl1",500);
  cl2 = myhistofactory->createCloud3D("/ich/cl2","mycl2",15);
  cl3 = myhistofactory->createCloud3D("/du/cl3","mycl3",500);
  cl4 = myhistofactory->createCloud3D("/er/cl4","mycl4",15);
  mytree->cd("er");
  cl5 = myhistofactory->createCloud3D("/ich/cl5","mycl5",500);

    for (int i = 0; i<490; i++)
      {
		cl1->fill( (double)i,(double)i,(double)i  );
	  	cl2->fill( (double)i,(double)i,(double)i  );
	  	cl3->fill( (double)i,(double)i,(double)i  );
	  	cl4->fill( (double)i,(double)i,(double)i  );
	  	cl5->fill( (double)i,(double)i,(double)i  );
      }

    //        cl3->scale(3.);
    //        cl4->scale(3.);

/// Schliessen der Datei. -----------------------------------------------------
  mytree->commit();
  mytree->close();

}

