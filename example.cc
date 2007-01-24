#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include <AIDA/AIDA.h>


using namespace AIDA ;
using namespace std;

int main()
{
  cout << "###############################################################################" << endl
       << "#" << endl
       << "# R A I D A   Test Program v00.00" << endl
       << "#" << endl
       << "# This small example program shows how to use the ROOT implementation" << endl
       << "# of the Abstract Interfaces for Data Analysis (AIDA). Further information" << endl
       << "# about AIDA and a description of the interface can be found on the web" << endl
       << "# page of AIDA: http://aida.freehep.org/." << endl
       << "#" << endl
       << "###############################################################################" << endl;

// First create a pointer to the "IAnalysisFactory". This factory can 
// then be used to produce all other factories.

  IAnalysisFactory * AF = AIDA_createAnalysisFactory();

// Now create a "ITreeFactory", which can be used to create and open 
// an output file to store histogram and n-tuple data. 

  ITreeFactory * TRF = AF->createTreeFactory();

/// Create a "ITree" object which is bound to a file. -------------------------
// You must always create a "ITree" object to create any other factory.

  string storeName("RAIDATest.root");
  string storeType("root");
  bool readOnly = false;
  bool createNew = true;
  string options("");

  ITree * TREE = TRF->create(storeName,storeType,readOnly,createNew,options);

/// Create a "IHistogramFactory" which is bound to the tree "*TREE". 

  IHistogramFactory * HF = AF->createHistogramFactory(*TREE);

/// Create a "ITupleFactory" which is bound to the tree "*TREE". 

  ITupleFactory * TUF = AF->createTupleFactory(*TREE);

/// Create some sub-directories to store the histograms, n-tuples etc.
// in a structured way in the file.

  TREE->mkdir("Histograms");
  TREE->mkdir("Histograms/1D");
  TREE->mkdir("Histograms/2D");
  TREE->mkdir("Histograms/3D");

  TREE->mkdir("ProfileHistograms");
  TREE->mkdir("ProfileHistograms/1D");
  TREE->mkdir("ProfileHistograms/2D");

  TREE->mkdir("Cloudes");
  TREE->mkdir("Cloudes/1D");
  TREE->mkdir("Cloudes/2D");
  TREE->mkdir("Cloudes/3D");

  TREE->mkdir("N-Tuples");

// Create a bunch of different histograms. ------------------------------------

  // Specify the absolut path of the objects
  // (The current directory is "/").
  
  string name = "histo";
  string title = "My first Histogram with RAIDA";
  int nBins = 10;
  double lowerEdge = 0;
  double upperEdge = 100;
  
  IHistogram1D * H1D_1 = HF->createHistogram1D(name,title,
					       nBins,lowerEdge,upperEdge);
  
  string path = "Histograms/1D/eqd"; 
  
  IHistogram1D * H1D_2 = HF->createHistogram1D(path,"equal distribution",
					       20,0,100);
  
  string pathandtitle = "Histograms/1D/steps";
  
  IHistogram1D * H1D_3 = HF->createHistogram1D(pathandtitle,10,0,100);

  // Create a 1D Histogram with variable binning.

  vector<double> bins;
  bins.push_back(0.);
  bins.push_back(10);
  bins.push_back(20);
  bins.push_back(22);
  bins.push_back(24);
  bins.push_back(25);
  bins.push_back(26);
  bins.push_back(28);
  bins.push_back(30);
  bins.push_back(40);
  bins.push_back(50);

  IHistogram1D * H1D_4 = HF->createHistogram1D("Histograms/1D/vbin","Variable binning",bins);

  // Change the directory:
  TREE->cd("Histograms/2D");

  // Create a histogram by specifying a relative path. 

  name = "flat";
  title = "flat distribution";
  int nBinsX = 10;
  double lowerEdgeX = 0;
  double upperEdgeX = 100;
  int nBinsY = 10;
  double lowerEdgeY = 0;
  double upperEdgeY = 100;

  IHistogram2D * H2D_1 = HF->createHistogram2D(name,title,
					       nBinsX,lowerEdgeX,upperEdgeX,
					       nBinsY,lowerEdgeY,upperEdgeY);

  // Change the directory:
  TREE->cd("../3D");

  // Create a 3D histogram with relative path

  name = "cube";
  title = "a nice die";
  nBinsX = 10;
  lowerEdgeX = 0;
  upperEdgeX = 100;
  nBinsY = 10;
  lowerEdgeY = 0;
  upperEdgeY = 100;
  int nBinsZ = 10;
  double lowerEdgeZ = 0;
  double upperEdgeZ = 100;

  IHistogram3D * H3D_1 = HF->createHistogram3D(name,title,
					       nBinsX,lowerEdgeX,upperEdgeX,
					       nBinsY,lowerEdgeY,upperEdgeY,
					       nBinsZ,lowerEdgeZ,upperEdgeZ);


/// Fill the histograms with random numbers -----------------------------------

// initialise random number generator

  srand(time(NULL));

  // 1D Histograms:
  for (int i = 0; i<100000; i++)
    {
      H1D_1->fill( (double)(rand() % 100) );
      H1D_2->fill( (double)(rand() % 120) -10 );

      H1D_3->fill( (double)(rand() % 100) );
      H1D_3->fill( (double)(rand() % 90) +9 );
      H1D_3->fill( (double)(rand() % 80) +19 );
      H1D_3->fill( (double)(rand() % 70) +29 );
      H1D_3->fill( (double)(rand() % 60) +39 );
      H1D_3->fill( (double)(rand() % 50) +49 );
      H1D_3->fill( (double)(rand() % 40) +59 );
      H1D_3->fill( (double)(rand() % 30) +69 );
      H1D_3->fill( (double)(rand() % 20) +79 );
      H1D_3->fill( (double)(rand() % 10) +89 );

      H1D_4->fill( (double)(rand() % 60) -5  );
    }

  // 2D and 3D Histograms:
  for (int i=0; i<100000; i++)
    {
      // all weights are 2
      H2D_1->fill( (double)(rand() % 110) -5,(double)(rand() % 110) -5,2.);
      // random weights
      H3D_1->fill((double)(rand() % 110) -5,
		  (double)(rand() % 110) -5,
		  (double)(rand() % 110) -5,
		  (double)(rand() % 10000)/5000. );
    }

/// Create some profile histograms --------------------------------------------




/// Save the Objects to the file ----------------------------------------------
  TREE->commit();
  TREE->cd("/Histograms");
  TREE->ls("..");

/// Close the file ------------------------------------------------------------
  TREE->close();

  return 0;
}

