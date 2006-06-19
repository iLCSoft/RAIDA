#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/IAxisROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/RAIDAUtil.h>
#include <iostream>
#include <TH1D.h>
#include <TDirectory.h>
#include <string>
#include <vector>

using namespace AIDA ;
using namespace std;

IHistogram1DROOT::IHistogram1DROOT(const std::string & name,
				   const std::string & title,
				   int nBins,
				   double lowerEdge,
				   double upperEdge,
				   const std::string & options) 
{
  _histogram = new TH1D(name.c_str(),
			title.c_str(), 
			(Int_t)nBins,(Axis_t)lowerEdge,
			(Axis_t)upperEdge);
  _histogramAIDA = new TH1D(Naming::binEntry(name).c_str(),
			    Naming::titleBinEntry(title).c_str(), 
			    (Int_t)nBins,(Axis_t)lowerEdge,
			    (Axis_t)upperEdge);
  _histogramAIDABinMean = new TH1D(Naming::binMeanX(name).c_str(),
				   Naming::titleBinMeanX(title).c_str(), 
				   (Int_t)nBins,(Axis_t)lowerEdge,
				   (Axis_t)upperEdge);
  //  gDirectory->ls();

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
}

IHistogram1DROOT::IHistogram1DROOT(const std::string & name,
				   const std::string & title,
				   const std::vector<double>  & binEdges,
				   const std::string & options) 
{
  const int nBinsX = binEdges.size()-1;
  Double_t xBins[nBinsX+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdges[i];

  _histogram = new TH1D(name.c_str(),
			title.c_str(), 
			(Int_t)nBinsX,xBins);
  _histogramAIDA = new TH1D(Naming::binEntry(name).c_str(),
			    Naming::titleBinEntry(title).c_str(), 
			    (Int_t)nBinsX,xBins);
  _histogramAIDABinMean = new TH1D(Naming::binMeanX(name).c_str(),
				   Naming::titleBinMeanX(title).c_str(), 
				   (Int_t)nBinsX,xBins);

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning();
}

IHistogram1DROOT::IHistogram1DROOT(const std::string & name,
				   const IHistogram1DROOT & hist) 
{
  _histogram = (TH1D*)hist._histogram->Clone( name.c_str() );
  _histogramAIDA = (TH1D*)hist._histogramAIDA->Clone( Naming::binEntry(name).c_str() );
  _histogramAIDABinMean = (TH1D*)hist._histogramAIDABinMean->Clone( Naming::binMeanX(name).c_str() );

  // create axis
  _xAxis = new IAxisROOT( _histogram->GetXaxis() );
  if ( hist._xAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
  else 
    dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
}

IHistogram1DROOT::IHistogram1DROOT(const std::string & name,
				   const IHistogram2DROOT & hist,
				   char axis,
				   int lowerBin,
				   int upperBin) 
{ // ######
  if (axis == 'x')
    {
      int index1ROOT = RAIDAUtil::binIndexAIDA2ROOT(lowerBin,hist.xAxis().bins());
      int index2ROOT = RAIDAUtil::binIndexAIDA2ROOT(upperBin,hist.xAxis().bins());

      _histogram = (TH1D*)hist._histogram->ProjectionX( name.c_str(), index1ROOT, index2ROOT );
      _histogramAIDA = (TH1D*)hist._histogramAIDA->ProjectionX( Naming::binEntry(name).c_str(), index1ROOT, index2ROOT );
      _histogramAIDABinMean = (TH1D*)hist._histogramAIDABinMeanX->ProjectionX( Naming::binMeanX(name).c_str(), index1ROOT, index2ROOT );
      _histogramAIDABinMean->Reset();
      for (int i=-2; i<hist.xAxis().bins(); i++)
	{
	  double binmean = 0, binhight = 0;
	  for (int j=-2; j<hist.yAxis().bins(); j++)
	    {
	      binmean += hist.binMeanX(i,j)*hist.binHeight(i,j);
	      binhight += hist.binHeight(i,j);
	    }
	  binmean = binmean / binhight;

	  // different bin index for root and AIDA:
	  _histogramAIDABinMean->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( i, hist.xAxis().bins() ), 
					       (Double_t)binmean );
	}

      // create axis
      _xAxis = new IAxisROOT( _histogram->GetXaxis() );
      if ( hist._xAxis->isFixedBinning() )
	dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
      else 
	dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
    }
  else if (axis == 'y')
    {
      int index1ROOT = RAIDAUtil::binIndexAIDA2ROOT(lowerBin,hist.yAxis().bins());
      int index2ROOT = RAIDAUtil::binIndexAIDA2ROOT(upperBin,hist.yAxis().bins());

      _histogram = (TH1D*)hist._histogram->ProjectionY( name.c_str(), index1ROOT, index2ROOT );
      _histogramAIDA = (TH1D*)hist._histogramAIDA->ProjectionY( Naming::binEntry(name).c_str(), index1ROOT, index2ROOT );
      _histogramAIDABinMean = (TH1D*)hist._histogramAIDABinMeanY->ProjectionY( Naming::binMeanX(name).c_str(), index1ROOT, index2ROOT );
      _histogramAIDABinMean->Reset();
      for (int j=-2; j<hist.yAxis().bins(); j++)
	{
	  double binmean = 0, binhight = 0;
	  for (int i=-2; i<hist.xAxis().bins(); i++)
	    {
	      binmean += hist.binMeanY(i,j)*hist.binHeight(i,j);
	      binhight += hist.binHeight(i,j);
	    }
	  binmean = binmean / binhight;

	  // different bin index for root and AIDA:
	  _histogramAIDABinMean->SetBinContent( (Int_t)RAIDAUtil::binIndexAIDA2ROOT( j, hist.yAxis().bins() ), 
						(Double_t)binmean );
	}

      // create axis
      _xAxis = new IAxisROOT( _histogram->GetXaxis() );
      if ( hist._yAxis->isFixedBinning() )
	dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
      else 
	dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
    }
  //  cout << "### histo da? " << _histogram->GetBinContent(1) << endl; 
}

bool IHistogram1DROOT::fill(double x, double weight)
{
  // only fill if weight is positiv 
  if (weight<0) {  return false; }

  int iBin = (int)_histogram->FindBin( (Axis_t)x );
  double iBinHeight = (double)_histogram->GetBinContent(iBin);
  double newBinMean, oldBinMean;
  oldBinMean = (double)_histogramAIDABinMean->GetBinContent(iBin);
  newBinMean = (oldBinMean * iBinHeight + x*weight)/(weight+iBinHeight);

  _histogramAIDABinMean->SetBinContent( (Int_t)iBin, (Stat_t)newBinMean );
  _histogram->Fill((Axis_t)x,(Stat_t)weight);
  _histogramAIDA->Fill((Axis_t)x,(Stat_t)1.);
  return true;

}

// ----------------------------------------------------------------------------
// from IBaseHistogram.h 
// ----------------------------------------------------------------------------

string IHistogram1DROOT::title() const
{
  string a(_histogram->GetTitle());
  return a;
}

bool IHistogram1DROOT::setTitle(const std::string & title)
{
  _histogram->SetTitle( title.c_str() );
  _histogramAIDA->SetTitle( Naming::titleBinEntry(title).c_str() );
  _histogramAIDABinMean->SetTitle( Naming::titleBinMeanX(title).c_str() );
  return true;
}

bool IHistogram1DROOT::setName(const std::string & name) 
{
  _histogram->SetName( name.c_str() );
  _histogramAIDA->SetName( Naming::binEntry(name).c_str() );
  _histogramAIDABinMean->SetName( Naming::binMeanX(name).c_str() );
  return true;
}

int IHistogram1DROOT::dimension() const 
{
  return (int)_histogram->GetDimension();
}

bool IHistogram1DROOT::reset()
{
  _histogram->Reset("");
  _histogramAIDA->Reset("");
  _histogramAIDABinMean->Reset("");
  return true;
}

int IHistogram1DROOT::entries() const 
{
  double integral;
  integral = 0.;

  for (int i = 1; i<=(int)_histogramAIDA->GetNbinsX();i++)
    {
      integral += (double)_histogramAIDA->GetBinContent(i);
    }
  return (int)integral;
}

int IHistogram1DROOT::allEntries() const 
{
  return (int)_histogramAIDA->GetEntries();
}

int IHistogram1DROOT::extraEntries() const 
{
  double extra;
  extra = (double)_histogramAIDA->GetBinContent(0)
    + (double)_histogramAIDA->GetBinContent( _histogramAIDA->GetNbinsX() + 1);
  return (int)extra;
}

double IHistogram1DROOT::sumBinHeights() const 
{
  double integral;
  integral = 0.;

  for (int i = 1; i<=(int)_histogram->GetNbinsX();i++)
    {
      integral += (double)_histogram->GetBinContent( (Int_t)i );
    }
  return integral;
}

double IHistogram1DROOT::sumAllBinHeights() const 
{
  double integralall;
  integralall = sumBinHeights() 
    + (double)_histogram->GetBinContent(0)
    + (double)_histogram->GetBinContent( _histogram->GetNbinsX() + 1);
  return integralall;
}

double IHistogram1DROOT::sumExtraBinHeights() const 
{
  double integralextra;

  integralextra = 
    + (double)_histogram->GetBinContent(0)
    + (double)_histogram->GetBinContent( _histogram->GetNbinsX() + 1);

  return integralextra;
}

double IHistogram1DROOT::minBinHeight() const 
{
  double minHeight;

  minHeight = (double)_histogram->GetBinContent(1);

  for (int i = 1; i<=(int)_histogram->GetNbinsX();i++)
    {
      if ((double)_histogram->GetBinContent(i) < minHeight)
	{
	  minHeight = (double)_histogram->GetBinContent(i);
	}
    }

  return minHeight;
}

double IHistogram1DROOT::maxBinHeight() const 
{
  double maxHeight;

  maxHeight = (double)_histogram->GetBinContent(1);

  for (int i = 1; i<=(int)_histogram->GetNbinsX();i++)
    {
      if ((double)_histogram->GetBinContent(i) > maxHeight)
	{
	  maxHeight = (double)_histogram->GetBinContent(i);
	}
    }

  return maxHeight;
}

bool IHistogram1DROOT::scale(double scaleFactor) 
{
  /// FIXME! richtige beruecksichtigung der Fehler im Zusammenhang mit dcale!
  _histogram->Scale( (Double_t)scaleFactor );
  return true;
}

// ---------------------------------------------------------------------------
// Functions from IHistogram1D.h
// ---------------------------------------------------------------------------

double IHistogram1DROOT::binMean(int index) const 
{ 
  int indexROOT = RAIDAUtil::binIndexAIDA2ROOT(index,axis().bins());
  return (double)_histogramAIDABinMean->GetBinContent(indexROOT);
}

int IHistogram1DROOT::binEntries(int index) const 
{
  int indexROOT = RAIDAUtil::binIndexAIDA2ROOT(index,axis().bins());
  return (int)_histogramAIDA->GetBinContent(indexROOT);
}

double IHistogram1DROOT::binHeight(int index) const 
{
  int indexROOT = RAIDAUtil::binIndexAIDA2ROOT(index,axis().bins());
  return (double)_histogram->GetBinContent( (Int_t)indexROOT );
}

double IHistogram1DROOT::binError(int index) const 
{
  int indexROOT = RAIDAUtil::binIndexAIDA2ROOT(index,axis().bins());
  return (double)_histogram->GetBinError(indexROOT);
}

double IHistogram1DROOT::mean() const 
{
  return (double)_histogram->GetMean();
}

double IHistogram1DROOT::rms() const 
{
  return (double)_histogram->GetRMS();
}

const IAxis & IHistogram1DROOT::axis() const 
{
  return *_xAxis;
}

int IHistogram1DROOT::coordToIndex(double coord) const 
{
  int indexROOT = (int)_histogram->FindBin( (Axis_t)coord );
  return RAIDAUtil::binIndexROOT2AIDA(indexROOT,axis().bins());
}

bool IHistogram1DROOT::add(const IHistogram1D & hist) 
{
  if ( axis().bins() != hist.axis().bins() ) return false;
  IHistogram1DROOT const * localhist = dynamic_cast<const IHistogram1DROOT*>(&hist);

  for (int i=0 ; i<=_histogramAIDABinMean->GetNbinsX()+1 ; i++)
    {
      double binMean1 = (double)_histogramAIDABinMean->GetBinContent(i);
      double binMean2 = (double)localhist->_histogramAIDABinMean->GetBinContent(i);
      double weight1 = (double)_histogram->GetBinContent(i);
      double weight2 = (double)localhist->_histogram->GetBinContent(i);

      double newBinMean = 
	(binMean1 * weight1 + binMean2 * weight2)/(weight1+weight2);
      _histogramAIDABinMean->SetBinContent( (Int_t)i, (Double_t)newBinMean );
    }

  _histogram->Add(localhist->_histogram);
  _histogramAIDA->Add(localhist->_histogramAIDA);

  return true;
}

bool IHistogram1DROOT::subtract(const IHistogram1D & hist) 
{
  if ( axis().bins() != hist.axis().bins() ) return false;
  IHistogram1DROOT const * localhist = dynamic_cast<const IHistogram1DROOT*>(&hist);

  for ( int i=0 ; i<=_histogramAIDABinMean->GetNbinsX()+1 ; i++ )
    {
      double binMean1 = (double)_histogramAIDABinMean->GetBinContent(i);
      double binMean2 = (double)localhist->_histogramAIDABinMean->GetBinContent(i);
      double weight1 = (double)_histogram->GetBinContent(i);
      double weight2 = (double)localhist->_histogram->GetBinContent(i);

      double newBinMean;
      if ( (weight1-weight2) )
	{
	  newBinMean = 
	    (binMean1 * weight1 - binMean2 * weight2)/(weight1-weight2);
	}
      else
	{
	  newBinMean = 0; 
	}
      _histogramAIDABinMean->SetBinContent( (Int_t)i, (Double_t)newBinMean );
    }

  _histogram->Add(localhist->_histogram,-1.);
  _histogramAIDA->Add(localhist->_histogramAIDA,-1.);

  return true;
}

bool IHistogram1DROOT::multiply(const IHistogram1D & hist) 
{
  if ( axis().bins() != hist.axis().bins() ) return false;
  IHistogram1DROOT const * localhist = dynamic_cast<const IHistogram1DROOT*>(&hist);

  for ( int i=0 ; i<=_histogramAIDABinMean->GetNbinsX()+1 ; i++ )
    {
      _histogramAIDABinMean->SetBinContent( (Int_t)i, (Double_t)0 );
    }

  _histogram->Multiply(localhist->_histogram);
  _histogramAIDA->Multiply(localhist->_histogramAIDA);

  return true;
}

bool IHistogram1DROOT::divide(const IHistogram1D & hist) 
{
  if ( axis().bins() != hist.axis().bins() ) return false;
  IHistogram1DROOT const * localhist = dynamic_cast<const IHistogram1DROOT*>(&hist);

  for ( int i=0 ; i<=_histogramAIDABinMean->GetNbinsX()+1 ; i++ )
    {
      _histogramAIDABinMean->SetBinContent( (Int_t)i, (Double_t)0 );
    }

  _histogram->Divide(localhist->_histogram);
  _histogramAIDA->Divide(localhist->_histogramAIDA);

  return true;
}
