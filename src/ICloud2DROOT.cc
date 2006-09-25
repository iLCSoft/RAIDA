#include <RAIDA/ICloud2DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
// #include <RAIDA/utilROOT.h>
#include <RAIDA/PathName.h>
#include <RAIDA/Naming.h>
#include <AIDA/ITree.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

ICloud2DROOT::ICloud2DROOT(const std::string & path,
                           const std::string & title,
                           int nMax,
			   ITree* usedTree,
                           const std::string & options)
  : _usedTree(usedTree),
    _isConverted(false),
    //    _nBinsDefault(100),
    _nMax(nMax),
    _histoLowerEdgeX(0),
    _histoUpperEdgeX(0),
    _histoLowerEdgeY(0),
    _histoUpperEdgeY(0)
{
  _path.setPathName(path);
  //  _usedTree = usedTree;

  // TTree object to hold data points
  _ROOTTree = new TTree(_path.getName().c_str(),title.c_str());
  _ROOTTree->Branch("xValue",&_xValue,"xValue/D");
  _ROOTTree->Branch("yValue",&_yValue,"yValue/D");
  _ROOTTree->Branch("zValue",&_zValue,"zValue/D");
}

ICloud2DROOT::ICloud2DROOT(const std::string & path,
			   ITree* usedTree,
			   const ICloud2DROOT & cloud) 
  : _usedTree(usedTree),
    _isConverted(cloud._isConverted),
    //    _nBinsDefault(100),
    _nMax(cloud._nMax),
    _histoLowerEdgeX(cloud._histoLowerEdgeX),
    _histoUpperEdgeX(cloud._histoUpperEdgeX),
    _histoLowerEdgeY(cloud._histoLowerEdgeY),
    _histoUpperEdgeY(cloud._histoUpperEdgeY)
{
  _path.setPathName(path);

  if (cloud._isConverted)
    {
      const IHistogram2DROOT * phisto = dynamic_cast<const IHistogram2DROOT*>(cloud._AIDAHistogram);
      _AIDAHistogram = new IHistogram2DROOT(_path.getName(),
					    *phisto) ;
    }
  else
    {
      _ROOTTree = (TTree*)cloud._ROOTTree->Clone( _path.getName().c_str() );
      _ROOTTree->SetBranchAddress("xValue",&_xValue);
      _ROOTTree->SetBranchAddress("yValue",&_yValue);
      _ROOTTree->SetBranchAddress("zValue",&_zValue);
    }
}

bool ICloud2DROOT::fill(double x, double y, double weight) 
{
  // only fill if weight is positiv
  if (weight<0) { return false; }

  if (!_isConverted) // fill data in ttree
    {
      _xValue = x;
      _yValue = y;
      _zValue = weight;
      _ROOTTree->Fill();
    }
  else // fill data in histogram
    {
      _AIDAHistogram->fill(x,y,weight);
    }
  if (!_isConverted && _ROOTTree->GetEntriesFast()==_nMax)
    {
      convert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"), 
	      (double)_ROOTTree->GetMaximum("xValue"),
	      _nBinsDefault, (double)_ROOTTree->GetMinimum("yValue"), 
	      (double)_ROOTTree->GetMaximum("yValue") );
    }
  return true;
}

double ICloud2DROOT::lowerEdgeX() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMinimum("xValue");
    }
  else
    {
      return _histoLowerEdgeX;
    }
}

double ICloud2DROOT::lowerEdgeY() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMinimum("yValue");
    }
  else
    {
      return _histoLowerEdgeY;
    }
}

double ICloud2DROOT::upperEdgeX() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMaximum("xValue");
    }
  else
    {
      return _histoUpperEdgeX;
    }
}

double ICloud2DROOT::upperEdgeY() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMaximum("yValue");
    }
  else
    {
      return _histoUpperEdgeY;
    }
}

double ICloud2DROOT::valueX(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->GetEntry( (Int_t)index );
  return x;
}

double ICloud2DROOT::valueY(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->GetEntry( (Int_t)index );
  return y;
}

double ICloud2DROOT::weight(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->GetEntry( (Int_t)index );
  return z;
}

double ICloud2DROOT::meanX() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y,z;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += z; 
	  myMean += x*z;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->meanX();
    }
}

double ICloud2DROOT::meanY() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y,z;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += z; 
	  myMean += y*z;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->meanY();
    }
}

double ICloud2DROOT::rmsX() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = meanX();
      double x,y,z;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += z;
	  myRMS += z*(myMean - x)*z*(myMean - x);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rmsX();
    }
}

double ICloud2DROOT::rmsY() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = meanY();
      double x,y,z;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += z;
	  myRMS += z*(myMean - y)*z*(myMean - y);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rmsY();
    }
}

bool ICloud2DROOT::convert(int nBinsX,
			   double lowerEdgeX,
			   double upperEdgeX,
			   int nBinsY,
			   double lowerEdgeY,
			   double upperEdgeY)
{
  return myConvert(nBinsX,lowerEdgeX,upperEdgeX,nBinsY,lowerEdgeY,upperEdgeY);
}

bool ICloud2DROOT::myConvert(int nBinsX,
			     double lowerEdgeX,
			     double upperEdgeX,
			     int nBinsY,
			     double lowerEdgeY,
			     double upperEdgeY) const
{ 
  if (_isConverted) return false ;

  _histoLowerEdgeX = lowerEdgeX;
  _histoUpperEdgeX = upperEdgeX+0.000001;
  _histoLowerEdgeY = lowerEdgeY;
  _histoUpperEdgeY = upperEdgeY+0.000001;
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
  _AIDAHistogram = new IHistogram2DROOT(_path.getNameTemp(),
					title,
					nBinsX,_histoLowerEdgeX,
					_histoUpperEdgeX,
					nBinsY,_histoLowerEdgeY,
					_histoUpperEdgeY,options) ;

  _usedTree->cd( thePWD ) ;

  double x,y,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ ) 
    {
      _ROOTTree->GetEntry( (Int_t)i );
      _AIDAHistogram->fill(x,y,weight);
    }

  delete _ROOTTree;
  IHistogram2DROOT* temphisto
    = dynamic_cast<IHistogram2DROOT*>(_AIDAHistogram);
  temphisto->setName( _path.getName() );
  return true;
}

const IHistogram2D & ICloud2DROOT::histogram() const 
{
  if (!_isConverted)
    {
      myConvertToHistogram() ;
    }

  return *_AIDAHistogram;
}

bool ICloud2DROOT::fillHistogram(IHistogram2D & hist) const 
{
  if (_isConverted) return false;

  double x,y,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ )
    {
      _ROOTTree->GetEntry( (Int_t)i );
      hist.fill(x,y,weight);
    }
  return true;
}

double ICloud2DROOT::sumOfWeights() const 
{
  if (!_isConverted)
    {
      double x,y,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&weight);
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

bool ICloud2DROOT::convertToHistogram() 
{
  return myConvertToHistogram();
}

bool ICloud2DROOT::myConvertToHistogram() const 
{
  return myConvert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"),
		   (double)_ROOTTree->GetMaximum("xValue"),
		   _nBinsDefault, (double)_ROOTTree->GetMinimum("yValue"),
		   (double)_ROOTTree->GetMaximum("yValue") );
}

bool ICloud2DROOT::isConverted() const 
{
  return _isConverted;
}

int ICloud2DROOT::maxEntries() const 
{
  return _nMax;
}

bool ICloud2DROOT::scale(double scaleFactor) 
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
      _ROOTTree->Branch("zValue",&_zValue,"zValue/D");

      double x,y,weight;
      tempROOTTree->SetBranchAddress("xValue",&x);
      tempROOTTree->SetBranchAddress("yValue",&y);
      tempROOTTree->SetBranchAddress("zValue",&weight);
      for ( int i=0; i<tempROOTTree->GetEntriesFast(); i++ ) 
	{
	  tempROOTTree->GetEntry( (Int_t)i );
	  _xValue = x;
	  _yValue = y;
	  _zValue = weight * scaleFactor;
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

std::string ICloud2DROOT::title() const 
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

bool ICloud2DROOT::setTitle(const std::string & title) 
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

int ICloud2DROOT::dimension() const 
{
  return 2;
}

bool ICloud2DROOT::reset() 
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

int ICloud2DROOT::entries() const 
{
  return _AIDAHistogram->entries();
}


