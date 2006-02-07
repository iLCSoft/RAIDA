#include <RAIDA/ICloud3DROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
// #include <RAIDA/utilROOT.h>
#include <RAIDA/PathName.h>
#include <RAIDA/Naming.h>
#include <AIDA/ITree.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TTree.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

ICloud3DROOT::ICloud3DROOT(const std::string & path,
                           const std::string & title,
                           int nMax,
			   ITree* usedTree,
                           const std::string & options)
  : _isConverted(false),
    _nBinsDefault(10), // ######
    _nMax(nMax),
    _histoLowerEdgeX(0),
    _histoUpperEdgeX(0),
    _histoLowerEdgeY(0),
    _histoUpperEdgeY(0),
    _histoLowerEdgeZ(0),
    _histoUpperEdgeZ(0)
{
  _path.setPathName(path);
  _usedTree = usedTree;

  // TTree object to hold data points
  _ROOTTree = new TTree(_path.getName().c_str(),title.c_str());
  _ROOTTree->Branch("xValue",&_xValue,"xValue/D");
  _ROOTTree->Branch("yValue",&_yValue,"yValue/D");
  _ROOTTree->Branch("zValue",&_zValue,"zValue/D");
  _ROOTTree->Branch("wValue",&_wValue,"wValue/D");
}

bool ICloud3DROOT::fill(double x, double y, double z, double weight) 
{
  // only fill if weight is positiv
  if (weight<0) { return false; }

  if (!_isConverted) // fill data in ttree
    {
      _xValue = x;
      _yValue = y;
      _zValue = z;
      _wValue = weight;
      _ROOTTree->Fill();
    }
  else // fill data in histogram
    {
      _AIDAHistogram->fill(x,y,z,weight);
    }

  if (!_isConverted && _ROOTTree->GetEntriesFast()==_nMax)
    {
      convert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"), 
	      (double)_ROOTTree->GetMaximum("xValue"),
	      _nBinsDefault, (double)_ROOTTree->GetMinimum("yValue"), 
	      (double)_ROOTTree->GetMaximum("yValue"), 
	      _nBinsDefault, (double)_ROOTTree->GetMinimum("zValue"), 
	      (double)_ROOTTree->GetMaximum("zValue") );
    }
  return true;
}

double ICloud3DROOT::lowerEdgeX() const 
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

double ICloud3DROOT::lowerEdgeY() const 
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

double ICloud3DROOT::lowerEdgeZ() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMinimum("zValue");
    }
  else
    {
      return _histoLowerEdgeZ;
    }
}

double ICloud3DROOT::upperEdgeX() const 
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

double ICloud3DROOT::upperEdgeY() const 
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

double ICloud3DROOT::upperEdgeZ() const 
{
  if (!_isConverted)
    {
      return _ROOTTree->GetMaximum("zValue");
    }
  else
    {
      return _histoUpperEdgeZ;
    }
}

double ICloud3DROOT::valueX(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  _ROOTTree->GetEntry( (Int_t)index );
  return x;
}

double ICloud3DROOT::valueY(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  _ROOTTree->GetEntry( (Int_t)index );
  return y;
}

double ICloud3DROOT::valueZ(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  _ROOTTree->GetEntry( (Int_t)index );
  return z;
}

double ICloud3DROOT::weight(int index) const 
{
  if ( index<0 || index>=_ROOTTree->GetEntriesFast())
    {
      return (double)-1.;
    }

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  _ROOTTree->GetEntry( (Int_t)index );
  return weight;
}

double ICloud3DROOT::meanX() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight; 
	  myMean += x*weight;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->meanX();
    }
}

double ICloud3DROOT::meanY() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight; 
	  myMean += y*weight;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->meanY();
    }
}

double ICloud3DROOT::meanZ() const 
{ 
  if (!_isConverted)
    {
      double myMean = 0, sum = 0;
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight; 
	  myMean += z*weight;
	}
      return myMean / sum; 
    }
  else
    {
      return _AIDAHistogram->meanZ();
    }
}

double ICloud3DROOT::rmsX() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = meanX();
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight;
	  myRMS += weight*(myMean - x)*weight*(myMean - x);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rmsX();
    }
}

double ICloud3DROOT::rmsY() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = meanY();
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight;
	  myRMS += weight*(myMean - y)*weight*(myMean - y);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rmsY();
    }
}

double ICloud3DROOT::rmsZ() const 
{
  if (!_isConverted)
    {
      double myRMS = 0, sum = 0;
      double myMean = meanZ();
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
      for (int i=0; i<_ROOTTree->GetEntriesFast() ; i++)
	{
	  _ROOTTree->GetEntry( (Int_t)i );
	  sum += weight;
	  myRMS += weight*(myMean - z)*weight*(myMean - z);
	}
      myRMS = sqrt( myRMS / sqrt(sum * (sum -0)) );
      return myRMS; 
    }
  else
    {
      return _AIDAHistogram->rmsZ();
    }
}

bool ICloud3DROOT::convert(int nBinsX,
			   double lowerEdgeX,
			   double upperEdgeX,
			   int nBinsY,
			   double lowerEdgeY,
			   double upperEdgeY,
			   int nBinsZ,
			   double lowerEdgeZ,
			   double upperEdgeZ)
{
  return myConvert(nBinsX,lowerEdgeX,upperEdgeX,
		   nBinsY,lowerEdgeY,upperEdgeY,
		   nBinsZ,lowerEdgeZ,upperEdgeZ);
}

bool ICloud3DROOT::myConvert(int nBinsX,
			     double lowerEdgeX,
			     double upperEdgeX,
			     int nBinsY,
			     double lowerEdgeY,
			     double upperEdgeY,
			     int nBinsZ,
			     double lowerEdgeZ,
			     double upperEdgeZ) const
{ 
  if (_isConverted) return false ;

  _histoLowerEdgeX = lowerEdgeX;
  _histoUpperEdgeX = upperEdgeX+0.000001;
  _histoLowerEdgeY = lowerEdgeY;
  _histoUpperEdgeY = upperEdgeY+0.000001;
  _histoLowerEdgeZ = lowerEdgeZ;
  _histoUpperEdgeZ = upperEdgeZ+0.000001;
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
  _AIDAHistogram = new IHistogram3DROOT(_path.getNameTemp(),
					title,
					nBinsX,_histoLowerEdgeX,
					_histoUpperEdgeX,
					nBinsY,_histoLowerEdgeY,
					_histoUpperEdgeY,
					nBinsZ,_histoLowerEdgeZ,
					_histoUpperEdgeZ,options) ;

  _usedTree->cd( thePWD ) ;

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ ) 
    {
      _ROOTTree->GetEntry( (Int_t)i );
      _AIDAHistogram->fill(x,y,z,weight);
    }

  delete _ROOTTree;
  IHistogram3DROOT* temphisto
    = dynamic_cast<IHistogram3DROOT*>(_AIDAHistogram);
  temphisto->setName( _path.getName() );
  return true;
}

const IHistogram3D & ICloud3DROOT::histogram() const 
{
  if (!_isConverted)
    {
      myConvertToHistogram() ;
    }

  return *_AIDAHistogram;
}

bool ICloud3DROOT::fillHistogram(IHistogram3D & hist) const 
{
  if (_isConverted) return false;

  double x,y,z,weight;
  _ROOTTree->SetBranchAddress("xValue",&x);
  _ROOTTree->SetBranchAddress("yValue",&y);
  _ROOTTree->SetBranchAddress("zValue",&z);
  _ROOTTree->SetBranchAddress("wValue",&weight);
  for ( int i=0; i<_ROOTTree->GetEntriesFast(); i++ )
    {
      _ROOTTree->GetEntry( (Int_t)i );
      hist.fill(x,y,z,weight);
    }
  return true;
}

double ICloud3DROOT::sumOfWeights() const 
{
  if (!_isConverted)
    {
      double x,y,z,weight;
      _ROOTTree->SetBranchAddress("xValue",&x);
      _ROOTTree->SetBranchAddress("yValue",&y);
      _ROOTTree->SetBranchAddress("zValue",&z);
      _ROOTTree->SetBranchAddress("wValue",&weight);
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

bool ICloud3DROOT::convertToHistogram() 
{
  return myConvertToHistogram();
}

bool ICloud3DROOT::myConvertToHistogram() const 
{
  return myConvert(_nBinsDefault, (double)_ROOTTree->GetMinimum("xValue"),
                   (double)_ROOTTree->GetMaximum("xValue"),
                   _nBinsDefault, (double)_ROOTTree->GetMinimum("yValue"),
                   (double)_ROOTTree->GetMaximum("yValue"), 
                   _nBinsDefault, (double)_ROOTTree->GetMinimum("zValue"),
                   (double)_ROOTTree->GetMaximum("zValue") );
}

bool ICloud3DROOT::isConverted() const
{
  return _isConverted;
}

int ICloud3DROOT::maxEntries() const
{
  return _nMax;
}

bool ICloud3DROOT::scale(double scaleFactor) 
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
      _ROOTTree->Branch("wValue",&_wValue,"wValue/D");

      double x,y,z,weight;
      tempROOTTree->SetBranchAddress("xValue",&x);
      tempROOTTree->SetBranchAddress("yValue",&y);
      tempROOTTree->SetBranchAddress("zValue",&z);
      tempROOTTree->SetBranchAddress("wValue",&weight);
      for ( int i=0; i<tempROOTTree->GetEntriesFast(); i++ ) 
	{
	  tempROOTTree->GetEntry( (Int_t)i );
	  _xValue = x;
	  _yValue = y;
	  _zValue = z;
	  _wValue = weight * scaleFactor;
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

std::string ICloud3DROOT::title() const
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

bool ICloud3DROOT::setTitle(const std::string & title) 
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

int ICloud3DROOT::dimension() const
{
  return 3;
}

bool ICloud3DROOT::reset() 
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

int ICloud3DROOT::entries() const
{
  return _AIDAHistogram->entries();
}

