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
#include <AIDA/IProfile1D.h>
#include <AIDA/IProfile2D.h>

#include <AIDA/ITupleFactory.h>
#include <AIDA/ITuple.h>
#include <AIDA/ICloud1D.h>
#include <AIDA/ICloud2D.h>
#include <AIDA/ICloud3D.h>
#include <AIDA/IAxis.h>

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
  //  cl6 = myhistofactory->createCloud1D("/er/cl6");

  mytree->cd("er");
  cl5 = myhistofactory->createCloud3D("/ich/cl5","mycl5",500);

  IHistogram1D *myhistoo = myhistofactory->createHistogram1D("/ich/xxl","hi xxl",5,0,1);
  //  mytree->cd("/");
  ITuple *mytuple;
  vector<string> names,types;
  names.push_back("myd");
  types.push_back("D");
  names.push_back("myf");
  types.push_back("F");
  names.push_back("myi");
  types.push_back("I");
  names.push_back("mys");
  types.push_back("S");
  names.push_back("myl");
  types.push_back("L");
  names.push_back("myc");
  types.push_back("char");
  names.push_back("myb");
  types.push_back("bool");
  //cout << "### Noch am LEBEN!!!" << endl;
  mytuple = mytuplefactory->create("/ich/mynt","my first ntuple",
				   names,types,"");
  mytuple->fill(0,11.1);
  mytuple->fill(1,11.2);
  mytuple->fill(2,113);
  mytuple->fill(3,(short)114);
  mytuple->fill(4,(long)115);
  mytuple->fill(5,'b');
  mytuple->fill(6,true);
  mytuple->addRow();

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
  mytree->cd("/er");
  ICloud1D *cl6;
  ICloud2D *cl7;
  ICloud3D *cl8;
  cl6 = myhistofactory->createCloud1D("cl6");
  cl7 = myhistofactory->createCloud2D("cl7");
  cl8 = myhistofactory->createCloud3D("cl8");
  //  IHistogram1D *myhi1 = myhistofactory->createHistogram1D("t1",5,0,1);
  //  IHistogram2D *myhi2 = myhistofactory->createHistogram2D("t2",5,0,1,5,0,1);
  //  IHistogram3D *myhi3 = myhistofactory->createHistogram3D("t3",5,0,1,5,0,1,5,0,1);
  IProfile2D *mypr1 = myhistofactory->createProfile2D("/er/pr1",5,0,1,5,0,1);
  IProfile2D *mypr2 = myhistofactory->createProfile2D("/er/pr2",5,0,1,5,0,1,2,3);

  mytree->commit();
  mytree->close();

}

