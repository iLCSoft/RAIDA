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
  mytree->cd("/");

// 1D histos: 
  cout << "1D-Histos: ------------------------------------------------------------------" << endl;
  IHistogram1D *myhisto2 = myhistofactory->createHistogram1D("/la","l1",5,2,7);
  cout << "binning: " << myhisto2->axis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto2->axis().lowerEdge() << " - " 
       << myhisto2->axis().upperEdge() << " bins: " 
       << myhisto2->axis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto2->axis().binLowerEdge(k) << " - " 
	 << myhisto2->axis().binUpperEdge(k) << " width: " 
	 << myhisto2->axis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto2->axis().coordToIndex(0) << " " 
       << myhisto2->axis().coordToIndex(3) << " " 
       << myhisto2->axis().coordToIndex(9)  << endl;

// 2D histos: 
  cout << "2D-Histos: ------------------------------------------------------------------" << endl;
  IHistogram2D *myhisto22 
    = myhistofactory->createHistogram2D("/lb","l2",5,2,7,5,9,14);
// x-Achse:
  cout << "binning: X" << myhisto22->xAxis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto22->xAxis().lowerEdge() << " - " 
       << myhisto22->xAxis().upperEdge() << " bins: " 
       << myhisto22->xAxis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto22->xAxis().binLowerEdge(k) << " - " 
	 << myhisto22->xAxis().binUpperEdge(k) << " width: " 
	 << myhisto22->xAxis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto22->xAxis().coordToIndex(0) << " " 
       << myhisto22->xAxis().coordToIndex(3) << " " 
       << myhisto22->xAxis().coordToIndex(9)  << endl;
// y-Achse:
  cout << "binning: Y" << myhisto22->yAxis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto22->yAxis().lowerEdge() << " - " 
       << myhisto22->yAxis().upperEdge() << " bins: " 
       << myhisto22->yAxis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto22->yAxis().binLowerEdge(k) << " - " 
	 << myhisto22->yAxis().binUpperEdge(k) << " width: " 
	 << myhisto22->yAxis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto22->yAxis().coordToIndex(0) << " " 
       << myhisto22->yAxis().coordToIndex(13) << " " 
       << myhisto22->yAxis().coordToIndex(19)  << endl;
// 3D histos: 
  cout << "3D-Histos: ------------------------------------------------------------------" << endl;
  IHistogram3D *myhisto23 
    = myhistofactory->createHistogram3D("/lc","l3",5,2,7,5,9,14,5,22,27);
// x-Achse:
  cout << "binning: X" << myhisto23->xAxis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto23->xAxis().lowerEdge() << " - " 
       << myhisto23->xAxis().upperEdge() << " bins: " 
       << myhisto23->xAxis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto23->xAxis().binLowerEdge(k) << " - " 
	 << myhisto23->xAxis().binUpperEdge(k) << " width: " 
	 << myhisto23->xAxis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto23->xAxis().coordToIndex(0) << " " 
       << myhisto23->xAxis().coordToIndex(3) << " " 
       << myhisto23->xAxis().coordToIndex(9)  << endl;
// y-Achse:
  cout << "binning: Y" << myhisto23->yAxis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto23->yAxis().lowerEdge() << " - " 
       << myhisto23->yAxis().upperEdge() << " bins: " 
       << myhisto23->yAxis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto23->yAxis().binLowerEdge(k) << " - " 
	 << myhisto23->yAxis().binUpperEdge(k) << " width: " 
	 << myhisto23->yAxis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto23->yAxis().coordToIndex(0) << " " 
       << myhisto23->yAxis().coordToIndex(13) << " " 
       << myhisto23->yAxis().coordToIndex(19)  << endl;
// z-Achse:
  cout << "binning: Z" << myhisto23->zAxis().isFixedBinning() << endl; 
  cout << "range: " 
       << myhisto23->zAxis().lowerEdge() << " - " 
       << myhisto23->zAxis().upperEdge() << " bins: " 
       << myhisto23->zAxis().bins() << endl; 
  for (int k=0;k<=6;k++) 
    cout << "bin " << k << " " 
	 << myhisto23->zAxis().binLowerEdge(k) << " - " 
	 << myhisto23->zAxis().binUpperEdge(k) << " width: " 
	 << myhisto23->zAxis().binWidth(k) << endl;
  cout << "index: " 
       << myhisto23->zAxis().coordToIndex(20) << " " 
       << myhisto23->zAxis().coordToIndex(23) << " " 
       << myhisto23->zAxis().coordToIndex(29)  << endl;


  mytree->commit();
  mytree->close();

}

