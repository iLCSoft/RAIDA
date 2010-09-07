// #include <RAIDA/IHistogramROOT.h>
#include <RAIDA/IAxisROOT.h>
#include <RAIDA/IProfile1DROOT.h>
#include <RAIDA/IProfile2DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/ICloud1DROOT.h>
#include <RAIDA/ICloud2DROOT.h>
#include <RAIDA/ICloud3DROOT.h>
#include <RAIDA/IHistogramFactoryROOT.h>
#include <RAIDA/PathName.h>
#include <RAIDA/AIDAHistogramsInROOT.h>
#include <RAIDA/RAIDAUtil.h>
#include <TH1D.h>
#include <TH2D.h>

using namespace AIDA ;
using namespace std;

// nMax is for some Constructors of ICloud
const int IHistogramFactoryROOT::_nMaxDefault = -1;


IHistogramFactoryROOT::IHistogramFactoryROOT(ITree & tree)
{
  _usedTree = &tree;
}

// default consturctor needed to initialise _usedTree pointer correctly
IHistogramFactoryROOT::IHistogramFactoryROOT()
    : _usedTree(0)
{
}

IHistogramFactoryROOT::~IHistogramFactoryROOT()
{
    // do not write to file, i.e. do not call _usedTree->commit()
    // this only should happen if explicitly called by user
  
    // itterate on all histos in the set and delete them
    for (std::set<IBaseHistogram *>::iterator setIter = _histosInThisFactory.begin();
	     setIter != _histosInThisFactory.end(); setIter++  ) 
    {
	delete *setIter;
    }
}

bool IHistogramFactoryROOT::destroy(IBaseHistogram * hist)
{

    // check if the pointer is valid
    // if it is not in the set deleting it would cause a segfault
    if (_histosInThisFactory.find(hist) == _histosInThisFactory.end() )
    {
	return false;
    }

    // if the histo is there, delete it and remove the pointer from the set
    delete hist;
    _histosInThisFactory.erase(hist);
    
    return true;
}

IHistogram1D * IHistogramFactoryROOT::createHistogram1D(
               const std::string & path, 
               const std::string & title, 
               int nBins, 
               double lowerEdge, 
               double upperEdge, 
               const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D histogram with equal binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBins: " << nBins 
       << " lowerEdge: " << lowerEdge 
       << " upperEdge: " << upperEdge << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram1DROOT* histo = new IHistogram1DROOT(thePath.getName(),
					       title,nBins,lowerEdge,upperEdge,
					       options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);

  return histo;
}

IHistogram1D * IHistogramFactoryROOT::createHistogram1D
                                            (const std::string & pathAndTitle,
					     int nBins,
					     double lowerEdge,
					     double upperEdge) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram1D(const std::string & pathAndTitle,int nBins,double lowerEdge,double upperEdge): " << endl;
  cout << "          " 
       << "Creates a 1D histogram" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createHistogram1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,const std::string & options)" << endl << endl;
#endif

  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createHistogram1D(pathAndTitle,thePath.getName(),
			   nBins,lowerEdge,upperEdge);
}

IHistogram1D * IHistogramFactoryROOT::createHistogram1D(const std::string & path,
							const std::string & title,
							const std::vector<double>  & binEdges,
							const std::string & options) 
{ // ###
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram1D(const std::string & path,const std::string & title,const std::vector<double>  & binEdges,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdges.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << binEdges.size() 
       << " lowerEdge: " << binEdges[0] 
       << " upperEdge: " << binEdges[binEdges.size()-1] << endl;
  cout << "          "
       << "lower edge of bins:" ;
  for (int i=0 ; i<=binEdges.size()-1;i++)
    cout << " " << i << ": " << binEdges[i] ;
  cout << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);

  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdges))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram1DROOT* histo = new IHistogram1DROOT(thePath.getName(),
						 title,binEdges,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);

  return histo;
}

IHistogram1D * IHistogramFactoryROOT::createCopy(const std::string & path,
						 const IHistogram1D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram1D & hist):" << endl;
  cout << "          "
       << "Create a new 1D histogram from an other 1D histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          " 
       << "nBins: " << hist.axis().bins() 
       << " lowerEdge: " << hist.axis().lowerEdge()
       << " upperEdge: " << hist.axis().upperEdge() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram1DROOT* phist = dynamic_cast<const IHistogram1DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram1DROOT* histogram = new IHistogram1DROOT(thePath.getName(),
						     *phist) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);

  return histogram;
} 

IHistogram2D * IHistogramFactoryROOT::createHistogram2D(
                                      const std::string & path,
				      const std::string & title,
				      int nBinsX,
				      double lowerEdgeX,
				      double upperEdgeX,
				      int nBinsY,
				      double lowerEdgeY,
				      double upperEdgeY,
				      const std::string & options) 
{ 
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D histogram2D" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBinsX: " << nBinsX 
       << " lowerEdgeX: " << lowerEdgeX 
       << " upperEdgeX: " << upperEdgeX << endl;
  cout << "          " 
       << "nBinsY: " << nBinsY 
       << " lowerEdgeY: " << lowerEdgeY 
       << " upperEdgeY: " << upperEdgeY << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram2DROOT* histo = new IHistogram2DROOT(thePath.getName(),
						 title,
						 nBinsX,lowerEdgeX,upperEdgeX,
						 nBinsY,lowerEdgeY,upperEdgeY,
						 options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IHistogram2D * IHistogramFactoryROOT::createHistogram2D(const std::string & pathAndTitle,
							int nBinsX,
							double lowerEdgeX,
							double upperEdgeX,
							int nBinsY,
							double lowerEdgeY,
							double upperEdgeY) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram2D(const std::string & pathAndTitle,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY):" << endl; 
  cout << "          " 
       << "Creates a 2D histogram" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createHistogram2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,const std::string & options)" << endl << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createHistogram2D(pathAndTitle,thePath.getName(),
                           nBinsX,lowerEdgeX,upperEdgeX,
                           nBinsY,lowerEdgeY,upperEdgeY);
}

IHistogram2D * IHistogramFactoryROOT::createHistogram2D(const std::string & path,
							const std::string & title,
							const std::vector<double>  & binEdgesX,
							const std::vector<double>  & binEdgesY,
							const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram2D(const std::string & path,const std::string & title,const std::vector<double>  & binEdgesX,const std::vector<double>  & binEdgesY,const std::string & options):" << endl;
    cout << "          "
       << "Create a new 2D histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdgesX.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of x-axis to small!" << endl;
#endif
      return NULL;
    }

  if (binEdgesY.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of y-axis to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << binEdgesX.size() 
       << " lowerEdgeX: " << binEdgesX[0] 
       << " upperEdgeX: " << binEdgesX[binEdgesX.size()-1] << endl;
  cout << "          " 
       << "nBinsY: " << binEdgesY.size() 
       << " lowerEdgeY: " << binEdgesY[0] 
       << " upperEdgeY: " << binEdgesY[binEdgesY.size()-1] << endl;
  cout << "          "
       << "lower edge of x-bins:" ;
  for (int i=0 ; i<=binEdgesX.size()-1;i++)
    cout << " " << i << ": " << binEdgesX[i] ;
  cout << endl;
  cout << "          "
       << "lower edge of y-bins:" ;
  for (int i=0 ; i<=binEdgesY.size()-1;i++)
    cout << " " << i << ": " << binEdgesY[i] ;
  cout << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesX))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the x-axis!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesY))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the y-axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram2DROOT* histo = new IHistogram2DROOT(thePath.getName(),
						 title,
						 binEdgesX,binEdgesY,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IHistogram2D * IHistogramFactoryROOT::createCopy(const std::string & path,
						 const IHistogram2D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram2D & hist):" << endl;
  cout << "          "
       << "Create a new 2d histogram from an other 2D histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          " 
       << "nBinsX: " << hist.xAxis().bins() 
       << " lowerEdgeX: " << hist.xAxis().lowerEdge()
       << " upperEdgeX: " << hist.xAxis().upperEdge() << endl;
  cout << "          " 
       << "nBinsY: " << hist.yAxis().bins() 
       << " lowerEdgeY: " << hist.yAxis().lowerEdge()
       << " upperEdgeY: " << hist.yAxis().upperEdge() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram2DROOT* phist = dynamic_cast<const IHistogram2DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram2DROOT* histogram = new IHistogram2DROOT(thePath.getName(),
						     *phist) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}

IHistogram3D * IHistogramFactoryROOT::createHistogram3D
                                      (const std::string & path,
                                       const std::string & title,
                                       int nBinsX,
                                       double lowerEdgeX,
                                       double upperEdgeX,
                                       int nBinsY,
                                       double lowerEdgeY,
                                       double upperEdgeY,
                                       int nBinsZ,
                                       double lowerEdgeZ,
                                       double upperEdgeZ,
                                       const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram3D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,int nBinsZ,double lowerEdgeZ,double upperEdgeZ,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 3D histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBinsX: " << nBinsX 
       << " lowerEdgeX: " << lowerEdgeX 
       << " upperEdgeX: " << upperEdgeX << endl;
  cout << "          " 
       << "nBinsY: " << nBinsY 
       << " lowerEdgeY: " << lowerEdgeY 
       << " upperEdgeY: " << upperEdgeY << endl;
  cout << "          " 
       << "nBinsZ: " << nBinsZ 
       << " lowerEdgeZ: " << lowerEdgeZ 
       << " upperEdgeZ: " << upperEdgeZ << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram3DROOT* histo = new IHistogram3DROOT(thePath.getName(),
						 title,
						 nBinsX,lowerEdgeX,upperEdgeX,
						 nBinsY,lowerEdgeY,upperEdgeY,
						 nBinsZ,lowerEdgeZ,upperEdgeZ,
						 options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IHistogram3D * IHistogramFactoryROOT::createHistogram3D(const std::string & pathAndTitle,
							int nBinsX,
							double lowerEdgeX,
							double upperEdgeX,
							int nBinsY,
							double lowerEdgeY,
							double upperEdgeY,
							int nBinsZ,
							double lowerEdgeZ,
							double upperEdgeZ) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram3D(const std::string & pathAndTitle,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,int nBinsZ,double lowerEdgeZ,double upperEdgeZ): " << endl;
  cout << "          "
       << "Creates a 3D histogram" << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::createHistogram3D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,int nBinsZ,double lowerEdgeZ,double upperEdgeZ,const std::string & options):" << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          " 
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createHistogram3D(pathAndTitle,thePath.getName(),
                           nBinsX,lowerEdgeX,upperEdgeX,
                           nBinsY,lowerEdgeY,upperEdgeY,
                           nBinsZ,lowerEdgeZ,upperEdgeZ);
}

IHistogram3D * IHistogramFactoryROOT::createHistogram3D(const std::string & path,
							const std::string & title,
							const std::vector<double>  & binEdgesX,
							const std::vector<double>  & binEdgesY,
							const std::vector<double>  & binEdgesZ,
							const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createHistogram3D(const std::string & path,const std::string & title,const std::vector<double> & binEdgesX,const std::vector<double> & binEdgesY,const std::vector<double> & binEdgesZ,const std::string & options)" << endl;
  cout << "          "
       << "Create a new 3D histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdgesX.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of x-axis to small!" << endl;
#endif
      return NULL;
    }

  if (binEdgesY.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of y-axis to small!" << endl;
#endif
      return NULL;
    }

  if (binEdgesZ.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of z-axis to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << binEdgesX.size() 
       << " lowerEdgeX: " << binEdgesX[0] 
       << " upperEdgeX: " << binEdgesX[binEdgesX.size()-1] << endl;
  cout << "          " 
       << "nBinsY: " << binEdgesY.size() 
       << " lowerEdgeY: " << binEdgesY[0] 
       << " upperEdgeY: " << binEdgesY[binEdgesY.size()-1] << endl;
  cout << "          " 
       << "nBinsZ: " << binEdgesZ.size() 
       << " lowerEdgeZ: " << binEdgesZ[0] 
       << " upperEdgeZ: " << binEdgesZ[binEdgesZ.size()-1] << endl;
  cout << "          "
       << "lower edge of x-bins:" ;
  for (int i=0 ; i<=binEdgesX.size()-1;i++)
    cout << " " << i << ": " << binEdgesX[i] ;
  cout << endl;
  cout << "          "
       << "lower edge of y-bins:" ;
  for (int i=0 ; i<=binEdgesY.size()-1;i++)
    cout << " " << i << ": " << binEdgesY[i] ;
  cout << endl;
  cout << "          "
       << "lower edge of z-bins:" ;
  for (int i=0 ; i<=binEdgesZ.size()-1;i++)
    cout << " " << i << ": " << binEdgesZ[i] ;
  cout << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesX))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the x-axis!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesY))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the y-axis!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesZ))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the z-axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IHistogram3DROOT* histo = new IHistogram3DROOT(thePath.getName(),
						 title,
						 binEdgesX,binEdgesY,
						 binEdgesZ,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IHistogram3D * IHistogramFactoryROOT::createCopy(const std::string & path,
						 const IHistogram3D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram3D & hist):" << endl;
  cout << "          "
       << "Create a new 3D histogram from an other 3D histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          " 
       << "nBinsX: " << hist.xAxis().bins() 
       << " lowerEdgeX: " << hist.xAxis().lowerEdge()
       << " upperEdgeX: " << hist.xAxis().upperEdge() << endl;
  cout << "          " 
       << "nBinsY: " << hist.yAxis().bins() 
       << " lowerEdgeY: " << hist.yAxis().lowerEdge()
       << " upperEdgeY: " << hist.yAxis().upperEdge() << endl;
  cout << "          " 
       << "nBinsZ: " << hist.zAxis().bins() 
       << " lowerEdgeZ: " << hist.zAxis().lowerEdge()
       << " upperEdgeZ: " << hist.zAxis().upperEdge() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram3DROOT* phist = dynamic_cast<const IHistogram3DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram3DROOT* histogram = new IHistogram3DROOT(thePath.getName(),
						     *phist) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & path,
						    const std::string & title,
						    int nBins,
						    double lowerEdge,
						    double upperEdge,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBins: " << nBins 
       << " lowerEdge: " << lowerEdge 
       << " upperEdge: " << upperEdge << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile1DROOT* histo = new IProfile1DROOT(thePath.getName(),
					     title,
					     nBins,lowerEdge,upperEdge,
					     options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & path,
						    const std::string & title,
						    int nBins,
						    double lowerEdge,
						    double upperEdge,
						    double lowerValue,
						    double upperValue,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,double lowerValue,double upperValue,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBins: " << nBins 
       << " lowerEdge: " << lowerEdge 
       << " upperEdge: " << upperEdge << endl;
  cout << "          " 
       << " lowerValue: " << lowerValue 
       << " upperValue: " << upperValue << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile1DROOT* histo = new IProfile1DROOT(thePath.getName(),
					     title,
					     nBins,lowerEdge,upperEdge,
					     lowerValue,upperValue,
					     options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & pathAndTitle,
						    int nBins,
						    double lowerEdge,
						    double upperEdge) 
{ // xxx---xxx
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & pathAndTitle,int nBins,double lowerEdge,double upperEdge):" << endl;
  cout << "          "  
       << "Creates a 1D profile histogram" << endl;
  cout << "          "  
       << "will call: IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,const std::string & options)" << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createProfile1D(pathAndTitle,thePath.getName(),
			 nBins,lowerEdge,upperEdge);
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & pathAndTitle,
						    int nBins,
						    double lowerEdge,
						    double upperEdge,
						    double lowerValue,
						    double upperValue) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & pathAndTitle,int nBins,double lowerEdge,double upperEdge,double lowerValue,double upperValue):" << endl;
  cout << "          "  
       << "Creates a 1D profile histogram" << endl;
  cout << "          "  
       << "will call: IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,int nBins,double lowerEdge,double upperEdge,double lowerValue,double upperValue,const std::string & options)" << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createProfile1D(pathAndTitle,thePath.getName(),
			 nBins,lowerEdge,upperEdge,lowerValue,upperValue);
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & path,
						    const std::string & title,
						    const std::vector<double>  & binEdges,
						    const std::string & options) 
{ 
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,const std::vector<double>  & binEdges,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D profile histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdges.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << binEdges.size() 
       << " lowerEdge: " << binEdges[0] 
       << " upperEdge: " << binEdges[binEdges.size()-1] << endl;
  cout << "          "
       << "lower edge of bins:" ;
  for (int i=0 ; i<=binEdges.size()-1;i++)
    cout << " " << i << ": " << binEdges[i] ;
  cout << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdges))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile1DROOT* histo = new IProfile1DROOT(thePath.getName(),
					     title,binEdges,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile1D * IHistogramFactoryROOT::createProfile1D(const std::string & path,
						    const std::string & title,
						    const std::vector<double>  & binEdges,
						    double lowerValue,
						    double upperValue,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile1D(const std::string & path,const std::string & title,const std::vector<double>  & binEdges,double lowerValue,double upperValue,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D profile histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdges.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << binEdges.size() 
       << " lowerEdge: " << binEdges[0] 
       << " upperEdge: " << binEdges[binEdges.size()-1] << endl;
  cout << "          "
       << "lower edge of bins:" ;
  for (int i=0 ; i<=binEdges.size()-1;i++)
    cout << " " << i << ": " << binEdges[i] ;
  cout << endl;
  cout << "          " 
       << " lowerValue: " << lowerValue 
       << " upperValue: " << upperValue << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdges))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile1DROOT* histo = new IProfile1DROOT(thePath.getName(),
					     title,binEdges,
					     lowerValue,upperValue,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile1D * IHistogramFactoryROOT::createCopy(const std::string & path,
					       const IProfile1D & profile) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const IProfile1D & profile):" << endl;
  cout << "          "
       << "Create a new 1D profile histogram from an other 1D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << profile.title() << endl;
  cout << "          " 
       << "nBins: " << profile.axis().bins() 
       << " lowerEdge: " << profile.axis().lowerEdge()
       << " upperEdge: " << profile.axis().upperEdge() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IProfile1DROOT* pprof = dynamic_cast<const IProfile1DROOT*>(&profile);
  if (!pprof) return NULL;
  IProfile1DROOT* profhist = new IProfile1DROOT(thePath.getName(),
						 *pprof) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(profhist);
  return profhist;
}


IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & path,
						    const std::string & title,
						    int nBinsX,
						    double lowerEdgeX,
						    double upperEdgeX,
						    int nBinsY,
						    double lowerEdgeY,
						    double upperEdgeY,
						    const std::string & options)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBinsX: " << nBinsX 
       << " lowerEdgeX: " << lowerEdgeX 
       << " upperEdgeX: " << upperEdgeX << endl;
  cout << "          " 
       << "nBinsY: " << nBinsY 
       << " lowerEdgeY: " << lowerEdgeY 
       << " upperEdgeY: " << upperEdgeY << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile2DROOT* histo = new IProfile2DROOT(thePath.getName(),
					     title,
					     nBinsX,lowerEdgeX,upperEdgeX,
					     nBinsY,lowerEdgeY,upperEdgeY,
					     options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & path,
						    const std::string & title,
						    int nBinsX,
						    double lowerEdgeX,
						    double upperEdgeX,
						    int nBinsY,
						    double lowerEdgeY,
						    double upperEdgeY,
						    double lowerValue,
						    double upperValue,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,double lowerValue,double upperValue,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nBinsX: " << nBinsX 
       << " lowerEdgeX: " << lowerEdgeX 
       << " upperEdgeX: " << upperEdgeX << endl;
  cout << "          " 
       << "nBinsY: " << nBinsY 
       << " lowerEdgeY: " << lowerEdgeY 
       << " upperEdgeY: " << upperEdgeY << endl;
  cout << "          " 
       << " lowerValue: " << lowerValue 
       << " upperValue: " << upperValue << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile2DROOT* histo = new IProfile2DROOT(thePath.getName(),
					     title,
					     nBinsX,lowerEdgeX,upperEdgeX,
					     nBinsY,lowerEdgeY,upperEdgeY,
					     lowerValue,upperValue,
					     options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & pathAndTitle,
						    int nBinsX,
						    double lowerEdgeX,
						    double upperEdgeX,
						    int nBinsY,
						    double lowerEdgeY,
						    double upperEdgeY) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & pathAndTitle,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY):" << endl;
  cout << "          "  
       << "Create a 2D profile histogram" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,const std::string & options)" << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createProfile2D(pathAndTitle,thePath.getName(),
			 nBinsX,lowerEdgeX,upperEdgeX,
			 nBinsY,lowerEdgeY,upperEdgeY);
}

IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & pathAndTitle,
						    int nBinsX,
						    double lowerEdgeX,
						    double upperEdgeX,
						    int nBinsY,
						    double lowerEdgeY,
						    double upperEdgeY,
						    double lowerValue,
						    double upperValue) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & pathAndTitle,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,double lowerValue,double upperValue):" << endl;
  cout << "          "  
       << "Create a 2D profile histogram" << endl;
  cout << "          "  
       << "will call: IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,int nBinsX,double lowerEdgeX,double upperEdgeX,int nBinsY,double lowerEdgeY,double upperEdgeY,double lowerValue,double upperValue,const std::string & options)" << endl;  
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  return createProfile2D(pathAndTitle,thePath.getName(),
			 nBinsX,lowerEdgeX,upperEdgeX,
			 nBinsY,lowerEdgeY,upperEdgeY,
			 lowerValue,upperValue);
}

IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & path,
						    const std::string & title,
						    const std::vector<double>  & binEdgesX,
						    const std::vector<double>  & binEdgesY,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,const std::vector<double>  & binEdgesX,const std::vector<double>  & binEdgesY,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D profile histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdgesX.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of x-axis to small!" << endl;
#endif
      return NULL;
    }

  if (binEdgesY.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges of y-axis to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << binEdgesX.size() 
       << " lowerEdgeX: " << binEdgesX[0] 
       << " upperEdgeX: " << binEdgesX[binEdgesX.size()-1] << endl;
  cout << "          " 
       << "nBinsY: " << binEdgesY.size() 
       << " lowerEdgeY: " << binEdgesY[0] 
       << " upperEdgeY: " << binEdgesY[binEdgesY.size()-1] << endl;
  cout << "          "
       << "lower edge of x-bins:" ;
  for (int i=0 ; i<=binEdgesX.size()-1;i++)
    cout << " " << i << ": " << binEdgesX[i] ;
  cout << endl;
  cout << "          "
       << "lower edge of y-bins:" ;
  for (int i=0 ; i<=binEdgesY.size()-1;i++)
    cout << " " << i << ": " << binEdgesY[i] ;
  cout << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesX))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the x-axis!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesY))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the y-axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile2DROOT* histo = new IProfile2DROOT(thePath.getName(),
					     title,binEdgesX,binEdgesY,
					     options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile2D * IHistogramFactoryROOT::createProfile2D(const std::string & path,
						    const std::string & title,
						    const std::vector<double>  & binEdgesX,
						    const std::vector<double>  & binEdgesY,
						    double lowerValue,
						    double upperValue,
						    const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createProfile2D(const std::string & path,const std::string & title,const std::vector<double>  & binEdgesX,const std::vector<double>  & binEdgesY,double lowerValue,double upperValue,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D profile histogram with variable binning" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
#endif

  if (binEdgesX.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges ov x-axis to small!" << endl;
#endif
      return NULL;
    }

  if (binEdgesY.size() <2) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
	   << "number of specified bin edges ov y-axis to small!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << binEdgesX.size() 
       << " lowerEdgeX: " << binEdgesX[0] 
       << " upperEdgeX: " << binEdgesX[binEdgesX.size()-1] << endl;
  cout << "          " 
       << "nBinsY: " << binEdgesY.size() 
       << " lowerEdgeY: " << binEdgesY[0] 
       << " upperEdgeY: " << binEdgesY[binEdgesY.size()-1] << endl;
  cout << "          "
       << "lower edge of x-bins:" ;
  for (int i=0 ; i<=binEdgesX.size()-1;i++)
    cout << " " << i << ": " << binEdgesX[i] ;
  cout << endl;
  cout << "          "
       << "lower edge of y-bins:" ;
  for (int i=0 ; i<=binEdgesY.size()-1;i++)
    cout << " " << i << ": " << binEdgesY[i] ;
  cout << endl;
  cout << "          " 
       << " lowerValue: " << lowerValue 
       << " upperValue: " << upperValue << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesX))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the x-axis!" << endl;
#endif
      return NULL;
    }

  if (!RAIDAUtil::isOrdered(binEdgesY))
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "Bin edges must be ordered along the y-axis!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  IProfile2DROOT* histo = new IProfile2DROOT(thePath.getName(),
					     title,binEdgesX,binEdgesY,
					     lowerValue,upperValue,options) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

IProfile2D * IHistogramFactoryROOT::createCopy(const std::string & path,
					       const IProfile2D & profile) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const IProfile2D & profile):" << endl;
  cout << "          "
       << "Create a new 2D profile histogram from an other 2D profile histogram" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << profile.title() << endl;
  cout << "          " 
       << "nBinsX: " << profile.xAxis().bins() 
       << " lowerEdgeX: " << profile.xAxis().lowerEdge()
       << " upperEdgeX: " << profile.xAxis().upperEdge() << endl;
  cout << "          " 
       << "nBinsY: " << profile.yAxis().bins() 
       << " lowerEdgeY: " << profile.yAxis().lowerEdge()
       << " upperEdgeY: " << profile.yAxis().upperEdge() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IProfile2DROOT* pprof = dynamic_cast<const IProfile2DROOT*>(&profile);
  if (!pprof) return NULL;
  IProfile2DROOT* profhist = new IProfile2DROOT(thePath.getName(),
						 *pprof) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(profhist);
  return profhist;
}

ICloud1D * IHistogramFactoryROOT::createCloud1D(const std::string & path,
						const std::string & title,
						int nMax,
						const std::string & options)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud1D(const std::string & path,const std::string & title,int nMax,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 1D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nMax: " << nMax << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  thePath.changePath( _usedTree->pwd() );

  ICloud1DROOT* histo = new ICloud1DROOT(thePath.getPathName(),
					 title,nMax,_usedTree,options);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

ICloud1D * IHistogramFactoryROOT::createCloud1D(const std::string & pathAndTitle) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud1D(const std::string & pathAndTitle):" << endl;
  cout << "          " 
       << "Create a new 1D cloud" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCloud1D(const std::string & path,const std::string & title,int nMax,const std::string & options)" << endl;
#endif
  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }
  return createCloud1D(pathAndTitle,thePath.getName(),_nMaxDefault,"");
}

ICloud1D * IHistogramFactoryROOT::createCopy(const std::string & path,
					     const ICloud1D & cloud) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const ICloud1D & cloud):" << endl;
  cout << "          "
       << "Create a new 1D cloud from an other 1D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << cloud.title() << endl;
  cout << "          " 
       << "nMax: " << cloud.maxEntries() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  const ICloud1DROOT* pcloud = dynamic_cast<const ICloud1DROOT*>(&cloud);
  if (!pcloud) return NULL;
  ICloud1DROOT* newCloud = new ICloud1DROOT(thePath.getPathName(),
					    _usedTree,*pcloud);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(newCloud);
  return newCloud;
}

ICloud2D * IHistogramFactoryROOT::createCloud2D(const std::string & path,
			          const std::string & title,
			          int nMax,
			          const std::string & options)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud2D(const std::string & path,const std::string & title,int nMax,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 2D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nMax: " << nMax << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  ICloud2DROOT* histo = new ICloud2DROOT(thePath.getPathName(),
					 title,nMax,_usedTree,options);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

ICloud2D * IHistogramFactoryROOT::createCloud2D(const std::string & pathAndTitle) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud2D(const std::string & pathAndTitle):" << endl;
  cout << "          " 
       << "Create a new 2D cloud" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCloud2D(const std::string & path,const std::string & title,int nMax,const std::string & options)" << endl;
#endif

  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }
  return createCloud2D(pathAndTitle,thePath.getName(),_nMaxDefault,"");
}

ICloud2D * IHistogramFactoryROOT::createCopy(const std::string & path,
					     const ICloud2D & cloud)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const ICloud2D & cloud):" << endl;
  cout << "          "
       << "Create a new 2D cloud from an other 2D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << cloud.title() << endl;
  cout << "          " 
       << "nMax: " << cloud.maxEntries() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  const ICloud2DROOT* pcloud = dynamic_cast<const ICloud2DROOT*>(&cloud);
  if (!pcloud) return NULL;
  ICloud2DROOT* newCloud = new ICloud2DROOT(thePath.getPathName(),
					    _usedTree,*pcloud);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(newCloud);
  return newCloud;
}

ICloud3D * IHistogramFactoryROOT::createCloud3D(const std::string & path,
						const std::string & title,
						int nMax,
						const std::string & options)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud3D(const std::string & path,const std::string & title,int nMax,const std::string & options):" << endl;
  cout << "          "
       << "Create a new 3D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << title << endl;
  cout << "          " 
       << "nMax: " << nMax << endl;
  cout << "          "  
       << "options: " << options << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  ICloud3DROOT* histo = new ICloud3DROOT(thePath.getPathName(),
					 title,nMax,_usedTree,options);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histo);
  return histo;
}

ICloud3D * IHistogramFactoryROOT::createCloud3D(const std::string & pathAndTitle) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCloud3D(const std::string & pathAndTitle):" << endl;
  cout << "          " 
       << "Create a new 3D cloud" << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCloud3D(const std::string & path,const std::string & title,int nMax,const std::string & options)" << endl;
#endif

  PathName thePath(pathAndTitle);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }
  return createCloud3D(pathAndTitle,thePath.getName(),_nMaxDefault,"");
}

ICloud3D * IHistogramFactoryROOT::createCopy(const std::string & path,
					     const ICloud3D & cloud) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::createCopy(const std::string & path,const ICloud3D & cloud):" << endl;
  cout << "          "
       << "Create a new 3D cloud from an other 3D cloud" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << cloud.title() << endl;
  cout << "          " 
       << "nMax: " << cloud.maxEntries() << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a Cloud!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the cloud is created: " << _usedTree->pwd() << endl;
    }
#endif

  const ICloud3DROOT* pcloud = dynamic_cast<const ICloud3DROOT*>(&cloud);
  if (!pcloud) return NULL;
  ICloud3DROOT* newCloud = new ICloud3DROOT(thePath.getPathName(),
					    _usedTree,*pcloud);

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(newCloud);
  return newCloud;
}

IHistogram1D * IHistogramFactoryROOT::add(const std::string & path,
					  const IHistogram1D & hist1,
					  const IHistogram1D & hist2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::add(const std::string & path,const IHistogram1D & hist1,const IHistogram1D & hist2):" << endl;
  cout << "          " 
       << "Add two 1D histograms (hist1 + hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if ( hist1.axis().bins() != hist2.axis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of bins, can not add them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << hist1.axis().bins() << endl;
  cout << "          " 
       << "range of hist1: " << hist1.axis().lowerEdge() << " - " << hist1.axis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2: " << hist2.axis().lowerEdge() << " - " << hist2.axis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram1D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram1DROOT::add(const IHistogram1D & hist)" << endl;
#endif

  IHistogram1D *hist = createCopy(path,hist1);
  hist->add(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram1D * IHistogramFactoryROOT::subtract(const std::string & path,
					       const IHistogram1D & hist1,
					       const IHistogram1D & hist2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::subtract(const std::string & path,const IHistogram1D & hist1,const IHistogram1D & hist2):" << endl;
  cout << "          " 
       << "Subtract two 1D histograms (hist1 - hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if ( hist1.axis().bins() != hist2.axis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << hist1.axis().bins() << endl;
  cout << "          " 
       << "range of hist1: " << hist1.axis().lowerEdge() << " - " << hist1.axis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2: " << hist2.axis().lowerEdge() << " - " << hist2.axis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram1D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram1DROOT::subtract(const IHistogram1D & hist)" << endl;
#endif

  IHistogram1DROOT *hist = 
    dynamic_cast<IHistogram1DROOT*>( createCopy(path,hist1) );
  hist->subtract(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram1D * IHistogramFactoryROOT::multiply(const std::string & path,
			const IHistogram1D & hist1,
			const IHistogram1D & hist2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::multiply(const std::string & path,const IHistogram1D & hist1,const IHistogram1D & hist2):" << endl;
  cout << "          " 
       << "Multiply two 1D histograms (hist1 * hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if ( hist1.axis().bins() != hist2.axis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << hist1.axis().bins() << endl;
  cout << "          " 
       << "range of hist1: " << hist1.axis().lowerEdge() << " - " << hist1.axis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2: " << hist2.axis().lowerEdge() << " - " << hist2.axis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram1D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram1DROOT::multiply(const IHistogram1D & hist)" << endl;
#endif

  IHistogram1DROOT *hist = 
    dynamic_cast<IHistogram1DROOT*>( createCopy(path,hist1) );
  hist->multiply(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram1D * IHistogramFactoryROOT::divide(const std::string & path,
		      const IHistogram1D & hist1,
		      const IHistogram1D & hist2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::divide(const std::string & path,const IHistogram1D & hist1,const IHistogram1D & hist2):" << endl;
  cout << "          " 
       << "Divide two 1D histograms (hist1 / hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if ( hist1.axis().bins() != hist2.axis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of bins, can not divide them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBins: " << hist1.axis().bins() << endl;
  cout << "          " 
       << "range of hist1: " << hist1.axis().lowerEdge() << " - " << hist1.axis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2: " << hist2.axis().lowerEdge() << " - " << hist2.axis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram1D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram1DROOT::divide(const IHistogram1D & hist)" << endl;
#endif

  IHistogram1DROOT *hist = 
    dynamic_cast<IHistogram1DROOT*>( createCopy(path,hist1) );
  hist->divide(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram2D * IHistogramFactoryROOT::add(const std::string & path,
					  const IHistogram2D & hist1,
					  const IHistogram2D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::add(const std::string & path,const IHistogram2D & hist1,const IHistogram2D & hist2):" << endl;
  cout << "          " 
       << "Add two 2D histograms (hist1 + hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not add them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not add them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram2D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram2DROOT::add(const IHistogram2D & hist)" << endl;
#endif

  IHistogram2D *hist = createCopy(path,hist1);
  hist->add(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram2D * IHistogramFactoryROOT::subtract(const std::string & path,
			const IHistogram2D & hist1,
			const IHistogram2D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::subtract(const std::string & path,const IHistogram2D & hist1,const IHistogram2D & hist2):" << endl;
  cout << "          " 
       << "Subtract two 2D histograms (hist1 - hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram2D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram2DROOT::subtract(const IHistogram2D & hist)" << endl;
#endif

  IHistogram2DROOT *hist = 
    dynamic_cast<IHistogram2DROOT*>( createCopy(path,hist1) );
  hist->subtract(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram2D * IHistogramFactoryROOT::multiply(const std::string & path,
					       const IHistogram2D & hist1,
					       const IHistogram2D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::multiply(const std::string & path,const IHistogram2D & hist1,const IHistogram2D & hist2):" << endl;
  cout << "          " 
       << "Multiply two 2D histograms (hist1 * hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram2D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram2DROOT::multiply(const IHistogram2D & hist)" << endl;
#endif

  IHistogram2DROOT *hist = 
    dynamic_cast<IHistogram2DROOT*>( createCopy(path,hist1) );
  hist->multiply(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram2D * IHistogramFactoryROOT::divide(const std::string & path,
					     const IHistogram2D & hist1,
					     const IHistogram2D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::divide(const std::string & path,const IHistogram2D & hist1,const IHistogram2D & hist2):" << endl;
  cout << "          " 
       << "Divide two 2D histograms (hist1 / hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not divide them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not divide them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram2D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram2DROOT::divide(const IHistogram2D & hist)" << endl;
#endif

  IHistogram2DROOT *hist = 
    dynamic_cast<IHistogram2DROOT*>( createCopy(path,hist1) );
  hist->divide(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram3D * IHistogramFactoryROOT::add(const std::string & path,
					  const IHistogram3D & hist1,
					  const IHistogram3D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::add(const std::string & path,const IHistogram3D & hist1,const IHistogram3D & hist2):" << endl;
  cout << "          " 
       << "Add two 3D histograms (hist1 + hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not add them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not add them!" << endl;
#endif
      return NULL;
    }

  if (hist1.zAxis().bins() != hist2.zAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of z-bins, can not add them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() 
       << " nBinsZ: " << hist1.zAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist1.zAxis().lowerEdge() << " - " << hist1.zAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist2.zAxis().lowerEdge() << " - " << hist2.zAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram3D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram3DROOT::add(const IHistogram3D & hist)" << endl;
#endif

  IHistogram3D *hist = createCopy(path,hist1);
  hist->add(hist2) ;
  //  cout << "###---###" << dynamic_cast<IHistogram3DROOT*>(hist)->_histogram->GetNbinsX() << endl; 
  //  cout << "###---###" << dynamic_cast<IHistogram3DROOT*>(hist)->histoROOT()->GetNbinsX() << endl; 
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram3D * IHistogramFactoryROOT::subtract(const std::string & path,
					       const IHistogram3D & hist1,
					       const IHistogram3D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::subtract(const std::string & path,const IHistogram3D & hist1,const IHistogram3D & hist2):" << endl;
  cout << "          " 
       << "Subtract two 3D histograms (hist1 - hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

  if (hist1.zAxis().bins() != hist2.zAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of z-bins, can not subtract them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() 
       << " nBinsZ: " << hist1.zAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist1.zAxis().lowerEdge() << " - " << hist1.zAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist2.zAxis().lowerEdge() << " - " << hist2.zAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram3D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram3DROOT::subtract(const IHistogram3D & hist)" << endl;
#endif

  IHistogram3DROOT *hist = 
    dynamic_cast<IHistogram3DROOT*>( createCopy(path,hist1) );
  hist->subtract(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram3D * IHistogramFactoryROOT::multiply(const std::string & path,
					       const IHistogram3D & hist1,
					       const IHistogram3D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::multiply(const std::string & path,const IHistogram3D & hist1,const IHistogram3D & hist2):" << endl;
  cout << "          " 
       << "Multiply two 3D histograms (hist1 * hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

  if (hist1.zAxis().bins() != hist2.zAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of z-bins, can not multiply them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() 
       << " nBinsZ: " << hist1.zAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist1.zAxis().lowerEdge() << " - " << hist1.zAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist2.zAxis().lowerEdge() << " - " << hist2.zAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram3D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram3DROOT::multiply(const IHistogram3D & hist)" << endl;
#endif

  IHistogram3DROOT *hist = 
    dynamic_cast<IHistogram3DROOT*>( createCopy(path,hist1) );
  hist->multiply(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram3D * IHistogramFactoryROOT::divide(const std::string & path,
					     const IHistogram3D & hist1,
					     const IHistogram3D & hist2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::divide(const std::string & path,const IHistogram3D & hist1,const IHistogram3D & hist2):" << endl;
  cout << "          " 
       << "Divide two 3D histograms (hist1 / hist2)" << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path of new histogram: " << path << endl;
  cout << "          " 
       << "title of hist1: " << hist1.title() << endl;
  cout << "          " 
       << "title of hist2: " << hist2.title() << endl;
#endif

  if (hist1.xAxis().bins() != hist2.xAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of x-bins, can not divide them!" << endl;
#endif
      return NULL;
    }

  if (hist1.yAxis().bins() != hist2.yAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of y-bins, can not divide them!" << endl;
#endif
      return NULL;
    }

  if (hist1.zAxis().bins() != hist2.zAxis().bins() ) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "hist1 and hist2 have different number of z-bins, can not divide them!" << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "nBinsX: " << hist1.xAxis().bins() 
       << " nBinsY: " << hist1.yAxis().bins() 
       << " nBinsZ: " << hist1.zAxis().bins() << endl;
  cout << "          " 
       << "range of hist1 (x): " << hist1.xAxis().lowerEdge() << " - " << hist1.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist1.yAxis().lowerEdge() << " - " << hist1.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist1.zAxis().lowerEdge() << " - " << hist1.zAxis().upperEdge() << endl;
  cout << "          " 
       << "range of hist2 (x): " << hist2.xAxis().lowerEdge() << " - " << hist2.xAxis().upperEdge() << endl;
  cout << "          " 
       << "               (y): " << hist2.yAxis().lowerEdge() << " - " << hist2.yAxis().upperEdge() << endl;
  cout << "          " 
       << "               (z): " << hist2.zAxis().lowerEdge() << " - " << hist2.zAxis().upperEdge() << endl;
  cout << "          " 
       << "will call: IHistogramFactoryROOT::createCopy(const std::string & path,const IHistogram3D & hist) and " << endl;
  cout << "          " 
       << "           IHistogram3DROOT::divide(const IHistogram3D & hist)" << endl;
#endif

  IHistogram3DROOT *hist = 
    dynamic_cast<IHistogram3DROOT*>( createCopy(path,hist1) );
  hist->divide(hist2) ;
  // no need to add hist to  _histosInThisFactory, createCopy already did it 
  return hist;
}

IHistogram1D * IHistogramFactoryROOT::projectionX(const std::string & path,
						  const IHistogram2D & hist)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::projectionX(const std::string & path,const IHistogram2D & hist):" << endl;
  cout << "          "
       << "Create a new 1D histogram by projecting a 2D histogram along its x axis." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceX(const std::string & path,const IHistogram2D & hist,int index1,int index2)" << endl;
#endif
  return sliceX(path,hist,-2,-1);
}

IHistogram1D * IHistogramFactoryROOT::projectionY(const std::string & path,
						  const IHistogram2D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::projectionY(const std::string & path,const IHistogram2D & hist):" << endl;
  cout << "          "
       << "Create a new 1D histogram by projecting a 2D histogram along its y axis." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceY(const std::string & path,const IHistogram2D & hist,int index1,int index2)" << endl;
#endif
  return sliceY(path,hist,-2,-1);
}

IHistogram1D * IHistogramFactoryROOT::sliceX(const std::string & path,
					     const IHistogram2D & hist,
					     int index)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceX(const std::string & path,const IHistogram2D & hist,int index):" << endl;
  cout << "          "
       << "Create a new 1D histogram by slicing an 2D histogram parallel to the y axis at a given bin." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceX(const std::string & path,const IHistogram2D & hist,int index1,int index2)" << endl;
#endif
  return sliceX(path,hist,index,index);
}

IHistogram1D * IHistogramFactoryROOT::sliceY(const std::string & path,
					     const IHistogram2D & hist,
					     int index) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceY(const std::string & path,const IHistogram2D & hist,int index):" << endl;
  cout << "          "
       << "Create a new 1D histogram by slicing an 2D histogram parallel to the x axis at a given bin." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceY(const std::string & path,const IHistogram2D & hist,int index1,int index2)" << endl;
#endif
  return sliceY(path,hist,index,index);
}

IHistogram1D * IHistogramFactoryROOT::sliceX(const std::string & path,
		      const IHistogram2D & hist,
		      int index1,
		      int index2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceX(const std::string & path,const IHistogram2D & hist,int index1,int index2):" << endl;
  cout << "          "
       << "Create a new 1D histogram by slicing an 2D histogram parallel to the y axis between two bins (inclusive)." << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          "
       << "will call: IHistogram1DROOT::IHistogram1DROOT(const std::string & name,const IHistogram2DROOT & hist,char axis,int lowerBin,int upperBin)" << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram2DROOT* phist = dynamic_cast<const IHistogram2DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram1DROOT* histogram = new IHistogram1DROOT(thePath.getName(),
						     *phist,'x',index1,index2) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}


IHistogram1D * IHistogramFactoryROOT::sliceY(const std::string & path,
		      const IHistogram2D & hist,
		      int index1,
		      int index2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceY(const std::string & path,const IHistogram2D & hist,int index1,int index2):" << endl;
  cout << "          "
       << "Create a new 1D histogram by slicing an 2D histogram parallel to the x axis between two bins (inclusive)." << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          "
       << "will call: IHistogram1DROOT::IHistogram1DROOT(const std::string & name,const IHistogram2DROOT & hist,char axis,int lowerBin,int upperBin)" << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram2DROOT* phist = dynamic_cast<const IHistogram2DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram1DROOT* histogram = new IHistogram1DROOT(thePath.getName(),
						     *phist,'y',index1,index2) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}

IHistogram2D * IHistogramFactoryROOT::projectionXY(const std::string & path,
						   const IHistogram3D & hist)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::projectionXY(const std::string & path,const IHistogram3D & hist):" << endl;
  cout << "          "
       << "Create a new 2D histogram by projecting a 3D histogram on the xy plane." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceXY(const std::string & path,const IHistogram3D & hist,int index1,int index2)" << endl;
#endif
  return sliceXY(path,hist,-2,-1);
}

IHistogram2D * IHistogramFactoryROOT::projectionXZ(const std::string & path,
						   const IHistogram3D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::projectionXZ(const std::string & path,const IHistogram3D & hist):" << endl;
  cout << "          "
       << "Create a new 2D histogram by projecting a 3D histogram on the xz plane." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceXZ(const std::string & path,const IHistogram3D & hist,int index1,int index2)" << endl;
#endif
  return sliceXZ(path,hist,-2,-1);
}

IHistogram2D * IHistogramFactoryROOT::projectionYZ(const std::string & path,
						   const IHistogram3D & hist) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::projectionYZ(const std::string & path,const IHistogram3D & hist):" << endl;
  cout << "          "
       << "Create a new 2D histogram by projecting a 3D histogram on the yz plane." << endl << endl;
  cout << "          "
       << "will call: IHistogramFactoryROOT::sliceYZ(const std::string & path,const IHistogram3D & hist,int index1,int index2)" << endl;
#endif
  return sliceYZ(path,hist,-2,-1);
}

IHistogram2D * IHistogramFactoryROOT::sliceXY(const std::string & path,
					      const IHistogram3D & hist,
					      int index1,
					      int index2)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceXY(const std::string & path,const IHistogram3D & hist,int index1,int index2):" << endl;
  cout << "          "
       << "Create a new 2D histogram by slicing an 3D histogram perpendicular to the Z axis between two bins (inclusive)." << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          "
       << "will call: IHistogram2DROOT::IHistogram2DROOT(const std::string & name,const IHistogram3DROOT & hist,char axis,int lowerBin,int upperBin)" << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram3DROOT* phist = dynamic_cast<const IHistogram3DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram2DROOT* histogram = new IHistogram2DROOT(thePath.getName(),
						     *phist,"xy",index1,index2) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}

IHistogram2D * IHistogramFactoryROOT::sliceXZ(const std::string & path,
					      const IHistogram3D & hist,
					      int index1,
					      int index2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceXZ(const std::string & path,const IHistogram3D & hist,int index1,int index2):" << endl;
  cout << "          "
       << "Create a new 2D histogram by slicing an 3D histogram perpendicular to the Y axis between two bins (inclusive)." << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          "
       << "will call: IHistogram2DROOT::IHistogram2DROOT(const std::string & name,const IHistogram3DROOT & hist,char axis,int lowerBin,int upperBin)" << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }
  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram3DROOT* phist = dynamic_cast<const IHistogram3DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram2DROOT* histogram = new IHistogram2DROOT(thePath.getName(),
						     *phist,"xz",index1,index2) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}

IHistogram2D * IHistogramFactoryROOT::sliceYZ(const std::string & path,
					      const IHistogram3D & hist,
					      int index1,
					      int index2) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "IHistogramFactoryROOT::sliceYZ(const std::string & path,const IHistogram3D & hist,int index1,int index2):" << endl;
  cout << "          "
       << "Create a new 2D histogram by slicing an 3D histogram perpendicular to the X axis between two bins (inclusive)." << endl << endl;
  cout << "          "
       << "parameters: " << endl;
  cout << "          "
       << "----------- " << endl;
  cout << "          " 
       << "path: " << path << endl;
  cout << "          " 
       << "title: " << hist.title() << endl;
  cout << "          "
       << "will call: IHistogram2DROOT::IHistogram2DROOT(const std::string & name,const IHistogram3DROOT & hist,char axis,int lowerBin,int upperBin)" << endl;
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "No file specified: can not create a histogram!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
	  cout << "          "  
	       << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "  
	   << "directory where the histogram is created: " << _usedTree->pwd() << endl;
    }
#endif

  const IHistogram3DROOT* phist = dynamic_cast<const IHistogram3DROOT*>(&hist);
  if (!phist) return NULL;
  IHistogram2DROOT* histogram = new IHistogram2DROOT(thePath.getName(),
						     *phist,"yz",index1,index2) ;

  _usedTree->cd( thePWD ) ;

  _histosInThisFactory.insert(histogram);
  return histogram;
}
