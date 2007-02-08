#include <RAIDA/IProfile2DROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/IAxisROOT.h>
#include <RAIDA/RAIDAUtil.h>
#include <RAIDA/AIDAHistogramsInROOT.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

IProfile2DROOT::IProfile2DROOT(const std::string & name,
			       const std::string & title,
			       int nBinsX,
			       double lowerEdgeX,
			       double upperEdgeX,
			       int nBinsY,
			       double lowerEdgeY,
			       double upperEdgeY,
			       const std::string & options)
{
  _profile = new TProfile2D(name.c_str(),
			    title.c_str(),
			    (Int_t)nBinsX,
			    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
			    (Int_t)nBinsY,
			    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);

  Profile2DHistograms(name,title,
		      nBinsX,lowerEdgeX,upperEdgeX,
		      nBinsY,lowerEdgeY,upperEdgeY);
}

IProfile2DROOT::IProfile2DROOT(const std::string & name,
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
  _profile = new TProfile2D(name.c_str(),
			    title.c_str(),
			    (Int_t)nBinsX,
			    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
			    (Int_t)nBinsY,
			    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY,
			    (Axis_t)lowerValue,(Axis_t)upperValue);

  Profile2DHistograms(name,title,
		      nBinsX,lowerEdgeX,upperEdgeX,
		      nBinsY,lowerEdgeY,upperEdgeY);
}

IProfile2DROOT::IProfile2DROOT(const std::string & name,
			       const std::string & title,
			       const std::vector<double>  & binEdgesX,
			       const std::vector<double>  & binEdgesY,
			       const std::string & options)
{
  const int nBinsX = binEdgesX.size()-1;
  const int nBinsY = binEdgesY.size()-1;
  Double_t xBins[nBinsX+1];
  Double_t yBins[nBinsY+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdgesX[i];
  for (int i=0;i<=nBinsY;i++)
    yBins[i] = binEdgesY[i];

  _profile = new TProfile2D(name.c_str(),
			    title.c_str(),
			    (Int_t)nBinsX,xBins,
			    (Int_t)nBinsY,yBins);

  Profile2DHistograms(name,title,binEdgesX,binEdgesY);
}

IProfile2DROOT::IProfile2DROOT(const std::string & name,
			       const std::string & title,
			       const std::vector<double>  & binEdgesX,
			       const std::vector<double>  & binEdgesY,
			       double lowerValue,
			       double upperValue,
			       const std::string & options)
{
  const int nBinsX = binEdgesX.size()-1;
  const int nBinsY = binEdgesY.size()-1;
  Double_t xBins[nBinsX+1];
  Double_t yBins[nBinsY+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdgesX[i];
  for (int i=0;i<=nBinsY;i++)
    yBins[i] = binEdgesY[i];

  _profile = new TProfile2D(name.c_str(),
			    title.c_str(),
			    (Int_t)nBinsX,xBins,
			    (Int_t)nBinsY,yBins);
    //			    (Double_t)lowerValue,(Double_t)upperValue);

  Profile2DHistograms(name,title,binEdgesX,binEdgesY);
}

IProfile2DROOT::IProfile2DROOT(const std::string & name,
			       const IProfile2DROOT & profile) 
{
  _profile = (TProfile2D*)profile._profile->Clone( name.c_str() );
  _histogram = (TH2D*)profile._histogram->Clone( Naming::binContents(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogram->SetDirectory(0);
  _histogramAIDA = (TH2D*)profile._histogramAIDA->Clone( Naming::binEntry(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogramAIDA->SetDirectory(0);
  _histogramAIDABinMeanX = (TH2D*)profile._histogramAIDABinMeanX->Clone( Naming::binMeanX(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanX->SetDirectory(0);
  _histogramAIDABinMeanY = (TH2D*)profile._histogramAIDABinMeanY->Clone( Naming::binMeanY(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanY->SetDirectory(0);
  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  if ( profile._xAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;

  _yAxis = new IAxisROOT( _profile->GetYaxis() );
  if ( profile._yAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning() ;
}

void IProfile2DROOT::Profile2DHistograms(const std::string & name,
					 const std::string & title,
					 int nBinsX,
					 double lowerEdgeX,
					 double upperEdgeX,
					 int nBinsY,
					 double lowerEdgeY,
					 double upperEdgeY)
{
  _histogram = new TH2D(Naming::binContents(name).c_str(),
                        Naming::titleBinContents(title).c_str(),
			(Int_t)nBinsX,
			(Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
			(Int_t)nBinsY,
			(Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  if (!AIDAHistogramsInROOT)
    _histogram->SetDirectory(0);
  _histogramAIDA = new TH2D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
                            (Int_t)nBinsX,
                            (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
                            (Int_t)nBinsY,
                            (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  if (!AIDAHistogramsInROOT)
    _histogramAIDA->SetDirectory(0);
  _histogramAIDABinMeanX = new TH2D(Naming::binMeanX(name).c_str(),
                                    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanX->SetDirectory(0);
  _histogramAIDABinMeanY = new TH2D(Naming::binMeanY(name).c_str(),
                                    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanY->SetDirectory(0);
  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();

  _yAxis = new IAxisROOT( _profile->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
}

void IProfile2DROOT::Profile2DHistograms(const std::string & name,
					 const std::string & title,
					 const std::vector<double>  & binEdgesX,
					 const std::vector<double>  & binEdgesY)
{
  const int nBinsX = binEdgesX.size()-1;
  const int nBinsY = binEdgesY.size()-1;
  Double_t xBins[nBinsX+1];
  Double_t yBins[nBinsY+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdgesX[i];
  for (int i=0;i<=nBinsY;i++)
    yBins[i] = binEdgesY[i];

  _histogram = new TH2D(Naming::binContents(name).c_str(),
                        Naming::titleBinContents(title).c_str(),
			(Int_t)nBinsX,xBins,
                        (Int_t)nBinsY,yBins);
  if (!AIDAHistogramsInROOT)
    _histogram->SetDirectory(0);
  _histogramAIDA = new TH2D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,xBins,
			    (Int_t)nBinsY,yBins);
  if (!AIDAHistogramsInROOT)
    _histogramAIDA->SetDirectory(0);
  _histogramAIDABinMeanX = new TH2D(Naming::binMeanX(name).c_str(),
                                    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins);
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanX->SetDirectory(0);
  _histogramAIDABinMeanY = new TH2D(Naming::binMeanY(name).c_str(),
                                    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins);
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanY->SetDirectory(0);
  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning();

  _yAxis = new IAxisROOT( _profile->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning();
}

bool IProfile2DROOT::fill(double x, double y, double z, double weight) 
{
  if (weight<0) {  return false; }

  int    iBin = (int)_histogram->FindBin( (Axis_t)x,(Axis_t)y );
  double iBinHeight = (double)_histogram->GetBinContent(iBin);
  double newBinMeanX, oldBinMeanX, newBinMeanY, oldBinMeanY;

  oldBinMeanX = (double)_histogramAIDABinMeanX->GetBinContent(iBin);
  newBinMeanX = (oldBinMeanX * iBinHeight + x*weight)/(weight+iBinHeight);
  oldBinMeanY = (double)_histogramAIDABinMeanY->GetBinContent(iBin);
  newBinMeanY = (oldBinMeanY * iBinHeight + y*weight)/(weight+iBinHeight);

  _histogramAIDABinMeanX->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanX );
  _histogramAIDABinMeanY->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanY );
  _profile->Fill( (Axis_t)x,(Axis_t)y,(Stat_t)weight );
  _histogram->Fill( (Axis_t)x,(Axis_t)y,(Stat_t)weight );
  _histogramAIDA->Fill( (Axis_t)x,(Axis_t)y,(Stat_t)1. );
  return true;
}

double IProfile2DROOT::binMeanX(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogramAIDABinMeanX->GetBinContent( (Int_t)indexXROOT,
                                                        (Int_t)indexYROOT );
}

double IProfile2DROOT::binMeanY(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogramAIDABinMeanY->GetBinContent( (Int_t)indexXROOT,
                                                        (Int_t)indexYROOT );
}

int IProfile2DROOT::binEntries(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (int)_histogramAIDA->GetBinContent( (Int_t)indexXROOT,
					     (Int_t)indexYROOT );
}

int IProfile2DROOT::binEntriesX(int indexX) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());

  double sumX = 0;
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogramAIDA->GetBinContent( (Int_t)indexXROOT,(Int_t)i );
    }
  return (int)sumX;
}

int IProfile2DROOT::binEntriesY(int indexY) const 
{
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  double sumY = 0;
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)indexYROOT );
    }
  return (int)sumY;
}

double IProfile2DROOT::binHeight(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_profile->GetBinContent(_profile->GetBin( (Int_t)indexXROOT,
							   (Int_t)indexYROOT ));
}

double IProfile2DROOT::binHeightX(int indexX) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());

  double sumX = 0;
  for ( int i=0 ; i<=((int)_histogram->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogram->GetBinContent( (Int_t)indexXROOT,(Int_t)i );
    }
  return sumX;
}

double IProfile2DROOT::binHeightY(int indexY) const 
{
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  double sumY = 0;
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)indexYROOT );
    }
  return sumY;
}

double IProfile2DROOT::binError(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogram->GetBinError( (Int_t)indexXROOT,
					  (Int_t)indexYROOT );
}

double IProfile2DROOT::binRms(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_profile->GetBinError( (Int_t)indexXROOT,
					(Int_t)indexYROOT );
}

double IProfile2DROOT::meanX() const 
{
  return (double)_profile->GetMean( (Int_t)1 );
}

double IProfile2DROOT::meanY() const 
{
  return (double)_profile->GetMean( (Int_t)2 );
}

double IProfile2DROOT::rmsX() const 
{
  return (double)_profile->GetRMS( (Int_t)1 );
}

double IProfile2DROOT::rmsY() const 
{
  return (double)_profile->GetRMS( (Int_t)2 );
}

const IAxis & IProfile2DROOT::xAxis() const
{
  return *_xAxis;
}

const IAxis & IProfile2DROOT::yAxis() const
{
  return *_yAxis;
}

int IProfile2DROOT::coordToIndexX(double coordX) const 
{
  TH1D *xProj = _histogram->ProjectionX("_temphisto");
  int indexROOT = (int)xProj->FindBin( (Axis_t)coordX );

  delete xProj;
  return RAIDAUtil::binIndexROOT2AIDA(indexROOT,xAxis().bins());
}

int IProfile2DROOT::coordToIndexY(double coordY) const 
{
  TH1D *yProj = _histogram->ProjectionY("_temphisto");
  int indexROOT = (int)yProj->FindBin( (Axis_t)coordY );

  delete yProj;
  return RAIDAUtil::binIndexROOT2AIDA(indexROOT,yAxis().bins());
}

int IProfile2DROOT::allEntries() const 
{
  return (int)_histogramAIDA->GetEntries();
}

int IProfile2DROOT::extraEntries() const 
{
  double noExtra = 0.;

  /*
   sum of extra-bins:
   i   = bins of the Histogram
   x/X = extra bins of the histogram
   The first loop will add alog the x, the second alog the y direction. 
   to not count the bins at the corners two times the loop runs once only 
   from 1 to n!

       |  0  |  1  |  2  | ... |  n  | n+1
   ---------------------------------------- (x)
   0   |  X  |  X  |  X  |  X  |  X  |  X
   1   |  x  |  i  |  i  |  i  |  i  |  x
   2   |  x  |  i  |  i  |  i  |  i  |  x
   ... | ... 
   n   |  x  |  i  |  i  |  i  |  i  |  x
   n+1 |  X  |  X  |  X  |  X  |  X  |  X
      (y)
   */

  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++ )
    {
      noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)0 ); 
      noExtra += (double)_histogramAIDA->GetBinContent
          ( (Int_t)i,((Int_t)_histogramAIDA->GetNbinsY() + 1) ); 
    }

  /*
   sum of extra-bins:
       |  0  |  1  |  2  | ... |  n  | n+1
   ---------------------------------------- (x)
   0   |  x  |  x  |  x  |  x  |  x  |  x
   1   |  X  |  i  |  i  |  i  |  i  |  X
   2   |  X  |  i  |  i  |  i  |  i  |  X
   ... | ... 
   n   |  X  |  i  |  i  |  i  |  i  |  X
   n+1 |  x  |  x  |  x  |  x  |  x  |  x
      (y)
   */

  for ( int i=1 ; i<=(int)_histogramAIDA->GetNbinsY() ; i++ )
    {
      noExtra += (double)_histogramAIDA->GetBinContent( (Int_t)0,(Int_t)i ); 
      noExtra += (double)_histogramAIDA->GetBinContent
          ( ((Int_t)_histogramAIDA->GetNbinsX() + 1),(Int_t)i ); 
    }

  return (int)noExtra;
}

double IProfile2DROOT::sumBinHeights() const 
{
  double integral = 0.;

  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
          integral += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j );
        }
    }
  return integral;
}

double IProfile2DROOT::sumAllBinHeights() const 
{
  double integral = 0.;

  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsY()+1) ; j++ )
        {
          integral += (double)_histogram->GetBinContent(i,j);
        }
    }
  return integral;
}

double IProfile2DROOT::sumExtraBinHeights() const 
{
  double intExtra = 0.;

  /*
   sum of extra-bins:
   i   = bins of the Histogram
   x/X = extra bins of the histogram
   The first loop will add alog the x, the second alog the y direction. 
   to not count the bins at the corners two times the loop runs once only 
   from 1 to n!

       |  0  |  1  |  2  | ... |  n  | n+1
   ---------------------------------------- (x)
   0   |  X  |  X  |  X  |  X  |  X  |  X
   1   |  x  |  i  |  i  |  i  |  i  |  x
   2   |  x  |  i  |  i  |  i  |  i  |  x
   ... | ... 
   n   |  x  |  i  |  i  |  i  |  i  |  x
   n+1 |  X  |  X  |  X  |  X  |  X  |  X
      (y)
   */

  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      intExtra += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)0 ); 
      intExtra += (double)_histogram->GetBinContent
          ( (Int_t)i,((Int_t)_histogram->GetNbinsY() + 1) ); 
    }

  /*
   sum of extra-bins:
       |  0  |  1  |  2  | ... |  n  | n+1
   ---------------------------------------- (x)
   0   |  x  |  x  |  x  |  x  |  x  |  x
   1   |  X  |  i  |  i  |  i  |  i  |  X
   2   |  X  |  i  |  i  |  i  |  i  |  X
   ... | ... 
   n   |  X  |  i  |  i  |  i  |  i  |  X
   n+1 |  x  |  x  |  x  |  x  |  x  |  x
      (y)
   */

  for ( int i=1 ; i<=(int)_histogram->GetNbinsY() ; i++ )
    {
      intExtra += (double)_histogram->GetBinContent( (Int_t)0,(Int_t)i ); 
      intExtra += (double)_histogram->GetBinContent
          ( ((Int_t)_histogramAIDA->GetNbinsX() + 1),(Int_t)i ); 
    }

  return intExtra;
}

double IProfile2DROOT::minBinHeight() const 
{
  double minHeight;
  minHeight = (double)_histogram->GetBinContent( (Int_t)1,(Int_t)1 );

  for (int i = 1; i<=(int)_histogram->GetNbinsX();i++)
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
          if ( (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j ) < minHeight)
            {
              minHeight = (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j );
            }
        }
    }
  return minHeight;
}

double IProfile2DROOT::maxBinHeight() const 
{
  double maxHeight;
  maxHeight = (double)_histogram->GetBinContent( (Int_t)1,(Int_t)1 );

  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++)
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
        {
          if ( (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j ) > maxHeight)
            {
              maxHeight = (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j );
            }
        }
    }
  return maxHeight;
}

std::string IProfile2DROOT::title() const 
{
  string a(_profile->GetTitle());
  return a;
}

bool IProfile2DROOT::setTitle(const std::string & title) 
{
  _profile->SetTitle( title.c_str() );
  _histogram->SetTitle( Naming::titleBinContents(title).c_str() );
  _histogramAIDA->SetTitle( Naming::titleBinEntry(title).c_str() );
  _histogramAIDABinMeanX->SetTitle( Naming::titleBinMeanX(title).c_str() );
  _histogramAIDABinMeanY->SetTitle( Naming::titleBinMeanY(title).c_str() );
  return true;
}

int IProfile2DROOT::dimension() const 
{
  return (int)_profile->GetDimension();
}

bool IProfile2DROOT::reset() 
{
  _profile->Reset("");
  _histogram->Reset("");
  _histogramAIDA->Reset("");
  _histogramAIDABinMeanX->Reset("");
  _histogramAIDABinMeanY->Reset("");
  return true;
}

int IProfile2DROOT::entries() const 
{
  double integral = 0.;

  for ( int i=1 ; i<=(int)_histogramAIDA->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogramAIDA->GetNbinsY() ; j++ )
        {
          integral += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j );
        }
    }
  return (int)integral;
}
