#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/IAxisROOT.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

IHistogram3DROOT::IHistogram3DROOT(const std::string & name,
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
  _histogram = new TH3D(name.c_str(),
			title.c_str(),
			(Int_t)nBinsX,
			(Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
                        (Int_t)nBinsY,
			(Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
                        (Int_t)nBinsZ,
			(Axis_t)lowerEdgeZ,(Axis_t)upperEdgeZ);
  _histogramAIDA = new TH3D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,
			    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
			    (Int_t)nBinsY,
			    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
			    (Int_t)nBinsZ,
			    (Axis_t)lowerEdgeZ,(Axis_t)upperEdgeZ);
  _histogramAIDABinMeanX = new TH3D(Naming::binMeanX(name).c_str(),
				    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
				    (Int_t)nBinsZ,
				    (Axis_t)lowerEdgeZ,(Axis_t)upperEdgeZ);
  _histogramAIDABinMeanY = new TH3D(Naming::binMeanY(name).c_str(),
				    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
				    (Int_t)nBinsZ,
				    (Axis_t)lowerEdgeZ,(Axis_t)upperEdgeZ);
  _histogramAIDABinMeanZ = new TH3D(Naming::binMeanZ(name).c_str(),
				    Naming::titleBinMeanZ(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
				    (Int_t)nBinsZ,
				    (Axis_t)lowerEdgeZ,(Axis_t)upperEdgeZ);

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();

  _yAxis = new IAxisROOT( _histogram->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();

  _zAxis = new IAxisROOT( _histogram->GetZaxis() );
  dynamic_cast<IAxisROOT*>(_zAxis)->setFixedBinning();
}

IHistogram3DROOT::IHistogram3DROOT(const std::string & name,
				   const std::string & title,
				   const std::vector<double>  & binEdgesX,
				   const std::vector<double>  & binEdgesY,
				   const std::vector<double>  & binEdgesZ,
				   const std::string & options) 
{
  const int nBinsX = binEdgesX.size()-1;
  const int nBinsY = binEdgesY.size()-1;
  const int nBinsZ = binEdgesZ.size()-1;
  Double_t xBins[nBinsX+1];
  Double_t yBins[nBinsY+1];
  Double_t zBins[nBinsZ+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdgesX[i];
  for (int i=0;i<=nBinsY;i++)
    yBins[i] = binEdgesY[i];
  for (int i=0;i<=nBinsZ;i++)
    zBins[i] = binEdgesZ[i];

  _histogram = new TH3D(name.c_str(),
			title.c_str(),
			(Int_t)nBinsX,xBins,
                        (Int_t)nBinsY,yBins,
                        (Int_t)nBinsZ,zBins);
  _histogramAIDA = new TH3D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,xBins,
			    (Int_t)nBinsY,yBins,
			    (Int_t)nBinsZ,zBins);
  _histogramAIDABinMeanX = new TH3D(Naming::binMeanX(name).c_str(),
				    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins,
				    (Int_t)nBinsZ,zBins);
  _histogramAIDABinMeanY = new TH3D(Naming::binMeanY(name).c_str(),
				    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins,
				    (Int_t)nBinsZ,zBins);
  _histogramAIDABinMeanZ = new TH3D(Naming::binMeanZ(name).c_str(),
				    Naming::titleBinMeanZ(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins,
				    (Int_t)nBinsZ,zBins);
  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning();

  _yAxis = new IAxisROOT( _histogram->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning();

  _zAxis = new IAxisROOT( _histogram->GetZaxis() );
  dynamic_cast<IAxisROOT*>(_zAxis)->setVariableBinning();
}

IHistogram3DROOT::IHistogram3DROOT(const std::string & name,
		 const IHistogram3DROOT & hist) 
{
  _histogram = (TH3D*)hist._histogram->Clone( name.c_str() );
  _histogramAIDA = (TH3D*)hist._histogramAIDA->Clone( Naming::binEntry(name).c_str() );
  _histogramAIDABinMeanX = (TH3D*)hist._histogramAIDABinMeanX->Clone( Naming::binMeanX(name).c_str() );
  _histogramAIDABinMeanY = (TH3D*)hist._histogramAIDABinMeanY->Clone( Naming::binMeanY(name).c_str() );
  _histogramAIDABinMeanZ = (TH3D*)hist._histogramAIDABinMeanZ->Clone( Naming::binMeanZ(name).c_str() );

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  if ( hist._xAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;

  _yAxis = new IAxisROOT( _histogram->GetYaxis() );
  if ( hist._yAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning() ;

  _zAxis = new IAxisROOT( _histogram->GetZaxis() );
  if ( hist._zAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_zAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_zAxis)->setVariableBinning() ;
}


bool IHistogram3DROOT::fill(double x, double y, double z, double weight) 
{
  // only fill if weight is positiv
  if (weight<0) {  return false; }

  int iBin = (int)_histogram->FindBin( (Axis_t)x,(Axis_t)y,(Axis_t)z );
  double iBinHeight = (double)_histogram->GetBinContent(iBin);
  double newBinMeanX, oldBinMeanX;
  double newBinMeanY, oldBinMeanY;
  double newBinMeanZ, oldBinMeanZ;
  oldBinMeanX = (double)_histogramAIDABinMeanX->GetBinContent(iBin);
  newBinMeanX = (oldBinMeanX * iBinHeight + x*weight)/(weight+iBinHeight);
  oldBinMeanY = (double)_histogramAIDABinMeanY->GetBinContent(iBin);
  newBinMeanY = (oldBinMeanY * iBinHeight + y*weight)/(weight+iBinHeight);
  oldBinMeanZ = (double)_histogramAIDABinMeanZ->GetBinContent(iBin);
  newBinMeanZ = (oldBinMeanZ * iBinHeight + z*weight)/(weight+iBinHeight);

  _histogramAIDABinMeanX->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanX );
  _histogramAIDABinMeanY->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanY );
  _histogramAIDABinMeanZ->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanZ );
  _histogram->Fill( (Axis_t)x,(Axis_t)y,(Axis_t)z,(Stat_t)weight );
  _histogramAIDA->Fill( (Axis_t)x,(Axis_t)y,(Axis_t)z,(Stat_t)1. );
  return true;
}

double IHistogram3DROOT::binMeanX(int indexX, int indexY, int indexZ) const 
{
  return (double)_histogramAIDABinMeanX->GetBinContent( (Int_t)indexX,
                                                        (Int_t)indexY,
                                                        (Int_t)indexZ );
}

double IHistogram3DROOT::binMeanY(int indexX, int indexY, int indexZ) const 
{
  return (double)_histogramAIDABinMeanY->GetBinContent( (Int_t)indexX,
                                                        (Int_t)indexY,
                                                        (Int_t)indexZ );
}

double IHistogram3DROOT::binMeanZ(int indexX, int indexY, int indexZ) const 
{
  return (double)_histogramAIDABinMeanZ->GetBinContent( (Int_t)indexX,
                                                        (Int_t)indexY,
                                                        (Int_t)indexZ );
}

int IHistogram3DROOT::binEntries(int indexX, int indexY, int indexZ) const 
{
  double binCount;
  binCount = (double)_histogramAIDA->GetBinContent( (Int_t)indexX,
                                                    (Int_t)indexY,
                                                    (Int_t)indexZ );
  return (int)binCount;
}

int IHistogram3DROOT::binEntriesX(int index) const 
{
  double sumX = 0;
  if (index < 0 || index > ((int)_histogramAIDA->GetNbinsX()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsY()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogramAIDA->GetNbinsZ()+1) ; j++)
	{
	  sumX += (double)_histogramAIDA->GetBinContent( (Int_t)index,(Int_t)i,(Int_t)j );
	}
    }
  return (int)sumX;
}

int IHistogram3DROOT::binEntriesY(int index) const  
{
  double sumY = 0;
  if (index < 0 || index > ((int)_histogramAIDA->GetNbinsY()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogramAIDA->GetNbinsZ()+1) ; j++)
	{
	  sumY += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)index,(Int_t)j );
	}
    }
  return (int)sumY;
}

int IHistogram3DROOT::binEntriesZ(int index) const 
{
  double sumZ = 0;
  if (index < 0 || index > ((int)_histogramAIDA->GetNbinsZ()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogramAIDA->GetNbinsY()+1) ; j++)
	{
	  sumZ += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)index );
	}
    }
  return (int)sumZ;
}

double IHistogram3DROOT::binHeight(int indexX, int indexY, int indexZ) const 
{
  if ( (indexX < 0 || indexX > ((int)_histogram->GetNbinsX()+1)) ||
       (indexY < 0 || indexY > ((int)_histogram->GetNbinsY()+1)) ||
       (indexZ < 0 || indexZ > ((int)_histogram->GetNbinsZ()+1)) )
    {
      return -99999;
    }
  return (double)_histogram->GetBinContent( (Int_t)indexX,(Int_t)indexY,(Int_t)indexZ );
}

double IHistogram3DROOT::binHeightX(int index) const 
{
  double sumX = 0;
  if (index < 0 || index > ((int)_histogram->GetNbinsX()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogram->GetNbinsY()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsZ()+1) ; j++)
	{
	  sumX += (double)_histogram->GetBinContent( (Int_t)index,(Int_t)i,(Int_t)j );
	}
    }
  return sumX;
}

double IHistogram3DROOT::binHeightY(int index) const 
{
  double sumY = 0;
  if (index < 0 || index > ((int)_histogram->GetNbinsY()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsZ()+1) ; j++)
	{
	  sumY += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)index,(Int_t)j );
	}
    }
  return sumY;
}

double IHistogram3DROOT::binHeightZ(int index) const 
{
  double sumZ = 0;
  if (index < 0 || index > ((int)_histogram->GetNbinsZ()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++)
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsY()+1) ; j++)
	{
	  sumZ += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)index );
	}
    }
  return sumZ;
}

double IHistogram3DROOT::binError(int indexX, int indexY, int indexZ) const 
{
  return (double)_histogram->GetBinError( (Int_t)indexX,(Int_t)indexY,(Int_t)indexZ );
}

double IHistogram3DROOT::meanX() const 
{
  return (double)_histogram->GetMean( (Int_t)1 );
}

double IHistogram3DROOT::meanY() const 
{
  return (double)_histogram->GetMean( (Int_t)2 );
}

double IHistogram3DROOT::meanZ() const 
{
  return (double)_histogram->GetMean( (Int_t)3 );
}

double IHistogram3DROOT::rmsX() const 
{
  return (double)_histogram->GetRMS( (Int_t)1 );
}

double IHistogram3DROOT::rmsY() const 
{
  return (double)_histogram->GetRMS( (Int_t)2 );
}

double IHistogram3DROOT::rmsZ() const 
{
  return (double)_histogram->GetRMS( (Int_t)3 );
}

const IAxis & IHistogram3DROOT::xAxis() const
{
  return *_xAxis;
}

const IAxis & IHistogram3DROOT::yAxis() const
{
  return *_yAxis;
}

const IAxis & IHistogram3DROOT::zAxis() const
{
  return *_zAxis;
}

int IHistogram3DROOT::coordToIndexX(double coord) const 
{
  TH1 *xProj;
  int xBin;

  xProj = _histogram->Project3D("x");
  xBin = (int)xProj->FindBin( (Axis_t)coord );

  delete xProj;
  return xBin;
}

int IHistogram3DROOT::coordToIndexY(double coord) const 
{
  TH1 *yProj;
  int yBin;

  yProj = _histogram->Project3D("y");
  yBin = (int)yProj->FindBin( (Axis_t)coord );

  delete yProj;
  return yBin;
}

int IHistogram3DROOT::coordToIndexZ(double coord) const 
{
  TH1 *zProj;
  int zBin;

  zProj = _histogram->Project3D("z");
  zBin = (int)zProj->FindBin( (Axis_t)coord );

  delete zProj;
  return zBin;
}

// ---------------------------------------------------------------------------
// Functions from IBaseHistogram.h
// ---------------------------------------------------------------------------

std::string IHistogram3DROOT::title() const 
{
  string a(_histogram->GetTitle());
  return a;
}

bool IHistogram3DROOT::setTitle(const std::string & title) 
{
  _histogram->SetTitle( title.c_str() );
  _histogramAIDA->SetTitle( Naming::titleBinEntry(title).c_str() );
  _histogramAIDABinMeanX->SetTitle( Naming::titleBinMeanX(title).c_str() );
  _histogramAIDABinMeanY->SetTitle( Naming::titleBinMeanY(title).c_str() );
  _histogramAIDABinMeanZ->SetTitle( Naming::titleBinMeanZ(title).c_str() );
  return true;
}

bool IHistogram3DROOT::setName(const std::string & name) 
{
  _histogram->SetName( name.c_str() );
  _histogramAIDA->SetName( Naming::binEntry(name).c_str() );
  _histogramAIDABinMeanX->SetName( Naming::binMeanX(name).c_str() );
  _histogramAIDABinMeanY->SetName( Naming::binMeanY(name).c_str() );
  _histogramAIDABinMeanZ->SetName( Naming::binMeanZ(name).c_str() );
  return true;
}

int IHistogram3DROOT::dimension() const 
{
  return (int)_histogram->GetDimension();
}

bool IHistogram3DROOT::reset() 
{
  _histogram->Reset("");
  _histogramAIDA->Reset("");
  _histogramAIDABinMeanX->Reset("");
  _histogramAIDABinMeanY->Reset("");
  _histogramAIDABinMeanZ->Reset("");
  return true;
}

int IHistogram3DROOT::entries() const 
{
  double integral = 0;
  for ( int i=1 ; i<=(int)_histogramAIDA->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogramAIDA->GetNbinsY() ; j++ )
        {
	  for ( int k=1 ; k<=(int)_histogramAIDA->GetNbinsZ() ; k++ )
	    {
	      integral += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k );
	    }
        }
    }
  return (int)integral;
}

// ---------------------------------------------------------------------------
// Functions from IHistogram.h
// ---------------------------------------------------------------------------

int IHistogram3DROOT::allEntries() const 
{
  return (int)_histogramAIDA->GetEntries();
}

int IHistogram3DROOT::extraEntries() const 
{
  // xy-ebene mit 2*2 raendern
  // xz-ebene mit 1*2 Raendern entlang z
  // yz-ebene ohne rand

  double noExtra = 0.;

  // sum over xy-planes 
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++ )
    {
      for ( int j=0 ; j<=((int)_histogramAIDA->GetNbinsY()+1) ; j++ )
	{
	  noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)0 );
          noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j,((Int_t)_histogramAIDA->GetNbinsZ() + 1) );
	}
    }

  // sum over xz-planes 
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogramAIDA->GetNbinsZ() ; j++ )
	{
	  noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)0,(Int_t)j );
          noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)i,((Int_t)_histogramAIDA->GetNbinsY() + 1),(Int_t)j );
	}
    }

  // sum over yz-planes 
  for ( int i=1 ; i<=(int)_histogramAIDA->GetNbinsY() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogramAIDA->GetNbinsZ() ; j++ )
	{
	  noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)0,(Int_t)i,(Int_t)j );
          noExtra += (double)_histogramAIDA->GetBinContent( ((Int_t)_histogramAIDA->GetNbinsX() + 1),(Int_t)i,(Int_t)j );
	}
    }
  return (int)noExtra;
}

double IHistogram3DROOT::sumBinHeights() const 
{
  double integral = 0;
  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
	  for ( int k=1 ; k<=(int)_histogram->GetNbinsZ() ; k++ )
	    {
	      integral += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k );
	    }
        }
    }
  return integral;
}

double IHistogram3DROOT::sumAllBinHeights() const 
{
  double integral = 0;
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsY()+1) ; j++ )
        {
	  for ( int k=0 ; k<=((int)_histogram->GetNbinsZ()+1) ; k++ )
	    {
	      integral += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k );
	    }
        }
    }
  return integral;
}

double IHistogram3DROOT::sumExtraBinHeights() const 
{
  // xy-ebene mit 2*2 raendern
  // xz-ebene mit 1*2 Raendern entlang z
  // yz-ebene ohne rand

  double noExtra = 0.;

  // sum over xy-planes 
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsY()+1) ; j++ )
	{
	  noExtra += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)0 );
          noExtra += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,((Int_t)_histogram->GetNbinsZ() + 1) );
	}
    }

  // sum over xz-planes 
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsZ() ; j++ )
	{
	  noExtra += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)0,(Int_t)j );
          noExtra += (double)_histogram->GetBinContent( (Int_t)i,((Int_t)_histogram->GetNbinsY() + 1),(Int_t)j );
	}
    }

  // sum over yz-planes 
  for ( int i=1 ; i<=(int)_histogram->GetNbinsY() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsZ() ; j++ )
	{
	  noExtra += (double)_histogram->GetBinContent( (Int_t)0,(Int_t)i,(Int_t)j );
          noExtra += (double)_histogram->GetBinContent( ((Int_t)_histogram->GetNbinsX() + 1),(Int_t)i,(Int_t)j );
	}
    }
  return noExtra;
}

double IHistogram3DROOT::minBinHeight() const 
{
  double minHeight;
  minHeight = (double)_histogram->GetBinContent( (Int_t)1,(Int_t)1,(Int_t)1 );

  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
	  for ( int k=1 ; k<=(int)_histogram->GetNbinsZ() ; k++ )
	    {
	      if ( (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k ) < minHeight)
		{
		  minHeight = (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k );
		}
	    }
        }
    }
  return minHeight;
}

double IHistogram3DROOT::maxBinHeight() const 
{
  double maxHeight;
  maxHeight = (double)_histogram->GetBinContent( (Int_t)1,(Int_t)1,(Int_t)1 );

  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
	  for ( int k=1 ; k<=(int)_histogram->GetNbinsZ() ; k++ )
	    {
	      if ( (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k ) > maxHeight)
		{
		  maxHeight = (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j,(Int_t)k );
		}
	    }
        }
    }
  return maxHeight;
}

bool IHistogram3DROOT::scale(double scaleFactor) 
{
  /// FIXME! richtige beruecksichtigung der Fehler im Zusammenhang mit dcale!
  _histogram->Scale( (Double_t)scaleFactor );
  return true;
}

bool IHistogram3DROOT::add(const IHistogram3D & hist) 
{
  if (xAxis().bins() != hist.xAxis().bins() ) return false;
  if (yAxis().bins() != hist.yAxis().bins() ) return false;
  if (zAxis().bins() != hist.zAxis().bins() ) return false;

  IHistogram3DROOT const * localhist = dynamic_cast<const IHistogram3DROOT*>(&hist);

  for (int i=0 ; i<=_histogramAIDABinMeanX->GetNbinsX()+1 ; i++)
    {
      for (int j=0 ; j<=_histogramAIDABinMeanX->GetNbinsY()+1 ; j++)
	{
	  for (int k=0 ; k<=_histogramAIDABinMeanX->GetNbinsZ()+1 ; k++)
	    {
	      double binMeanX1 = (double)_histogramAIDABinMeanX->GetBinContent(i,j,k);
	      double binMeanX2 = (double)localhist->_histogramAIDABinMeanX->GetBinContent(i,j,k);
	      double binMeanY1 = (double)_histogramAIDABinMeanY->GetBinContent(i,j,k);
	      double binMeanY2 = (double)localhist->_histogramAIDABinMeanY->GetBinContent(i,j,k);
	      double binMeanZ1 = (double)_histogramAIDABinMeanZ->GetBinContent(i,j,k);
	      double binMeanZ2 = (double)localhist->_histogramAIDABinMeanZ->GetBinContent(i,j,k);

	      double weight1 = (double)_histogram->GetBinContent(i,j,k);
	      double weight2 = (double)localhist->_histogram->GetBinContent(i,j,k);

	      double newBinMeanX = 
		(binMeanX1 * weight1 + binMeanX2 * weight2)/(weight1+weight2);
	      double newBinMeanY = 
		(binMeanY1 * weight1 + binMeanY2 * weight2)/(weight1+weight2);
	      double newBinMeanZ = 
		(binMeanZ1 * weight1 + binMeanZ2 * weight2)/(weight1+weight2);
	      _histogramAIDABinMeanX->SetBinContent( (Int_t)i,(Int_t)j,(Int_t)k, (Double_t)newBinMeanX );
	      _histogramAIDABinMeanY->SetBinContent( (Int_t)i,(Int_t)j,(Int_t)k, (Double_t)newBinMeanY );
	      _histogramAIDABinMeanZ->SetBinContent( (Int_t)i,(Int_t)j,(Int_t)k, (Double_t)newBinMeanZ );
	    }
	}
    }
  _histogram->Add(localhist->_histogram);
  _histogramAIDA->Add(localhist->_histogramAIDA);

  return true;
}
