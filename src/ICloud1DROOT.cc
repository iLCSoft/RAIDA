#include <RAIDA/ICloud1DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
// #include <RAIDA/utilROOT.h>
#include <RAIDA/PathName.h>
#include <RAIDA/Naming.h>
#include <AIDA/ITree.h>
#include <iostream>
#include <TH1D.h>
#include <TTree.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

ICloud1DROOT::ICloud1DROOT(const std::string & path,
			   const std::string & title,
			   int nMax,
			   ITree* usedTree,
			   const std::string & options)
  :   _usedTree(usedTree),
      _isConverted(false),
      //      _nBinsDefault(100),
      _nMax(nMax),
      _histoLowerEdge(0),
      _histoUpperEdge(0)
{
  _path.setPathName(path);
  //  _usedTree = usedTree;

  // TTree object to hold data points
  _ROOTTree = new TTree(_path.getName().c_str(),title.c_str());
  _ROOTTree->Branch("xValue",&_xValue,"xValue/D");
  _ROOTTree->Branch("yValue",&_yValue,"yValue/D");
}

ICloud1DROOT::ICloud1DROOT(const std::string & path,
			   ITree* usedTree,
			   const ICloud1DROOT & cloud) 
  : _usedTree(usedTree),
    _isConverted(cloud._isConverted),
    //    _nBinsDefault(100),
    _nMax(cloud._nMax),
    _histoLowerEdge(cloud._histoLowerEdge),
    _histoUpperEdge(cloud._histoUpperEdge)
{
  _path.setPathName(path);


  if (cloud._isConverted)
    {
      const IHistogram1DROOT * phisto = dynamic_cast<const IHistogram1DROOT*>(cloud._AIDAHistogram);
      _AIDAHistogram = new IHistogram1DROOT(_path.getName(),
					    *phisto) ;
    }
  else
    {
      _ROOTTree = (TTree*)cloud._ROOTTree->Clone( _path.getName().c_str() );
      _ROOTTree->SetBranchAddress("xValue",&_xValue);
      _ROOTTree->SetBranchAddress("yValue",&_yValue);
    }
}

bool ICloud1DROOT::fill(double x, double weight) 
{
  // only fill if weight is positiv
  if (weight<0) { return false; }

  if (!_isConverted) // fill data in ttree 
    {
      _xValue = x;
      _yValue = weight;
      _ROOTTree->Fill();
    }
  else // fill data in histogram 
    {
      _AIDAHistogram->fill(x,weight);
    }
  //  cout << _ROOTTree->GetEntriesFast() << " " << _nMax << endl;
  if (!_isConverted && _ROOTTree->GetEntriesFast()==_nMax)
    {
      convert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"), (double)_ROOTTree->GetMaximum("xValue"));
    }
  return true;
}

double ICloud1DROOT::lowerEdge() const 
{
  if (!_isConverted) 
    {
      return _ROOTTree->GetMinimum("xValue");
    }
  else
    {
      return _histoLowerEdge;
    }
}

double ICloud1DROOT::upperEdge() const 
{
  if (!_isConverted) 
    {
      return _ROOTTree->GetMaximum("xValue");
    }
  else
    {
      return _histoUpperEdge;
    }
}

double ICloud1DROOT::value(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast()) 
    {
      return (double)-1.;
    }

  double x,y;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->GetEntry( (Int_t)index );
  return x;
}

double ICloud1DROOT::weight(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast()) 
    {
      return (double)-1.;
    }

  double x,y;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->GetEntry( (Int_t)index );
  return y;
}

double ICloud1DROOT::mean() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += y; 
	  myMean += x*y;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->mean();
    }
}

double ICloud1DROOT::rms() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = mean();
      double x,y;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += y;
	  myRMS += y*(myMean - x)*y*(myMean - x);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rms();
    }
}

bool ICloud1DROOT::convert(int nBins, double lowerEdge, double upperEdge) 
{
  return myConvert(nBins, lowerEdge, upperEdge);
}

bool ICloud1DROOT::myConvert(int nBins, 
			     double lowerEdge, 
                             double upperEdge) const 
{ 
  if (_isConverted) return false ;

  _histoLowerEdge = lowerEdge;
  _histoUpperEdge = upperEdge+0.000001;
  _isConverted = true;

  // go to right Directory and create histogram 
  string thePWD = _usedTree->pwd();
  if ( !_path.onlyName() )
    {
      _usedTree->cd( _path.getPath() ); 
      //      cout << "### pwd: " << _usedTree->pwd() << endl;
    }

  string options("");
  string title = _ROOTTree->GetTitle();
  _AIDAHistogram = new IHistogram1DROOT(_path.getNameTemp(),
					title,nBins,
					_histoLowerEdge,_histoUpperEdge,
					options) ;
  _usedTree->cd( thePWD ) ;

  double x,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ ) 
    {
      _ROOTTree->GetEntry( (Int_t)i );
      _AIDAHistogram->fill(x,weight);
    }

  delete _ROOTTree;

  IHistogram1DROOT* temphisto 
    = dynamic_cast<IHistogram1DROOT*>(_AIDAHistogram);
  temphisto->setName( _path.getName() );
  return true;
}

const IHistogram1D & ICloud1DROOT::histogram() const 
{
  if (!_isConverted) 
    {
      myConvertToHistogram() ;
    } 

  return *_AIDAHistogram;
}

bool ICloud1DROOT::fillHistogram(IHistogram1D & hist) const 
{
  if (_isConverted) return false; 

  double x,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ ) 
    {
      _ROOTTree->GetEntry( (Int_t)i );
      hist.fill(x,weight);
    }
  return true;
}

double ICloud1DROOT::sumOfWeights() const 
{
  if (!_isConverted)
    {
      double x,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&weight);
      double sumOfWeights = 0;
      for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ ) 
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sumOfWeights += weight;
	}
      return sumOfWeights; 
    }
  else
    {
      return _AIDAHistogram->sumAllBinHeights();
    }
}

bool ICloud1DROOT::convertToHistogram()  
{
  return myConvertToHistogram();
}

bool ICloud1DROOT::myConvertToHistogram() const 
{
  return myConvert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"), 
		   (double)_ROOTTree->GetMaximum("xValue"));
}

bool ICloud1DROOT::isConverted() const 
{
  return _isConverted;
}

int ICloud1DROOT::maxEntries() const 
{
  return _nMax;
}

bool ICloud1DROOT::scale(double scaleFactor) 
{ 
  if (scaleFactor<0) return false; 

  if (!_isConverted)
    {
      string title(_ROOTTree->GetTitle());
      TTree *tempROOTTree = _ROOTTree;
      tempROOTTree->SetNameTitle("myTempCloude","myTempCloude");

      // go to right Directory and create histogram 
      string thePWD = _usedTree->pwd();

      if ( !_path.onlyName() )
	{
	  _usedTree->cd( _path.getPath() ); 
	}

      _ROOTTree = new TTree(_path.getName().c_str(),title.c_str());

      _usedTree->cd( thePWD ) ;

      _ROOTTree->Branch("xValue",&_xValue,"xValue/D");
      _ROOTTree->Branch("yValue",&_yValue,"yValue/D");

      double x,weight;
      tempROOTTree->SetBranchAddress("xValue",&x);
      tempROOTTree->SetBranchAddress("yValue",&weight);
      for ( int i=0; i<tempROOTTree->GetEntriesFast(); i++ ) 
	{
	  tempROOTTree->GetEntry( (Int_t)i );
	  _xValue = x;
	  _yValue = weight * scaleFactor;
	  _ROOTTree->Fill();
	}
      delete tempROOTTree;
    }
  else
    {
      _AIDAHistogram->scale(scaleFactor);
    }

  return true;
}

std::string ICloud1DROOT::title() const 
{
  if (!_isConverted)
    {
      string temp(_ROOTTree->GetTitle());
      return temp;
    }
  else
    {
      return _AIDAHistogram->title();
    }
}

bool ICloud1DROOT::setTitle(const std::string & title) 
{
  if (!_isConverted)
    {
      _ROOTTree->SetTitle( title.c_str() );
    }
  else
    {
      _AIDAHistogram->setTitle( title );
    }

  return true;
}

int ICloud1DROOT::dimension() const 
{
  return 1;
}

bool ICloud1DROOT::reset() 
{ // ### FIXME !!! benoetigt bessere moeglichkeit des resets
  if (!_isConverted)
    {
      _ROOTTree->Reset("");
      return true;
    }
  else
    {
      return false;
    }

}

int ICloud1DROOT::entries() const 
{
  return _AIDAHistogram->entries();
}




