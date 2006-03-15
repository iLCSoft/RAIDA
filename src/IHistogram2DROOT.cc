#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/IAxisROOT.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

IHistogram2DROOT::IHistogram2DROOT(const std::string & name,
				   const std::string & title,
				   int nBinsX,
				   double lowerEdgeX,
				   double upperEdgeX,
				   int nBinsY,
				   double lowerEdgeY,
				   double upperEdgeY,
				   const std::string & options) 
{
  _histogram = new TH2D(name.c_str(),title.c_str(),
			(Int_t)nBinsX,(Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
                        (Int_t)nBinsY,(Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  _histogramAIDA = new TH2D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,
			    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
			    (Int_t)nBinsY,
			    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  _histogramAIDABinMeanX = new TH2D(Naming::binMeanX(name).c_str(),
				    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);
  _histogramAIDABinMeanY = new TH2D(Naming::binMeanY(name).c_str(),
				    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,
				    (Axis_t)lowerEdgeX,(Axis_t)upperEdgeX,
				    (Int_t)nBinsY,
				    (Axis_t)lowerEdgeY,(Axis_t)upperEdgeY);

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
  _yAxis = new IAxisROOT( _histogram->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
}

IHistogram2DROOT::IHistogram2DROOT(const std::string & name,
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

  _histogram = new TH2D(name.c_str(),title.c_str(),
			(Int_t)nBinsX,xBins,
                        (Int_t)nBinsY,yBins);
  _histogramAIDA = new TH2D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,xBins,
			    (Int_t)nBinsY,yBins);
  _histogramAIDABinMeanX = new TH2D(Naming::binMeanX(name).c_str(),
				    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins);
  _histogramAIDABinMeanY = new TH2D(Naming::binMeanY(name).c_str(),
				    Naming::titleBinMeanY(title).c_str(),
				    (Int_t)nBinsX,xBins,
				    (Int_t)nBinsY,yBins);
  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning();
  _yAxis = new IAxisROOT( _histogram->GetYaxis() );
  dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning();
}

IHistogram2DROOT::IHistogram2DROOT(const std::string & name,
				   const IHistogram2DROOT & hist) 
{
  _histogram = (TH2D*)hist._histogram->Clone( name.c_str() );
  _histogramAIDA = (TH2D*)hist._histogramAIDA->Clone( Naming::binEntry(name).c_str() );
  _histogramAIDABinMeanX = (TH2D*)hist._histogramAIDABinMeanX->Clone( Naming::binMeanX(name).c_str() );
  _histogramAIDABinMeanY = (TH2D*)hist._histogramAIDABinMeanY->Clone( Naming::binMeanY(name).c_str() );

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
}

string IHistogram2DROOT::title() const
{
  string a(_histogram->GetTitle());
  return a;
}

bool IHistogram2DROOT::setTitle(const std::string & title)
{
  _histogram->SetTitle( title.c_str() );
  _histogramAIDA->SetTitle( Naming::titleBinEntry(title).c_str() );
  _histogramAIDABinMeanX->SetTitle( Naming::titleBinMeanX(title).c_str() );
  _histogramAIDABinMeanY->SetTitle( Naming::titleBinMeanY(title).c_str() );
  return true;
}

bool IHistogram2DROOT::setName(const std::string & name) 
{
  _histogram->SetName( name.c_str() );
  _histogramAIDA->SetName( Naming::binEntry(name).c_str() );
  _histogramAIDABinMeanX->SetName( Naming::binMeanX(name).c_str() );
  _histogramAIDABinMeanY->SetName( Naming::binMeanY(name).c_str() );
  return true;
}

int IHistogram2DROOT::dimension() const
{
  return (int)_histogram->GetDimension();
}

bool IHistogram2DROOT::reset()
{
  _histogram->Reset("");
  _histogramAIDA->Reset("");
  _histogramAIDABinMeanX->Reset("");
  _histogramAIDABinMeanY->Reset("");
  return true;
}

int IHistogram2DROOT::entries() const
{
  double integral;
  integral = 0.;

  for ( int i=1 ; i<=(int)_histogramAIDA->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogramAIDA->GetNbinsY() ; j++ )
	{
	  integral += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)j );
	}
    }
  return (int)integral;
}

int IHistogram2DROOT::allEntries() const
{
  return (int)_histogramAIDA->GetEntries();
}

int IHistogram2DROOT::extraEntries() const 
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

double IHistogram2DROOT::sumBinHeights() const 
{
  double integral;
  integral = 0.;

  for ( int i=1 ; i<=(int)_histogram->GetNbinsX() ; i++ )
    {
      for ( int j=1 ; j<=(int)_histogram->GetNbinsY() ; j++ )
	{
	  integral += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)j );
	}
    }
  return integral;
}

double IHistogram2DROOT::sumAllBinHeights() const 
{
  double integral;
  integral = 0.;

  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++ )
    {
      for ( int j=0 ; j<=((int)_histogram->GetNbinsY()+1) ; j++ )
	{
	  integral += (double)_histogram->GetBinContent(i,j);
	}
    }
  return integral;
}

double IHistogram2DROOT::sumExtraBinHeights() const 
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

double IHistogram2DROOT::minBinHeight() const 
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

double IHistogram2DROOT::maxBinHeight() const 
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

bool IHistogram2DROOT::scale(double scaleFactor)
{
  /// FIXME! richtige beruecksichtigung der Fehler im Zusammenhang mit dcale!
  _histogram->Scale( (Double_t)scaleFactor );
  return true;
}

bool IHistogram2DROOT::fill(double x, double y, double weight)
{
  // only fill if weight is positiv
  if (weight<0) {  return false; }

  int iBin = (int)_histogram->FindBin( (Axis_t)x,(Axis_t)y );
  double iBinHeight = (double)_histogram->GetBinContent(iBin);
  double newBinMeanX, oldBinMeanX, newBinMeanY, oldBinMeanY;
  oldBinMeanX = (double)_histogramAIDABinMeanX->GetBinContent(iBin);
  newBinMeanX = (oldBinMeanX * iBinHeight + x*weight)/(weight+iBinHeight);
  oldBinMeanY = (double)_histogramAIDABinMeanY->GetBinContent(iBin);
  newBinMeanY = (oldBinMeanY * iBinHeight + y*weight)/(weight+iBinHeight);

  _histogramAIDABinMeanX->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanX );
  _histogramAIDABinMeanY->SetBinContent( (Int_t)iBin, (Stat_t)newBinMeanY );
  _histogram->Fill( (Axis_t)x,(Axis_t)y,(Stat_t)weight );
  _histogramAIDA->Fill( (Axis_t)x,(Axis_t)y,(Stat_t)1. );
  return true;
}

double IHistogram2DROOT::binMeanX(int indexX, int indexY) const 
{
  return (double)_histogramAIDABinMeanX->GetBinContent( (Int_t)indexX,
                                                        (Int_t)indexY );
}

double IHistogram2DROOT::binMeanY(int indexX, int indexY) const 
{
  return (double)_histogramAIDABinMeanY->GetBinContent( (Int_t)indexX,
                                                        (Int_t)indexY );
}

int IHistogram2DROOT::binEntries(int indexX, int indexY) const 
{
  double binCount;
  binCount = (double)_histogramAIDA->GetBinContent( (Int_t)indexX,(Int_t)indexY);
  return (int)binCount;
}

int IHistogram2DROOT::binEntriesX(int index) const 
{
  double sumX = 0;
  if (index < 0 || index > ((int)_histogramAIDA->GetNbinsX()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogramAIDA->GetBinContent( (Int_t)index,(Int_t)i );
    }
  return (int)sumX;
}

int IHistogram2DROOT::binEntriesY(int index) const 
{
  double sumY = 0;
  if (index < 0 || index > ((int)_histogramAIDA->GetNbinsY()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)index );
    }
  return (int)sumY;
}

double IHistogram2DROOT::binHeight(int indexX, int indexY) const 
{
  if ( (indexX < 0 || indexX > ((int)_histogram->GetNbinsX()+1)) ||
       (indexY < 0 || indexY > ((int)_histogram->GetNbinsY()+1)) )
    {
      return -99999;
    }
  return (double)_histogram->GetBinContent( (Int_t)indexX,(Int_t)indexY );
}

double IHistogram2DROOT::binHeightX(int index) const 
{
  double sumX = 0;
  if (index < 0 || index > ((int)_histogram->GetNbinsX()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogram->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogram->GetBinContent( (Int_t)index,(Int_t)i );
    }
  return sumX;
}

double IHistogram2DROOT::binHeightY(int index) const 
{
  double sumY = 0;
  if (index < 0 || index < ((int)_histogram->GetNbinsY()+1))
    {
      return -99999;
    }
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)index );
    }
  return sumY;
}

double IHistogram2DROOT::binError(int indexX, int indexY) const 
{
  return (double)_histogram->GetBinError( (Int_t)indexX,(Int_t)indexY );
}

double IHistogram2DROOT::meanX() const 
{
  return (double)_histogram->GetMean( (Int_t)1 );
}

double IHistogram2DROOT::meanY() const 
{
  return (double)_histogram->GetMean( (Int_t)2 );
}

double IHistogram2DROOT::rmsX() const 
{
  return (double)_histogram->GetRMS( (Int_t)1 );
}

double IHistogram2DROOT::rmsY() const 
{
  return (double)_histogram->GetRMS( (Int_t)2 );
}

const IAxis & IHistogram2DROOT::xAxis() const
{
  return *_xAxis;
}

const IAxis & IHistogram2DROOT::yAxis() const
{
  return *_yAxis;
}

int IHistogram2DROOT::coordToIndexX(double coord) const 
{
  TH1D *xProj;
  int xBin; 

  xProj = _histogram->ProjectionX("_temphisto");
  xBin = (int)xProj->FindBin( (Axis_t)coord );

  delete xProj;
  return xBin; 
}

int IHistogram2DROOT::coordToIndexY(double coord) const 
{
  TH1D *yProj;
  int yBin; 

  yProj = _histogram->ProjectionY("_temphisto");
  yBin = (int)yProj->FindBin( (Axis_t)coord );

  delete yProj;
  return yBin; 
}

bool IHistogram2DROOT::add(const IHistogram2D & hist) 
{
  if (xAxis().bins() != hist.xAxis().bins() ) return false;
  if (yAxis().bins() != hist.yAxis().bins() ) return false;

  IHistogram2DROOT const * localhist = dynamic_cast<const IHistogram2DROOT*>(&hist);

  for (int i=0 ; i<=_histogramAIDABinMeanX->GetNbinsX()+1 ; i++)
    {
      for (int j=0 ; j<=_histogramAIDABinMeanX->GetNbinsY()+1 ; j++)
	{
	  double binMeanX1 = (double)_histogramAIDABinMeanX->GetBinContent(i,j);
	  double binMeanX2 = (double)localhist->_histogramAIDABinMeanX->GetBinContent(i,j);
	  double binMeanY1 = (double)_histogramAIDABinMeanY->GetBinContent(i,j);
	  double binMeanY2 = (double)localhist->_histogramAIDABinMeanY->GetBinContent(i,j);

	  double weight1 = (double)_histogram->GetBinContent(i,j);
	  double weight2 = (double)localhist->_histogram->GetBinContent(i,j);

	  double newBinMeanX = 
	    (binMeanX1 * weight1 + binMeanX2 * weight2)/(weight1+weight2);
	  double newBinMeanY = 
	    (binMeanY1 * weight1 + binMeanY2 * weight2)/(weight1+weight2);
	  _histogramAIDABinMeanX->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)newBinMeanX );
	  _histogramAIDABinMeanY->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)newBinMeanY );
	}
    }

  _histogram->Add(localhist->_histogram);
  _histogramAIDA->Add(localhist->_histogramAIDA);

  return true;
}
