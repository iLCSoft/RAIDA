#include <RAIDA/IProfile1DROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/IAxisROOT.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile.h>
#include <TDirectory.h>
#include <string>

using namespace AIDA ;
using namespace std;

IProfile1DROOT::IProfile1DROOT(const std::string & name,
			       const std::string & title,
			       int nBins,
			       double lowerEdge,
			       double upperEdge,
			       const std::string & options)
{
  _profile = new TProfile(name.c_str(),
			  title.c_str(),
			  (Int_t)nBins,
                          (Axis_t)lowerEdge,(Axis_t)upperEdge);

  Profile1DHistograms(name,title,nBins,lowerEdge,upperEdge);
}

IProfile1DROOT::IProfile1DROOT(const std::string & name,
			       const std::string & title,
			       int nBins,
			       double lowerEdge,
			       double upperEdge,
			       double lowerValue,
			       double upperValue,
			       const std::string & options) 
{
  _profile = new TProfile(name.c_str(),
			  title.c_str(),
			  (Int_t)nBins,
                          (Axis_t)lowerEdge,(Axis_t)upperEdge,
                          (Axis_t)lowerValue,(Axis_t)upperValue);

  Profile1DHistograms(name,title,nBins,lowerEdge,upperEdge);
}

IProfile1DROOT::IProfile1DROOT(const std::string & name,
			       const IProfile1DROOT & profile) 
{
  _profile = (TProfile*)profile._profile->Clone( name.c_str() );
  _histogram = (TH1D*)profile._histogram->Clone( Naming::binContents(name).c_str() );
  _histogramAIDA = (TH1D*)profile._histogramAIDA->Clone( Naming::binEntry(name).c_str() );
  _histogramAIDABinMeanX = (TH1D*)profile._histogramAIDABinMeanX->Clone( Naming::binMeanX(name).c_str() );

  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  if ( profile._xAxis->isFixedBinning() )
    dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
  else
    dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
}

IProfile1DROOT::IProfile1DROOT(const std::string & name,
			       const std::string & title,
			       const std::vector<double>  & binEdges,
			       const std::string & options)
{
  const int nBinsX = binEdges.size()-1;
  Double_t xBins[nBinsX+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdges[i];

  _profile = new TProfile(name.c_str(),
			  title.c_str(),
			  (Int_t)nBinsX,xBins);
  Profile1DHistograms(name,title,binEdges);
}

IProfile1DROOT::IProfile1DROOT(const std::string & name,
			       const std::string & title,
			       const std::vector<double>  & binEdges,
			       double lowerValue,
			       double upperValue,
			       const std::string & options)
{
  const int nBinsX = binEdges.size()-1;
  Double_t xBins[nBinsX+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdges[i];

  _profile = new TProfile(name.c_str(),
			  title.c_str(),
			  (Int_t)nBinsX,xBins,
			  (Double_t)lowerValue,(Double_t)upperValue);
  Profile1DHistograms(name,title,binEdges);
}

void IProfile1DROOT::Profile1DHistograms(const std::string & name,
					 const std::string & title,
					 int nBins,
					 double lowerEdge,
					 double upperEdge)
{
  _histogram = new TH1D(Naming::binContents(name).c_str(),
			Naming::titleBinContents(title).c_str(),
			(Int_t)nBins,
			(Axis_t)lowerEdge,(Axis_t)upperEdge);
  _histogramAIDA = new TH1D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
                            (Int_t)nBins,
                            (Axis_t)lowerEdge,(Axis_t)upperEdge);
  _histogramAIDABinMeanX = new TH1D(Naming::binMeanX(name).c_str(),
                                    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBins,
				    (Axis_t)lowerEdge,(Axis_t)upperEdge);

  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
}

void IProfile1DROOT::Profile1DHistograms(const std::string & name,
					 const std::string & title,
					 const std::vector<double>  & binEdges)
{
  const int nBinsX = binEdges.size()-1;
  Double_t xBins[nBinsX+1];
  for (int i=0;i<=nBinsX;i++)
    xBins[i] = binEdges[i];

  _histogram = new TH1D(Naming::binContents(name).c_str(),
			Naming::titleBinContents(title).c_str(),
			(Int_t)nBinsX,xBins);
  _histogramAIDA = new TH1D(Naming::binEntry(name).c_str(),
                            Naming::titleBinEntry(title).c_str(),
			    (Int_t)nBinsX,xBins);
  _histogramAIDABinMeanX = new TH1D(Naming::binMeanX(name).c_str(),
                                    Naming::titleBinMeanX(title).c_str(),
				    (Int_t)nBinsX,xBins);

  // create axis
  _xAxis = new IAxisROOT( _profile->GetXaxis() );
  dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning();
}

bool IProfile1DROOT::fill(double x, double y, double weight)
{
  // only fill if weight is positiv
  if (weight<0) {  return false; }

  int iBin = (int)_histogram->FindBin( (Axis_t)x );
  double iBinHeight = (double)_histogram->GetBinContent(iBin);
  double newBinMean, oldBinMean;
  oldBinMean = (double)_histogramAIDABinMeanX->GetBinContent(iBin);
  newBinMean = (oldBinMean * iBinHeight + x*weight)/(weight+iBinHeight);

  _histogramAIDABinMeanX->SetBinContent( (Int_t)iBin, (Stat_t)newBinMean );
  _profile->Fill((Axis_t)x,(Stat_t)weight);
  _histogram->Fill((Axis_t)x,(Stat_t)weight);
  _histogramAIDA->Fill((Axis_t)x,(Stat_t)1.);
  return true;
}

double IProfile1DROOT::binMean(int index) const 
{
  return (double)_histogramAIDABinMeanX->GetBinContent(index);
}

int IProfile1DROOT::binEntries(int index) const 
{
  double bincount;
  bincount = (double)_histogramAIDA->GetBinContent(index);
  return (int)bincount;
}

double IProfile1DROOT::binHeight(int index) const 
{
  return (double)_profile->GetBinEntries( (Int_t)index );
}

double IProfile1DROOT::binError(int index) const
{
  return (double)_histogram->GetBinError( (Int_t)index );
}

double IProfile1DROOT::binRms(int index) const 
{
  return (double)_profile->GetBinError( (Int_t)index );
}

double IProfile1DROOT::mean() const 
{
  return (double)_profile->GetMean( (Int_t)1 );
}

double IProfile1DROOT::rms() const 
{
  return (double)_profile->GetRMS();
}

const IAxis & IProfile1DROOT::axis() const
{
  return *_xAxis;
}

int IProfile1DROOT::coordToIndex(double coord) const 
{
  // FIXME!!! pruefen ob das auch mit profile die richtigen ergebnisse liefert
  return (int)_histogram->FindBin( (Axis_t)coord );
}

int IProfile1DROOT::allEntries() const 
{
  return (int)_histogramAIDA->GetEntries();
}

int IProfile1DROOT::extraEntries() const 
{
  double extra;
  extra = (double)_histogramAIDA->GetBinContent(0)
    + (double)_histogramAIDA->GetBinContent( _histogramAIDA->GetNbinsX() + 1);
  return (int)extra;
}

double IProfile1DROOT::sumBinHeights() const 
{
  double integral = 0.;

  for (int i = 1; i<=(int)_profile->GetNbinsX();i++)
    {
      integral += (double)_profile->GetBinEntries( (Int_t)i );
    }
  return integral;
}

double IProfile1DROOT::sumAllBinHeights() const 
{
  double integralall;
  integralall = sumBinHeights()
    + (double)_profile->GetBinEntries(0)
    + (double)_profile->GetBinEntries( _profile->GetNbinsX() + 1);
  return integralall;
}

double IProfile1DROOT::sumExtraBinHeights() const 
{
  double integralextra;

  integralextra =
    + (double)_profile->GetBinEntries(0)
    + (double)_profile->GetBinEntries( _profile->GetNbinsX() + 1);

  return integralextra;
}

double IProfile1DROOT::minBinHeight() const 
{
  double minHeight;

  minHeight = (double)_profile->GetBinEntries( (Int_t)1 );

  for (int i = 1; i<=(int)_profile->GetNbinsX();i++)
    {
      if ((double)_profile->GetBinEntries( (Int_t)i ) < minHeight)
        {
          minHeight = (double)_profile->GetBinEntries( (Int_t)i );
        }
    }

  return minHeight;
}

double IProfile1DROOT::maxBinHeight() const 
{
  double maxHeight;

  maxHeight = (double)_profile->GetBinEntries( (Int_t)1 );

  for (int i = 1; i<=(int)_profile->GetNbinsX();i++)
    {
      if ((double)_profile->GetBinEntries( (Int_t)i ) > maxHeight)
        {
          maxHeight = (double)_profile->GetBinEntries( (Int_t)i );
        }
    }

  return maxHeight;
}

std::string IProfile1DROOT::title() const 
{
  string a(_profile->GetTitle());
  return a;
}

bool IProfile1DROOT::setTitle(const std::string & title) 
{
  _profile->SetTitle( title.c_str() );
  _histogram->SetTitle( Naming::titleBinContents(title).c_str() );
  _histogramAIDA->SetTitle( Naming::titleBinEntry(title).c_str() );
  _histogramAIDABinMeanX->SetTitle( Naming::titleBinMeanX(title).c_str() );
  return true;
}

int IProfile1DROOT::dimension() const 
{
  return (int)_profile->GetDimension();
}

bool IProfile1DROOT::reset() 
{
  _profile->Reset("");
  _histogram->Reset("");
  _histogramAIDA->Reset("");
  _histogramAIDABinMeanX->Reset("");
  return true;
}

int IProfile1DROOT::entries() const 
{
  double integral = 0.;

  for (int i = 1; i<=(int)_histogramAIDA->GetNbinsX();i++)
    {
      integral += (double)_histogramAIDA->GetBinContent(i);
    }
  return (int)integral;
}
