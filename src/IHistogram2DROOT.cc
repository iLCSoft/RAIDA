#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/Naming.h>
#include <RAIDA/IAxisROOT.h>
#include <RAIDA/RAIDAUtil.h>
#include <RAIDA/AIDAHistogramsInROOT.h>
#include <iostream>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <string>
#include <iomanip>

using namespace AIDA ;
using namespace std;

IHistogram2DROOT::~IHistogram2DROOT()
{
    // The histograms (at least _histogram) are associated to a file.
    // Set the directory to 0 to remove this binding so we can delete them.
    _histogram->SetDirectory(0);
    delete _histogram;

    _histogramAIDA->SetDirectory(0);
    delete _histogramAIDA;

    _histogramAIDABinMeanX->SetDirectory(0);
    delete _histogramAIDABinMeanX;

    _histogramAIDABinMeanY->SetDirectory(0);
    delete _histogramAIDABinMeanY;

    delete _xAxis;
    delete _yAxis;
}

IHistogram2DROOT::IHistogram2DROOT()
  : _histogram(0),  _histogramAIDA(0), _histogramAIDABinMeanX(0),
    _histogramAIDABinMeanY(0), _xAxis(0),  _yAxis(0)
{
    // nothing to do, just created implementation to initialize pointers correctly
}

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
  if (!AIDAHistogramsInROOT)
    _histogramAIDA->SetDirectory(0);
  _histogramAIDABinMeanX = (TH2D*)hist._histogramAIDABinMeanX->Clone( Naming::binMeanX(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanX->SetDirectory(0);
  _histogramAIDABinMeanY = (TH2D*)hist._histogramAIDABinMeanY->Clone( Naming::binMeanY(name).c_str() );
  if (!AIDAHistogramsInROOT)
    _histogramAIDABinMeanY->SetDirectory(0);

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

IHistogram2DROOT::IHistogram2DROOT(const std::string & name,
				   const IHistogram3DROOT & hist,
				   std::string axis,
				   int lowerBin,
				   int upperBin)
{ // ######
  int index1ROOT;
  int index2ROOT;

  if (axis == "xy")
    {
      index1ROOT = RAIDAUtil::binIndexAIDA2ROOT( lowerBin,hist.zAxis().bins() );
      index2ROOT = RAIDAUtil::binIndexAIDA2ROOT( upperBin,hist.zAxis().bins() );
      // save original bin range of histogram and set new range 
      int lowerZBin = hist._histogram->GetZaxis()->GetFirst();
      int upperZBin = hist._histogram->GetZaxis()->GetLast();
      hist._histogram->GetZaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDA->GetZaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanX->GetZaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanY->GetZaxis()->SetRange(index1ROOT,index2ROOT);

      _histogram = (TH2D*)hist._histogram->Project3D("xye");
      _histogramAIDA = (TH2D*)hist._histogramAIDA->Project3D("xye");
      _histogramAIDABinMeanX = (TH2D*)hist._histogramAIDABinMeanX->Project3D("xye");
      _histogramAIDABinMeanY = (TH2D*)hist._histogramAIDABinMeanY->Project3D("xye");

      _histogramAIDABinMeanX->Reset();
      _histogramAIDABinMeanY->Reset();

      if (!AIDAHistogramsInROOT)
	_histogramAIDA->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanX->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanY->SetDirectory(0);

      for (int i=-2; i<hist.xAxis().bins(); i++)
	{
	  for (int j=-2; j<hist.yAxis().bins(); j++)
	    {
	      double binmeanx = 0, binmeany = 0, binhight = 0;
	      for (int k=-2; k<hist.zAxis().bins(); k++)
		{
		  binmeanx += hist.binMeanX(i,j,k)*hist.binHeight(i,j,k);
		  binmeany += hist.binMeanY(i,j,k)*hist.binHeight(i,j,k);
		  binhight += hist.binHeight(i,j,k);
		}
	      binmeanx = binmeanx / binhight;
	      binmeany = binmeany / binhight;

	      // different bin index for root and AIDA:
	      _histogramAIDABinMeanX->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( i, hist.xAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( j, hist.yAxis().bins() ), 
						    (Double_t)binmeanx );
	      _histogramAIDABinMeanY->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( i, hist.xAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( j, hist.yAxis().bins() ), 
						    (Double_t)binmeany );
	    }
	}

      // set range to original range 
      hist._histogram->GetZaxis()->SetRange(lowerZBin,upperZBin);
      hist._histogramAIDA->GetZaxis()->SetRange(lowerZBin,upperZBin);
      hist._histogramAIDABinMeanX->GetZaxis()->SetRange(lowerZBin,upperZBin);
      hist._histogramAIDABinMeanY->GetZaxis()->SetRange(lowerZBin,upperZBin);
      
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
  else if (axis == "xz")
    {
      index1ROOT = RAIDAUtil::binIndexAIDA2ROOT(lowerBin,hist.yAxis().bins() );
      index2ROOT = RAIDAUtil::binIndexAIDA2ROOT(upperBin,hist.yAxis().bins() );
      // save original bin range of histogram and set new range 
      int lowerYBin = hist._histogram->GetYaxis()->GetFirst();
      int upperYBin = hist._histogram->GetYaxis()->GetLast();
      hist._histogram->GetYaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDA->GetYaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanX->GetYaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanY->GetYaxis()->SetRange(index1ROOT,index2ROOT);

      _histogram = (TH2D*)hist._histogram->Project3D("xze");
      _histogramAIDA = (TH2D*)hist._histogramAIDA->Project3D("xze");
      _histogramAIDABinMeanX = (TH2D*)hist._histogramAIDABinMeanX->Project3D("xze");
      _histogramAIDABinMeanY = (TH2D*)hist._histogramAIDABinMeanZ->Project3D("xze");

      _histogramAIDABinMeanX->Reset();
      _histogramAIDABinMeanY->Reset();

      if (!AIDAHistogramsInROOT)
	_histogramAIDA->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanX->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanY->SetDirectory(0);

      for (int i=-2; i<hist.xAxis().bins(); i++)
	{
	  for (int k=-2; k<hist.zAxis().bins(); k++)
	    {
	      double binmeanx = 0, binmeanz = 0, binhight = 0;
	      for (int j=-2; j<hist.yAxis().bins(); j++)
		{
		  binmeanx += hist.binMeanX(i,j,k)*hist.binHeight(i,j,k);
		  binmeanz += hist.binMeanZ(i,j,k)*hist.binHeight(i,j,k);
		  binhight += hist.binHeight(i,j,k);
		}
	      binmeanx = binmeanx / binhight;
	      binmeanz = binmeanz / binhight;

	      // different bin index for root and AIDA:
	      _histogramAIDABinMeanX->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( i, hist.xAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( k, hist.zAxis().bins() ), 
						    (Double_t)binmeanx );
	      _histogramAIDABinMeanY->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( i, hist.xAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( k, hist.zAxis().bins() ), 
						    (Double_t)binmeanz );
	    }
	}

      // set range to original range 
      hist._histogram->GetYaxis()->SetRange(lowerYBin,upperYBin);
      hist._histogramAIDA->GetYaxis()->SetRange(lowerYBin,upperYBin);
      hist._histogramAIDABinMeanX->GetYaxis()->SetRange(lowerYBin,upperYBin);
      hist._histogramAIDABinMeanY->GetYaxis()->SetRange(lowerYBin,upperYBin);

      // create axis
      _xAxis = new IAxisROOT( _histogram->GetXaxis() );
      if ( hist._xAxis->isFixedBinning() )
        dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
      else
        dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
      _yAxis = new IAxisROOT( _histogram->GetYaxis() );
      if ( hist._zAxis->isFixedBinning() )
        dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
      else
        dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning() ;
    }
  else if (axis == "yz")
    {
      index1ROOT = RAIDAUtil::binIndexAIDA2ROOT(lowerBin,hist.xAxis().bins() );
      index2ROOT = RAIDAUtil::binIndexAIDA2ROOT(upperBin,hist.xAxis().bins() );
      // save original bin range of histogram and set new range 
      int lowerXBin = hist._histogram->GetXaxis()->GetFirst();
      int upperXBin = hist._histogram->GetXaxis()->GetLast();
      hist._histogram->GetXaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDA->GetXaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanX->GetXaxis()->SetRange(index1ROOT,index2ROOT);
      hist._histogramAIDABinMeanY->GetXaxis()->SetRange(index1ROOT,index2ROOT);

      _histogram = (TH2D*)hist._histogram->Project3D("yze");
      _histogramAIDA = (TH2D*)hist._histogramAIDA->Project3D("yze");
      _histogramAIDABinMeanX = (TH2D*)hist._histogramAIDABinMeanY->Project3D("yze");
      _histogramAIDABinMeanY = (TH2D*)hist._histogramAIDABinMeanZ->Project3D("yze");

      _histogramAIDABinMeanX->Reset();
      _histogramAIDABinMeanY->Reset();

      if (!AIDAHistogramsInROOT)
	_histogramAIDA->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanX->SetDirectory(0);
      if (!AIDAHistogramsInROOT)
	_histogramAIDABinMeanY->SetDirectory(0);

      for (int j=-2; j<hist.yAxis().bins(); j++)
	{
	  for (int k=-2; k<hist.zAxis().bins(); k++)
	    {
	      double binmeany = 0, binmeanz = 0, binhight = 0;
	      for (int i=-2; i<hist.xAxis().bins(); i++)
		{
		  binmeany += hist.binMeanY(i,j,k)*hist.binHeight(i,j,k);
		  binmeanz += hist.binMeanZ(i,j,k)*hist.binHeight(i,j,k);
		  binhight += hist.binHeight(i,j,k);
		}
	      binmeany = binmeany / binhight;
	      binmeanz = binmeanz / binhight;

	      // different bin index for root and AIDA:
	      _histogramAIDABinMeanX->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( j, hist.yAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( k, hist.zAxis().bins() ), 
						    (Double_t)binmeany );
	      _histogramAIDABinMeanY->SetBinContent((Int_t)RAIDAUtil::binIndexAIDA2ROOT( j, hist.yAxis().bins() ), 
						    (Int_t)RAIDAUtil::binIndexAIDA2ROOT( k, hist.zAxis().bins() ), 
						    (Double_t)binmeanz );
	    }
	}

      // set range to original range 
      hist._histogram->GetXaxis()->SetRange(lowerXBin,upperXBin);
      hist._histogramAIDA->GetXaxis()->SetRange(lowerXBin,upperXBin);
      hist._histogramAIDABinMeanX->GetXaxis()->SetRange(lowerXBin,upperXBin);
      hist._histogramAIDABinMeanY->GetXaxis()->SetRange(lowerXBin,upperXBin);

      // create axis
      _xAxis = new IAxisROOT( _histogram->GetXaxis() );
      if ( hist._yAxis->isFixedBinning() )
        dynamic_cast<IAxisROOT*>(_xAxis)->setFixedBinning();
      else
        dynamic_cast<IAxisROOT*>(_xAxis)->setVariableBinning() ;
      _yAxis = new IAxisROOT( _histogram->GetYaxis() );
      if ( hist._zAxis->isFixedBinning() )
        dynamic_cast<IAxisROOT*>(_yAxis)->setFixedBinning();
      else
        dynamic_cast<IAxisROOT*>(_yAxis)->setVariableBinning() ;
    }

  // change the name of the Histogram
  setName(name);
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
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogramAIDABinMeanX->GetBinContent( (Int_t)indexXROOT,
                                                        (Int_t)indexYROOT );
}

double IHistogram2DROOT::binMeanY(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());
  return (double)_histogramAIDABinMeanY->GetBinContent( (Int_t)indexXROOT,
                                                        (Int_t)indexYROOT );
}

int IHistogram2DROOT::binEntries(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());
  return (int)_histogramAIDA->GetBinContent( (Int_t)indexXROOT,
					     (Int_t)indexYROOT );
}

int IHistogram2DROOT::binEntriesX(int index) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(index,xAxis().bins());

  double sumX = 0;
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogramAIDA->GetBinContent( (Int_t)indexXROOT,(Int_t)i );
    }
  return (int)sumX;
}

int IHistogram2DROOT::binEntriesY(int index) const 
{
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(index,yAxis().bins());

  double sumY = 0;
  for ( int i=0 ; i<=((int)_histogramAIDA->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogramAIDA->GetBinContent( (Int_t)i,(Int_t)indexYROOT );
    }
  return (int)sumY;
}

double IHistogram2DROOT::binHeight(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogram->GetBinContent( (Int_t)indexXROOT,
					    (Int_t)indexYROOT );
}

double IHistogram2DROOT::binHeightX(int index) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(index,xAxis().bins());

  double sumX = 0;
  for ( int i=0 ; i<=((int)_histogram->GetNbinsY()+1) ; i++)
    {
      sumX += (double)_histogram->GetBinContent( (Int_t)indexXROOT,(Int_t)i );
    }
  return sumX;
}

double IHistogram2DROOT::binHeightY(int index) const 
{
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(index,yAxis().bins());

  double sumY = 0;
  for ( int i=0 ; i<=((int)_histogram->GetNbinsX()+1) ; i++)
    {
      sumY += (double)_histogram->GetBinContent( (Int_t)i,(Int_t)indexYROOT );
    }
  return sumY;
}

double IHistogram2DROOT::binError(int indexX, int indexY) const 
{
  int indexXROOT = RAIDAUtil::binIndexAIDA2ROOT(indexX,xAxis().bins());
  int indexYROOT = RAIDAUtil::binIndexAIDA2ROOT(indexY,yAxis().bins());

  return (double)_histogram->GetBinError( (Int_t)indexXROOT,
					  (Int_t)indexYROOT );
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
  TH1D *xProj = _histogram->ProjectionX("_temphisto");
  int indexROOT = (int)xProj->FindBin( (Axis_t)coord );

  delete xProj;


  return RAIDAUtil::binIndexROOT2AIDA(indexROOT,xAxis().bins());
}

int IHistogram2DROOT::coordToIndexY(double coord) const 
{
  TH1D *yProj = _histogram->ProjectionY("_temphisto");
  int indexROOT = (int)yProj->FindBin( (Axis_t)coord );

  delete yProj;

  return RAIDAUtil::binIndexROOT2AIDA(indexROOT,yAxis().bins());
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

bool IHistogram2DROOT::subtract(const IHistogram2D & hist) 
{
  if ( xAxis().bins() != hist.xAxis().bins() ) return false;
  if ( yAxis().bins() != hist.yAxis().bins() ) return false;
  IHistogram2DROOT const * localhist = dynamic_cast<const IHistogram2DROOT*>(&hist);

  for ( int i=0 ; i<=_histogramAIDABinMeanX->GetNbinsX()+1 ; i++ )
    {
      for ( int j=0 ; j<=_histogramAIDABinMeanX->GetNbinsY()+1 ; j++ )
	{
	  double binMeanX1 = (double)_histogramAIDABinMeanX->GetBinContent(i,j);
	  double binMeanX2 = (double)localhist->_histogramAIDABinMeanX->GetBinContent(i,j);
	  double binMeanY1 = (double)_histogramAIDABinMeanY->GetBinContent(i,j);
	  double binMeanY2 = (double)localhist->_histogramAIDABinMeanY->GetBinContent(i,j);

	  double weight1 = (double)_histogram->GetBinContent(i,j);
	  double weight2 = (double)localhist->_histogram->GetBinContent(i,j);
	  double newBinMeanX, newBinMeanY;
	  if ( (weight1-weight2) )
	    {
	      newBinMeanX = 
		(binMeanX1 * weight1 - binMeanX2 * weight2)/(weight1-weight2);
	      newBinMeanY = 
		(binMeanY1 * weight1 - binMeanY2 * weight2)/(weight1-weight2);
	    }
	  else
	    {
	      newBinMeanX = 0; 
	      newBinMeanY = 0; 
	    }
	  _histogramAIDABinMeanX->SetBinContent( (Int_t)i, (Int_t)j, (Double_t)newBinMeanX );
	  _histogramAIDABinMeanY->SetBinContent( (Int_t)i, (Int_t)j, (Double_t)newBinMeanY );
	}
    }

  _histogram->Add(localhist->_histogram,-1.);
  _histogramAIDA->Add(localhist->_histogramAIDA,-1.);

  return true;
}

bool IHistogram2DROOT::multiply(const IHistogram2D & hist) 
{
  if (xAxis().bins() != hist.xAxis().bins() ) return false;
  if (yAxis().bins() != hist.yAxis().bins() ) return false;

  IHistogram2DROOT const * localhist = dynamic_cast<const IHistogram2DROOT*>(&hist);

  for (int i=0 ; i<=_histogramAIDABinMeanX->GetNbinsX()+1 ; i++)
    {
      for (int j=0 ; j<=_histogramAIDABinMeanX->GetNbinsY()+1 ; j++)
	{
	  _histogramAIDABinMeanX->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)0 );
	  _histogramAIDABinMeanY->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)0 );
	}
    }

  _histogram->Multiply(localhist->_histogram);
  _histogramAIDA->Multiply(localhist->_histogramAIDA);

  return true;
}

bool IHistogram2DROOT::divide(const IHistogram2D & hist) 
{
  if (xAxis().bins() != hist.xAxis().bins() ) return false;
  if (yAxis().bins() != hist.yAxis().bins() ) return false;

  IHistogram2DROOT const * localhist = dynamic_cast<const IHistogram2DROOT*>(&hist);

  for (int i=0 ; i<=_histogramAIDABinMeanX->GetNbinsX()+1 ; i++)
    {
      for (int j=0 ; j<=_histogramAIDABinMeanX->GetNbinsY()+1 ; j++)
	{
	  _histogramAIDABinMeanX->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)0 );
	  _histogramAIDABinMeanY->SetBinContent( (Int_t)i,(Int_t)j, (Double_t)0 );
	}
    }

  _histogram->Divide(localhist->_histogram);
  _histogramAIDA->Divide(localhist->_histogramAIDA);

  return true;
}

void IHistogram2DROOT::printContents() const 
{
  int colWidth = 10;

  cout << "*******************************************************************************" << endl;
  cout << endl 
       << "Contents of 2D histogram:" << endl  
       << "------------------------" << endl << endl; 
  cout << "title:              " << title() << endl; 

  cout << "x-range:            " 
       << "min: " << xAxis().lowerEdge()
       << ", max: " << xAxis().upperEdge() 
       << ", nBins: " << xAxis().bins() ;
  if (xAxis().isFixedBinning()) cout << " (fixed " ;
  else cout << " (variable " ;
  cout << "binning)" << endl; 
  cout << "y-range:            " 
       << "min: " << yAxis().lowerEdge()
       << ", max: " << yAxis().upperEdge() 
       << ", nBins: " << yAxis().bins() ;
  if (yAxis().isFixedBinning()) cout << " (fixed " ;
  else cout << " (variable " ;
  cout << "binning)" << endl; 

  cout << "entries:            " 
       << "in-range:  " << entries() << endl; 
  cout << "                    " 
       << "x-UNDERFLOW: " << binEntriesX(-2) 
       << " x-OVERFLOW: " << binEntriesX(-1) << endl;
  cout << "                    " 
       << "y-UNDERFLOW: " << binEntriesY(-2) 
       << " y-OVERFLOW: " << binEntriesY(-1)
       << " (total: " << extraEntries() << ")" << endl; 
  cout << "                    " 
       << "total:     " << allEntries() << endl; 
  cout << "sum of bin heights: " 
       << "in-range:  " << sumBinHeights() << endl; 
  cout << "                    " 
       << "x-UNDERFLOW: " << binHeightX(-2)
       << " x-OVERFLOW: " << binHeightX(-1) << endl;
  cout << "                    " 
       << "y-UNDERFLOW: " << binHeightY(-2)
       << " y-OVERFLOW: " << binHeightY(-1)
       << " (total: " << sumExtraBinHeights() << ")" << endl; 
  cout << "                    " 
       << "sum:       " << sumAllBinHeights()<< endl; 
  cout << "bin height:         " << "minimum:   " << minBinHeight()
       << " maximum: " << maxBinHeight() << endl;
  cout << "statistics:         " 
       << "x-mean: " << meanX() 
       << " x-RMS: " << rmsX() 
       << " y-mean: " << meanY() 
       << " y-RMS: " << rmsY() << endl;
  cout << endl; 

  cout << "bin contents:" << endl 
       << "------------" << endl << endl;
  cout << "   x-binID | "
       << "   y-binID | "
       << "   x-low edge | "
       << "   y-low edge | "
       << "   entries | "
       << "x-bin mean | " 
       << "y-bin mean | " 
       << "     hight | " 
       << "     error" << endl; 
  cout << "------------------------------------------------------------------------------" << endl;

  for (int i=IAxis::UNDERFLOW_BIN; i<xAxis().bins(); i++)
    {
      for (int j=IAxis::UNDERFLOW_BIN; j<yAxis().bins(); j++)
	{
	  cout << setw(colWidth) << i << " | " ;
	  cout << setw(colWidth) << j << " | " ;
	  cout << setw(colWidth+3) << xAxis().binLowerEdge(i) << " | " ;
	  cout << setw(colWidth+3) << yAxis().binLowerEdge(j) << " | " ;
	  cout << setw(colWidth) << binEntries(i,j) << " | " 
	       << setw(colWidth) << binMeanX(i,j) << " | " 
	       << setw(colWidth) << binMeanY(i,j) << " | " 
	       << setw(colWidth) << binHeight(i,j) << " | " 
	       << setw(colWidth) << binError(i,j) << endl;
	}
    }
  cout << "------------------------------------------------------------------------------" << endl;

  cout << "*******************************************************************************" << endl;
}
