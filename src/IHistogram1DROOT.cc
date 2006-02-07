#include <RAIDA/IHistogram1DROOT.h>
// #include <RAIDA/utilROOT.h>
#include <RAIDA/Naming.h>
#include <iostream>
#include <TH1D.h>
#include <TDirectory.h>
#include <string>

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
  return (double)_histogramAIDABinMean->GetBinContent(index);
}

int IHistogram1DROOT::binEntries(int index) const 
{
  double bincount;
  bincount = (double)_histogramAIDA->GetBinContent(index);
  return (int)bincount;
}

double IHistogram1DROOT::binHeight(int index) const 
{
  return (double)_histogram->GetBinContent( (Int_t)index );
}

double IHistogram1DROOT::binError(int index) const 
{
  return (double)_histogram->GetBinError(index);
}

double IHistogram1DROOT::mean() const 
{
  return (double)_histogram->GetMean();
}

double IHistogram1DROOT::rms() const 
{
  return (double)_histogram->GetRMS();
}

int IHistogram1DROOT::coordToIndex(double coord) const 
{
  return (int)_histogram->FindBin( (Axis_t)coord );
}

bool IHistogram1DROOT::add(const IHistogram1D & hist) 
{
  // FIXME! bin mean muss noch beruecksichtigt werden!!!
  IHistogram1DROOT const * localhist = dynamic_cast<const IHistogram1DROOT*>(&hist);
  _histogramAIDA->Add(localhist->_histogramAIDA);
  _histogram->Add(localhist->_histogram);
  return true;
}

