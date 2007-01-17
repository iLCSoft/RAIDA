// #include <RAIDA/utilROOT.h>
#include <RAIDA/LeafPoint.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TDirectory.h>
#include <TFile.h>
#include <TTree.h>
#include <TAxis.h>

#include <iostream>
#include <string>
#include <vector>

#include <AIDA/IAnalysisFactory.h>
#include <AIDA/ITreeFactory.h>
#include <AIDA/ITree.h>
#include <AIDA/IHistogramFactory.h>
#include <RAIDA/IHistogram1DROOT.h>
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
  ICloud1D *cl10,*cl11;
  ICloud2D *cl20,*cl21;
  ICloud3D *cl30,*cl31;
  cl10 = myhistofactory->createCloud1D("/ich/cl10","mycl10",400);
  cl20 = myhistofactory->createCloud2D("/ich/cl20","mycl20",400);
  cl30 = myhistofactory->createCloud3D("/ich/cl30","mycl30",400);
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
  ITuple *mytuple1;
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

  mytuple1 = mytuplefactory->create("/ich/myntx","my first ntuplex",
				    " D col1 , int col2 , col3 ","");
  mytuple->fill(0,11.1);
  mytuple->fill(1,(float)-11.2);
  mytuple->fill(2,113);
  mytuple->fill(3,(short)114);
  mytuple->fill(4,(long)115);
  mytuple->fill(5,'b');
  mytuple->fill(6,true);
  cout << "### Spalte mit float: " << mytuple->getFloat(1) << endl;
  mytuple->addRow();

    for (int i = 0; i<490; i++)
      {
		cl1->fill( (double)i,(double)i,(double)i  );
		cl10->fill( (double)i );
		cl20->fill( (double)i,(double)i );
		cl30->fill( (double)i,(double)i,(double)i );
	  	cl2->fill( (double)i,(double)i,(double)i  );
	  	cl3->fill( (double)i,(double)i,(double)i  );
	  	cl4->fill( (double)i,(double)i,(double)i  );
	  	cl5->fill( (double)i,(double)i,(double)i  );
      }

    //        cl3->scale(3.);
    //        cl4->scale(3.);

/// Schliessen der Datei. -----------------------------------------------------
  mytree->cd("/er");
  //  ICloud1D *cl6;
  //  ICloud2D *cl7;
  //  ICloud3D *cl8;
  //  cl6 = myhistofactory->createCloud1D("cl6");
  //  cl7 = myhistofactory->createCloud2D("cl7");
  //  cl8 = myhistofactory->createCloud3D("cl8");

  //  IHistogram1D *myhi1 = myhistofactory->createHistogram1D("t1",5,0,1);
  //  IHistogram1D *myhi2 = myhistofactory->createCopy("/er/copy1",*myhi1);

  //  IHistogram2D *myhi3 = myhistofactory->createHistogram2D("t2",5,0,1,5,0,1);
  //  IHistogram2D *myhi4 = myhistofactory->createCopy("/er/copy2",*myhi3);

  //  IHistogram3D *myhi5 = myhistofactory->createHistogram3D("t3",5,0,1,5,0,1,5,0,1);
  //  IHistogram3D *myhi6 = myhistofactory->createCopy("/er/copy3",*myhi5);

  //  IProfile1D *mypr1 = myhistofactory->createProfile1D("/er/pr1",5,0,1);
  //  IProfile1D *mypr2 = myhistofactory->createCopy("/er/prc1",*mypr1);

  //  IProfile2D *mypr3 = myhistofactory->createProfile2D("/er/pr2",5,0,1,5,0,1);
  //  IProfile2D *mypr4 = myhistofactory->createCopy("/er/prc2",*mypr3);

  //IProfile2D *mypr2 = myhistofactory->createProfile2D("/er/pr2",5,0,1,5,0,1,2,3);

  //  cl11 = myhistofactory->createCopy("cl11",*cl10);
  //  cl21 = myhistofactory->createCopy("cl21",*cl20);
  //  cl31 = myhistofactory->createCopy("cl31",*cl30);

// variables Binning:
  vector<double> be;
  be.push_back(0.);
  be.push_back(1.);
  be.push_back(3.);

  //  IHistogram1D *myhi10 = myhistofactory->createHistogram1D("/er/v1","hv1",be);
  //  IHistogram2D *myhi20 = myhistofactory->createHistogram2D("/er/v2","hv2",be,be);
  //  IHistogram3D *myhi30 = myhistofactory->createHistogram3D("/er/v3","hv3",be,be,be);

  //  IProfile1D *mypr1 = myhistofactory->createProfile1D("pr1","mypr1",be);
  //  IProfile2D *mypr2 = myhistofactory->createProfile2D("pr2","mypr2",be,be);

  //    cout << "Variables Binning: " << endl;
  //    for ( int i=0 ; i<=mypr1->axis().bins()+1;i++)
  //      cout << i << " " 
  //  	 << mypr1->axis().binLowerEdge(i) << " " 
  //  	 << mypr1->axis().binUpperEdge(i) << " "
  //  	 << mypr2->xAxis().binLowerEdge(i) << " " 
  //  	 << mypr2->xAxis().binUpperEdge(i) << " "
  //  	 << mypr2->yAxis().binLowerEdge(i) << " " 
  //  	 << mypr2->yAxis().binUpperEdge(i) << " "
  //	 << myhi30->xAxis().binLowerEdge(i) << " " 
  //	 << myhi30->xAxis().binUpperEdge(i) << " "
  //	 << myhi30->yAxis().binLowerEdge(i) << " " 
  //	 << myhi30->yAxis().binUpperEdge(i) << " "
  //	 << myhi30->zAxis().binLowerEdge(i) << " " 
  //	 << myhi30->zAxis().binUpperEdge(i) << " "
  //  	 << endl;

// Add ... 
  IHistogram3D *myhi1 = myhistofactory->createHistogram3D("t1",3,0,1,3,0,1,1,0,1);
  IHistogram3D *myhi2 = myhistofactory->createHistogram3D("t2",3,0,1,3,0,1,1,0,1);
  IHistogram2D *myhii = myhistofactory->createHistogram2D("txy",3,0,1,3,0,1);
  myhi1->fill(-10.,-10.,0.5);
  myhi1->fill(-10.,0.1,0.5);
  myhi1->fill(-10,0.4,0.5);
  myhi1->fill(-10.,0.7,0.5);
  myhi1->fill(-10.,10.,0.5);
  myhi1->fill(0.1,-10.,0.5);
  myhi1->fill(0.1,0.1,0.5);
  myhi1->fill(0.1,0.4,0.5);
  myhi1->fill(0.1,0.7,0.5);
  myhi1->fill(0.1,10.,0.5);
  myhi1->fill(0.4,-10.,0.5);
  myhi1->fill(0.4,0.1,0.5);
  myhi1->fill(0.4,0.4,0.5);
  myhi1->fill(0.4,0.7,0.5);
  myhi1->fill(0.4,10.,0.5);
  myhi1->fill(0.7,-10.,0.5);
  myhi1->fill(0.7,0.1,0.5);
  myhi1->fill(0.7,0.4,0.5);
  myhi1->fill(0.7,0.7,0.5);
  myhi1->fill(0.7,10.,0.5);
  myhi1->fill(10.,-10.,0.5);
  myhi1->fill(10.,0.1,0.5);
  myhi1->fill(10.,0.4,0.5);
  myhi1->fill(10.,0.7,0.5);
  myhi1->fill(10.,10.,0.5);

  myhi2->fill(-20,-20,0.5);
  myhi2->fill(-20,0.3,0.5);
  myhi2->fill(-20,0.6,0.5);
  myhi2->fill(-20,0.9,0.5);
  myhi2->fill(-20,20.,0.5);
  myhi2->fill(0.3,-20,0.5);
  myhi2->fill(0.3,0.3,0.5);
  myhi2->fill(0.3,0.6,0.5);
  myhi2->fill(0.3,0.9,0.5);
  myhi2->fill(0.3,20,0.5);
  myhi2->fill(0.6,-20,0.5);
  myhi2->fill(0.6,0.3,0.5);
  myhi2->fill(0.6,0.6,0.5);
  myhi2->fill(0.6,0.9,0.5);
  myhi2->fill(0.6,20.,0.5);
  myhi2->fill(0.9,-20.,0.5);
  myhi2->fill(0.9,0.3,0.5);
  myhi2->fill(0.9,0.6,0.5);
  myhi2->fill(0.9,0.9,0.5);
  myhi2->fill(0.9,20.,0.5);
  myhi2->fill(20.,-20.,0.5);
  myhi2->fill(20.,0.3,0.5);
  myhi2->fill(20.,0.6,0.5);
  myhi2->fill(20.,0.9,0.5);
  myhi2->fill(20.,20.,0.5);
  // 2d-histo
  myhii->fill(-20,-20,0.5);
  myhii->fill(-20,0.3,0.5);
  myhii->fill(-20,0.6,0.5);
  myhii->fill(-20,0.9,0.5);
  myhii->fill(-20,20.,0.5);
  myhii->fill(0.3,-20,0.5);
  myhii->fill(0.3,0.3,0.3);
  myhii->fill(0.3,0.6,0.3);
  myhii->fill(0.3,0.9,0.3);
  myhii->fill(0.3,20,0.5);
  myhii->fill(0.6,-20,0.5);
  myhii->fill(0.6,0.3,0.6);
  myhii->fill(0.6,0.6,0.6);
  myhii->fill(0.6,0.9,0.6);
  myhii->fill(0.6,20.,0.5);
  myhii->fill(0.9,-20.,0.5);
  myhii->fill(0.9,0.3,0.9);
  myhii->fill(0.9,0.6,0.9);
  myhii->fill(0.9,0.9,0.9);
  myhii->fill(0.9,20.,0.5);
  myhii->fill(20.,-20.,0.5);
  myhii->fill(20.,0.3,0.5);
  myhii->fill(20.,0.6,0.5);
  myhii->fill(20.,0.9,0.5);
  myhii->fill(20.,20.,0.5);

  IHistogram3D *myhi3 = myhistofactory->add("added",*myhi1,*myhi2);
  // IHistogram1D *proj = myhistofactory->projectionY("pr",*myhii);  
  IHistogram1D *proj = myhistofactory->sliceY("pr",*myhii,1);  
  //  myhi1->add(*myhi2);
  //  IHistogram2D *myhi3 = myhi1; 
  cout << "### noch da! proj: " << proj << endl; 
  for (int i=0;i<=2;i++)
    {
  //        cout << proj->binMean(0) << " ";
      cout << proj->binHeight(i) << " ";
    }
  cout << endl; 
  for (int i=0;i<=2;i++)
    {
      for (int j=0;j<=2;j++)
	cout << myhii->binHeight(j,i) << " "; 
      cout << endl;
    }
  //cout << "### das ist nan" << endl;
  for (int i=-2;i<=2;i++)
    {
      for (int j=-2;j<=2;j++)
	cout << myhi3->binEntries(i,j,0) << " ";
      cout << endl;
    }
  for (int i=-2;i<=2;i++)
    {
      for (int j=-2;j<=2;j++)
	cout << myhi3->binMeanX(i,j,0) << " ";
      cout << endl;
    }
  for (int i=-2;i<=2;i++)
    {
      for (int j=-2;j<=2;j++)
	cout << myhi3->binMeanY(i,j,0) << " ";
      cout << endl;
    }

  IHistogram1D *myhi5 = myhistofactory->createHistogram1D("t3",3,0,1);
  IHistogram1D *myhi6 = myhistofactory->createHistogram1D("t4",3,0,1);
  myhi5->fill(-10.,2);
  myhi5->fill(-10.,2);
  myhi5->fill(0.1,4);
  myhi5->fill(0.4,6);
  myhi5->fill(0.7,8);
  myhi5->fill(10.,10);
  myhi5->fill(10.,10);
  myhi5->fill(10.,10);

  myhi6->fill(-10.,2);
  myhi6->fill(0.3,2);
  myhi6->fill(0.6,2);
  myhi6->fill(0.9,0);
  myhi6->fill(10.,0);

  //  IHistogram1D *myhi8 = myhistofactory->add("added",*myhi6,*myhi6);
  IHistogram1D *myhi7 = myhistofactory->divide("sub",*myhi5,*myhi6);
  //  IHistogram1D *myhi7 = myhistofactory->add("subadd",*myhi9,*myhi8);
  //  IHistogram1DROOT *myhi7 = dynamic_cast<IHistogram1DROOT*>(myhi5);
  //  myhi7->divide(*myhi6);


  for (int i=-3;i<=4;i++)
    cout << myhi5->binHeight(i) << " "; 
  cout << endl;
  for (int i=-3;i<=4;i++)
    cout << myhi5->binError(i) << " "; 
  cout << endl;
  for (int i=-3;i<=4;i++)
    cout << myhi5->binEntries(i) << " ";
  cout << endl;
  for (int i=-3;i<=4;i++)
    cout << myhi5->binMean(i) << " ";
  cout << endl;

  cout 
    << myhi5->coordToIndex(-20) << " " 
    << myhi5->coordToIndex(0.1) << " " 
    << myhi5->coordToIndex(0.5) << " " 
    << myhi5->coordToIndex(0.8) << " " 
    << myhi5->coordToIndex(30) << " " 
    << endl;

  //  mytree->cd("/");
  cout << "u and o bin: " << IAxis::UNDERFLOW_BIN << " " 
       << IAxis::OVERFLOW_BIN << endl;  


  TH1 * achshi = new TH1D("achstest","achstest",100,0.,1.);
  cout << "unten " << achshi->GetXaxis()->GetFirst() << " oben " 
       << achshi->GetXaxis()->GetLast() << endl;
  achshi->GetXaxis()->SetRange(23,56);
  cout << "unten " << achshi->GetXaxis()->GetFirst() << " oben " 
       << achshi->GetXaxis()->GetLast() << endl;

  IHistogram3D *my3d = myhistofactory->createHistogram3D(
      "u2",3,0.5,3.5,3,0.5,3.5,3,0.5,3.5);

  int l = 0 ;
  for (int i=0;i<5;i++)
    {
      for (int j=0;j<5;j++)
	{
	  for (int k=0;k<5;k++)
	    {
	      l++;
	      my3d->fill( (double)k, (double)j, (double)i, (double)l );
	      cout << i << " " << j << " " << k << " " << l << endl;
	    }
	}
    }

  for (int i=-2;i<3;i++)
    {
      for (int j=-2;j<3;j++)
	{
	  for (int k=-2;k<3;k++)
	    {
	      cout << my3d->binHeight(k,j,i) << " ";
	    }
	  cout << " L";
	}
      cout << endl << endl; 
    }

  IHistogram2D *mystueck = myhistofactory->sliceXY("stueck",*my3d,0,0);
  for (int j=-2;j<3;j++)
    {
      for (int i=-2;i<3;i++)
	{
	  //	  cout << mystueck->binHeight(j,i) << " ";
	  cout << mystueck->binEntries(j,i) << " ";
	}
      cout << endl ;
    }

//------------------------------------------------------------------------
        mytree->commit();
  ///      mytree->close();

}

