// used here to call the random number generator.
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>

// includes all AIDA header files
#include <AIDA/AIDA.h>


using namespace AIDA ;
using namespace std;

// ****************************************************************************
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

/// Hook an AIDA implementation -----------------------------------------------

  // First create a pointer to the "IAnalysisFactory" of a specific AIDA
  // implementation. This factory can then be used to produce all other 
  // factories.

  IAnalysisFactory * AF = AIDA_createAnalysisFactory();

// Create a ITreeFactory. -----------------------------------------------------
// A ITree can be used to store AIDA objects in memory or on disk.

  ITreeFactory * TRF = AF->createTreeFactory();

/// Create a ITree object which is bound to a file. ---------------------------
// You must always create a "ITree" object to create any other factory.

  /*
   * Creates a new tree and associates it with a store.
   * The store is assumed to be read/write.
   * The store will be created if it does not exist.
   * @param storeName The name of the store, if empty (""), the tree is 
   *                  created in memory and therefore will not be associated 
   *                  with a file.
   * @param storeType Implementation specific string, may control store type
   * @param readOnly If true the store is opened readonly, an exception if it 
   *                 does not exist
   * @param createNew If false the file must exist, if true the file will be 
   *                  created
   * @param options Other options, currently are not specified
   */
  // ITree * ITreeFactory::create(const std::string & storeName, 
  // 		                  const std::string & storeType = "", 
  //   		                  bool readOnly = false, 
  //		                  bool createNew = false, 
  //		                  const std::string & options = "") ;

  ITree * TREE = TRF->create("RAIDATest.root",
			     "root",
			     false,
			     true);

/// Create an IHistogramFactory which is bound to the tree "*TREE". -----------

  /*
   * Create an IHistogramFactory.
   * @param tree The ITree which created histograms will be associated to.
   * @return     The IHistogramFactory.
   */
  // IHistogramFactory * IAnalysisFactory::createHistogramFactory(ITree & tree);

  IHistogramFactory * HF = AF->createHistogramFactory(*TREE);

/// Create an ITupleFactory which is bound to the tree "*TREE". ---------------

  /*
   * Create an ITupleFactory.
   * @param tree The ITree which created tuples will be associated to.
   * @return     The ITupleFactory.
   */
  // ITupleFactory * IAnalysisFactory::createTupleFactory(ITree & tree);

  ITupleFactory * TUF = AF->createTupleFactory(*TREE);

/// Create some sub-directories to store the histograms, n-tuples etc.
// in a structured way in the file.

  /*
   * Create a new directory. Given a path only the last directory
   * in it is created if all the intermediate subdirectories already exist.
   * @param path The absolute or relative path of the new directory.
   * @return false If a subdirectory within the path does
   *               not exist or it is not a directory. Also if the directory 
   *               already exists.
   */
  // bool ITree::mkdir(const std::string & path);

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
  // (The current directory is "/").

  /*
   * Create a IHistogram1D.
   * @param path      The path of the created IHistogram. The path can either 
   *                  be a relative or full path.
   *                  ("/folder1/folder2/dataName" and 
   *                  "../folder/dataName" are valid paths).
   *                  All the directories in the path must exist. The 
   *                  characther `/` cannot be used in names; it is only 
   *                  used to delimit directories within paths.
   * @param title     The title of the IHistogram1D.
   * @param nBins     The number of bins of the x axis.
   * @param lowerEdge The lower edge of the x axis.
   * @param upperEdge The upper edge of the x axis.
   * @param options   The options for the IHistogram1D. The default is "".
   *                  "type=efficiency" for an efficiency IHistogram1D.
   * @return          The newly created IHistogram1D.
   */
  // IHistogram1D * IHistogramFactory::createHistogram1D(const std::string & path,
  //						         const std::string & title,
  //						         int nBins,
  //						         double lowerEdge,
  //						         double upperEdge,
  //						         const std::string & options = "") ;

  IHistogram1D * H1D_1 = HF->createHistogram1D("histo",
					       "My first Histogram with RAIDA",
					       10, 0., 100.);
  
  IHistogram1D * H1D_2 = HF->createHistogram1D("Histograms/1D/eqd",
					       "equal distribution",
					       20, 0., 100.);

  /*
   * Create a IHistogram1D.
   * @param pathAndTitle The path of the created IHistogram. 
   *                     The last part of the path is used as the title.
   * @param nBins        The number of bins of the x axis.
   * @param lowerEdge    The lower edge of the x axis.
   * @param upperEdge    The upper edge of the x axis.
   * @return             The newly created IHistogram1D.
   */
  // IHistogram1D * IHistogramFactory::createHistogram1D(const std::string & pathAndTitle,
  //                                                     int nBins,
  //                                                     double lowerEdge,
  //                                                     double upperEdge) ;

  IHistogram1D * H1D_3 = HF->createHistogram1D("Histograms/1D/steps",
					       10, 0., 100.);

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

  /*
   * Create a IHistogram1D.
   * @param path      The path of the created IHistogram.
   * @param title     The title of the IHistogram1D.
   * @param binEdges  The array of the bin edges for the x axis.
   * @param options   The options for the IHistogram1D. The default is "".
   *                  "type=efficiency" for an efficiency IHistogram1D.
   * @return          The newly created IHistogram1D.
   */
  // IHistogram1D * IHistogramFactory::createHistogram1D(const std::string & path,
  //                                                     const std::string & title,
  //				                         const std::vector<double>  & binEdges,
  //				                         const std::string & options = "") ;

  IHistogram1D * H1D_4 = HF->createHistogram1D("Histograms/1D/vbin",
					       "Variable binning",
					       bins);

  // Change the directory:

  /*
   * Change to a given directory.
   * @param path The absolute or relative path of the directory we are 
   *             changing to.
   * @return false If the path does not exist.
   */
  // bool ITree::cd(const std::string & path) ;

  TREE->cd("Histograms/2D");

  // Create a 2D histogram with relative path

  /*
   * Create a IHistogram2D.
   * @param path       The path of the created IHistogram.
   * @param title      The title of the IHistogram2D.
   * @param nBinsX     The number of bins of the x axis.
   * @param lowerEdgeX The lower edge of the x axis.
   * @param upperEdgeX The upper edge of the x axis.
   * @param nBinsY     The number of bins of the y axis.
   * @param lowerEdgeY The lower edge of the y axis.
   * @param upperEdgeY The upper edge of the y axis.
   * @param options    The options for the IHistogram2D. The default is "".
   *                   "type=efficiency" for an efficiency IHistogram2D.
   * @return           The newly created IHistogram2D.
   */
  // IHistogram2D * IHistogramFactory::createHistogram2D(const std::string & path,
  //  //						 const std::string & title,
  //						         int nBinsX,
  //						         double lowerEdgeX,
  //						         double upperEdgeX,
  //						         int nBinsY,
  //						         double lowerEdgeY,
  //						         double upperEdgeY,
  //						         const std::string & options = "") ;

  IHistogram2D * H2D_1 = HF->createHistogram2D("flat",
					       "flat distribution",
					       10, 0., 100.,
					       10, 0., 100.);


  // Change the directory:
  TREE->cd("../3D");

  // Create a 3D histogram with relative path

  /**
   * Create a IHistogram3D.
   * @param path       The path of the created IHistogram. 
   * @param title      The title of the IHistogram3D.
   * @param nBinsX     The number of bins of the x axis.
   * @param lowerEdgeX The lower edge of the x axis.
   * @param upperEdgeX The upper edge of the x axis.
   * @param nBinsY     The number of bins of the y axis.
   * @param lowerEdgeY The lower edge of the y axis.
   * @param upperEdgeY The upper edge of the y axis.
   * @param nBinsZ     The number of bins of the z axis.
   * @param lowerEdgeZ The lower edge of the z axis.
   * @param upperEdgeZ The upper edge of the z axis.
   * @param options    The options for the IHistogram3D. The default is "".
   *                   "type=efficiency" for an efficiency IHistogram3D.
   * @return           The newly created IHistogram3D.
   */
  // IHistogram3D * IHistogramFactory::createHistogram3D(const std::string & path,
  //   						         const std::string & title,
  //	   					         int nBinsX,
  //		   				         double lowerEdgeX,
  //			   			         double upperEdgeX,
  //				   		         int nBinsY,
  //					   	         double lowerEdgeY,
  //						         double upperEdgeY,
  //						         int nBinsZ,
  //						         double lowerEdgeZ,
  //						         double upperEdgeZ,
  //						         const std::string & options = "");

  IHistogram3D * H3D_1 = HF->createHistogram3D("cube",
					       "a nice die",
					       10, 0., 100.,
					       10, 0., 100.,
					       10, 0., 100.);

/// Fill the histograms with random numbers -----------------------------------

// initialise random number generator

  srand( time(NULL) );

  // 1D Histograms:

  for (int i = 0; i<100000; i++)
    {
      /**
       * Fill the IHistogram1D with a value and the
       * corresponding weight.
       * @param x      The value to be filled in.
       * @param weight The corresponding weight (by default 1).
       * @return false If the weight is <0.
       */
      // bool IHistogram1D::fill(double x, double weight = 1.);

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
      /**
       * Fill the IHistogram2D with a couple of values and the
       * corresponding weight.
       * @param x      The x value to be filled in.
       * @param y      The y value to be filled in.
       * @param weight The corresponding weight (by default 1).
       * @return false If the weight is <0.
       */
      // bool IHistogram2Dfill(double x, double y, double weight = 1.);

      H2D_1->fill( (double)(rand() % 110) -5,   // x-value
		   (double)(rand() % 110) -5,   // y-value
		   2.);                         // weight

      /**
       * Fill the IHistogram3D with a triplet of values and the
       * corresponding weight.
       * @param x      The x value to be filled in.
       * @param y      The y value to be filled in.
       * @param z      The z value to be filled in.
       * @param weight The corresponding weight (by default 1).
       * @return false If the weight is <0.
       */
      // bool IHistogram3Dfill(double x, double y, double z, double weight = 1.);

      H3D_1->fill((double)(rand() % 110) -5,        // x-value
		  (double)(rand() % 110) -5,        // y-value
		  (double)(rand() % 110) -5,        // z-value
		  (double)(rand() % 10000)/5000. ); // weight
    }

/// Create some profile histograms --------------------------------------------

  // 1D profile histograms

  /**
   * Create a IProfile1D.
   * @param path       The path of the created IProfile. 
   * @param title      The title of the IProfile1D.
   * @param nBins      The number of bins of the x axis.
   * @param lowerEdge  The lower edge of the x axis.
   * @param upperEdge  The upper edge of the x axis.
   * @param lowerValue The lower value displayed along the y axis.
   * @param upperValue The upper value displayed along the y axis.
   * @param options    The options for the IProfile1D. The default is "".
   * @return           The newly created IProfile1D.
   */
  // IProfile1D * IHistogramFactory::createProfile1D(const std::string & path,
  //						     const std::string & title,
  //						     int nBins,
  //						     double lowerEdge,
  //						     double upperEdge,
  //						     double lowerValue,
  //						     double upperValue,
  //						     const std::string & options = "");

  IProfile1D * P1D_1 = HF->createProfile1D("/ProfileHistograms/1D/profile",
					   "my first profilehistogram with RAIDA",
					   10, 0., 100.,
					   10., 20.);

  TREE->cd("/ProfileHistograms/1D");

  /**
   * Create a IProfile1D.
   * @param pathAndTitle The path of the created created IProfile. The path 
   *                     can either be a relative or full path.
   *                     The last part of the path is used as the title.
   * @param nBins        The number of bins of the x axis.
   * @param lowerEdge    The lower edge of the x axis.
   * @param upperEdge    The upper edge of the x axis.
   * @return             The newly created IProfile1D.
   */
  // IProfile1D * IHistogramFactory::createProfile1D(const std::string & pathAndTitle,
  //                                                 int nBins,
  //                                                 double lowerEdge,
  //                                                 double upperEdge) ;

  IProfile1D * P1D_2 = HF->createProfile1D("moreProfiles",
					   20, 0., 100.);

  /**
   * Create a IProfile1D.
   * @param path      The path of the created IProfile. 
   * @param title     The title of the IProfile1D.
   * @param binEdges  The array of the bin edges for the x axis.
   * @param options   The options for the IProfile1D. The default is "".
   * @return          The newly created IProfile1D.
   */
  // IProfile1D * IHistogramFactorycreateProfile1D(const std::string & path,
  //			                           const std::string & title,
  //			                           const std::vector<double>  & binEdges,
  //			                           const std::string & options = "");

  IProfile1D * P1D_3 = HF->createProfile1D("varBinning",
					   "variable binning of profile histogram",
					   bins);


  // 2D profile histograms

  TREE->cd("/ProfileHistograms/2D");

  /**
   * Create a IProfile2D.
   * @param path       The path of the created IProfile. 
   * @param title      The title of the IProfile2D.
   * @param nBinsX     The number of bins of the x axis.
   * @param lowerEdgeX The lower edge of the x axis.
   * @param upperEdgeX The upper edge of the x axis.
   * @param nBinsY     The number of bins of the y axis.
   * @param lowerEdgeY The lower edge of the y axis.
   * @param upperEdgeY The upper edge of the y axis.
   * @param lowerValue The lower value displayed along the z axis.
   * @param upperValue The upper value displayed along the z axis.
   * @param options    The options for the IProfile2D. The default is "".
   * @return           The newly created IProfile2D.
   */
  // IProfile2D * IHistogramFactory::createProfile2D(const std::string & path,
  //						     const std::string & title,
  //						     int nBinsX,
  //						     double lowerEdgeX,
  //						     double upperEdgeX,
  //						     int nBinsY,
  //						     double lowerEdgeY,
  //						     double upperEdgeY,
  //						     double lowerValue,
  //						     double upperValue,
  //						     const std::string & options = "");

  IProfile2D * P2D_1 = HF->createProfile2D("myprofile2D",
					   "a 2D profile histogram",
					   10, 0., 100., 
					   10, 0., 100., 
					   30., 70.);


/// Fill the profile histograms with random numbers ---------------------------

  for (int i=0; i<100000; i++)
    {
      // 1D profile histograms

      /**
       * Fill the IProfile1D with a couple of values and the
       * corresponding weight.
       * @param x      The x value to be filled in.
       * @param y      The y value to be filled in.
       * @param weight The corresponding weight (by default 1).
       * @return false If the weight is <0.
       */
      // bool IProfile1D::fill(double x, double y, double weight = 1) ;

      P1D_1->fill( (double)(rand() % 110) -5,       // x-values
		   (double)(rand() % 30),           // y-values
		   (double)(rand() % 10000)/5000.); // weight
      P1D_2->fill( (double)(rand() % 110) -5,       // x-values
		   (double)(rand() % 50),           // y-values
		   (double)(rand() % 10000)/5000.); // weight
      P1D_3->fill( (double)(rand() % 70) -5,        // x-values
		   (double)(rand() % 50),           // y-values
		   (double)(rand() % 10000)/5000.); // weight


      // 2D profile histograms

      /**
       * Fill the IProfile2D with a triplet of values and the
       * corresponding weight.
       * @param x      The x value to be filled in.
       * @param y      The y value to be filled in.
       * @param z      The z value to be filled in.
       * @param weight The corresponding weight (by default 1).
       * @return false If the weight is <0.
       */
      // bool IProfile1D::fill(double x, double y, double z, double weight = 1) ;

      P2D_1->fill( (double)(rand() % 110) -5,        // x-values
		   (double)(rand() % 110) -5,        // y-values
		   (double)(rand() % 90),            // z-values
		   (double)(rand() % 10000)/5000.); // weight
    }

/// Create some cloudes -------------------------------------------------------

  // 1D cloudes 
  TREE->cd("/Cloudes/1D");

  /**
   * Create a ICloud1D, an unbinned 1-dimensional histogram.
   * @param path    The path of the created ICloud. 
   * @param title   The title of the ICloud1D.
   * @param nMax    The maximum number of entries after which the ICloud1D
   *                will convert to an IHistogram1D. The default nMax = -1 
   *                means no autoconversion.
   * @param options The options for the ICloud1D. 
   * @return        The newly created ICloud1D.
   */
  // virtual ICloud1D * IHistogramFactory::createCloud1D(const std::string & path,
  //						         const std::string & title,
  //						         int nMax = -1,
  //						         const std::string & options = "");

  ICloud1D * C1D_1 = HF->createCloud1D("Cloud",
				       "my first cloud",
				       -1);

  ICloud1D * C1D_2 = HF->createCloud1D("numbers",          // name
				       "set of numbers",   // title
				       1000);              // The maximum number of entries after which the ICloud1D will convert to an IHistogram1D. The default nMax = -1 means no autoconversion.

  ICloud1D * C1D_3 = HF->createCloud1D("flat",              // name
				       "flat distribution", // title
				       -1);                 // The maximum number of entries after which the ICloud1D will convert to an IHistogram1D. The default nMax = -1 means no autoconversion.

  // 2D and 3D cloudes 
  TREE->cd("/Cloudes/2D");

  /**
   * Create a ICloud2D, an unbinned 2-dimensional histogram.
   * @param path    The path of the created ICloud. 
   * @param title   The title of the ICloud2D.
   * @param nMax    The maximum number of entries after which the ICloud2D
   *                will convert to an IHistogram2D. The default nMax = -1 
   *                means no autoconversion.
   * @param options The options for the ICloud2D. 
   * @return        The newly created ICloud2D.
   */
  // virtual ICloud2D * IHistogramFactory::createCloud2D(const std::string & path,
  //						         const std::string & title,
  //						         int nMax = -1,
  //						         const std::string & options = "");

  ICloud2D * C2D_1 = HF->createCloud2D("another",
				       "this is an other cloud",
				       -1);

  ICloud3D * C3D_1 = HF->createCloud3D("more",
				       "more cloud", 
				       -1);

/// Fill the cloudes with random numbers --------------------------------------

  for (int i=0; i<100000; i++)
    {
      // 1D cloudes

      /**
       * Fill the ICloud1D with a value and a corresponding weight.
       * @param x      The value.
       * @param weight The corresponding weight. By default it is 1.
       * @return false If the weight's value is <0. 
       */
      // bool ICloud1D::fill(double x, double weight = 1.);

      C1D_1->fill( (double)(rand() % 1000),  // x-value 
		   1.);                      // weight
      C1D_2->fill( (double)(rand() % 1000),  // x-value 
		   1.);                      // weight
      C1D_3->fill( (double)(rand() % 1000),           // x-value 
		   (double)(rand() % 10000)/5000.  ); // weight

      // 2D cloudes

      /**
       * Fill the ICloud2D with a couple of values and a corresponding weight.
       * @param x      The x value.
       * @param y      The y value.
       * @param weight The corresponding weight. By default it is 1.
       * @return false If the weight's value is <0.
       */
      // virtual bool ICloud2D::fill(double x, double y, double weight = 1.) ;

      C2D_1->fill( (double)(rand() % 1000),           // x-value 
		   (double)(rand() % 1000),           // y-value
		   (double)(rand() % 10000)/5000.  ); // weight

      // 3D cloudes

      /**
       * Fill the ICloud3D with a triplet of values and a corresponding weight.
       * @param x      The x value.
       * @param y      The y value.
       * @param z      The z value.
       * @param weight The corresponding weight. By default it is 1.
       * @return false If the ICloud3D is full, if the weight's value is
       *                                  is not between 0 and 1.
       *
       */
      // virtual bool ICloud3D::fill(double x, double y, double z, 
      //                             double weight = 1.);

      C3D_1->fill( (double)(rand() % 1000),           // x-value 
		   (double)(rand() % 1000),           // y-value
		   (double)(rand() % 1000),           // z-value
		   (double)(rand() % 10000)/5000.  ); // weight
    }

/// Create and fill n-tuples --------------------------------------------------

  TREE->cd("/N-Tuples");

  /**
   * Creates an NTuple
   * @param path    The path of the created ITuple. 
   * @param title   The title of the n-tuple
   * @param columns The names and types of the columns e.g. "float px, py, pz,
   *                float energy, int charge"
   * @param options NTuple options (currently undefined)
   */
  // virtual ITuple * ITupleFactory::create(const std::string & path,
  //                                        const std::string & title,
  //                                        const std::string & columns,
  //                                        const std::string & options = "") = 0;

  ITuple * ntu_1 = TUF->create("nt1",
			       "my first n-tuple",
			       "int id, bool student, int age, float size, double weight");

  for (int i=0; i<40000; i++)
    {
      int age = (rand() % 100) +4;
      bool student = false;
      float size;
      double weight;

      if (age < 5) 
	{
	  student = false;
	  size = (double)(rand() % 3500)/10000 +0.8;
	  weight = (double)(rand() % 2000)/100 +20;
	}
      else if (age == 5)
	{
	  if ((double)(rand() % 100) < 20) student = true;
	  size = (double)(rand() % 2500)/10000 +1.0;
	  weight = (double)(rand() % 2000)/100 +25;
	}
      else if (age >= 6 && age < 20) 
	{
	  student = true;
	  size = (double)(rand() % 6000)/10000 +1.2;
	  weight = (double)(rand() % 2000)/100 +40;
	}
      else if (age >= 20 && age < 25) 
	{
	  if ((double)(rand() % 100) < 30) student = true;
	  size = (double)(rand() % 6000)/10000 +1.5;
	  weight = (double)(rand() % 2500)/100 +50;
	}
      else if (age >= 25 && age < 31) 
	{
	  if ((double)(rand() % 100) < 20) student = true;
	  size = (double)(rand() % 6000)/10000 +1.5;
	  weight = (double)(rand() % 3500)/100 +50;
	}
      else 
	{
	  student = false;
	  size = (double)(rand() % 5000)/10000 +1.5;
	  weight = (double)(rand() % 4500)/100 +50;
	}

      /*
       * Fill a given column with data.
       * @param column The column's index within the ITuple.
       * @param value  The value to fill.
       * @return false If the column is of the wrong type.
       *
       */
      // bool fill(int column, int value) ;
      // bool fill(int column, bool value) ;
      // bool fill(int column, float value) ;
      // bool fill(int column, double value) ;
      // bool fill(int column, short value) ;
      // bool fill(int column, long value) ;
      // bool fill(int column, char value) ;
      // ...

      ntu_1->fill(0,i);
      ntu_1->fill(1,student);
      ntu_1->fill(2,age);
      ntu_1->fill(3,size);
      ntu_1->fill(4,weight);

      /*
       * Add the current row to the ITuple. This method should be called after
       * fill has been called for the columns; unfilled columns will be filled
       * with their default value.
       * @return false When the ITuple runs out of storage space.
       *
       */
      // bool addRow() ;

      ntu_1->addRow();
    }



/// Save the Objects to the file ----------------------------------------------

  /*
   * Commit any open transaction to the underlying store(s).
   * It flushes objects into the disk for non-memory-mapped stores.
   * @return false If the underlying store cannot be written out.
   */
  // bool commit();

  TREE->commit();
  TREE->cd("/Histograms");
  TREE->ls("..");

/// Close the file ------------------------------------------------------------

  /*
   * Closes the underlying store.
   * Changes will be saved only if commit() has been called before.
   * @return false If there are problems writing out
   *         the underlying store.
   */
  // bool close() ;

  TREE->close();

  return 0;
}
