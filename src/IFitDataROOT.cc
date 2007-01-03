// -*- C++ -*-
#include <RAIDA/IFitDataROOT.h>
#include <RAIDA/ICloud1DROOT.h>
#include <RAIDA/ICloud2DROOT.h>
#include <RAIDA/ICloud3DROOT.h>
#include <RAIDA/IDataPointSetROOT.h>
#include <RAIDA/IEvaluatorROOT.h>
#include <RAIDA/IHistogram1DROOT.h>
#include <RAIDA/IHistogram2DROOT.h>
#include <RAIDA/IHistogram3DROOT.h>
#include <RAIDA/IProfile1DROOT.h>
#include <RAIDA/IProfile2DROOT.h>
#include <RAIDA/IRangeSetROOT.h>
#include <RAIDA/ITupleROOT.h>
#include <RAIDA/NotYetImplementedException.h>

#include <string>
#include <vector>

using namespace AIDA ;

bool IFitDataROOT::create1DConnection(const IHistogram1D & h) 
{
  throw(NotYetImplementedException("create1DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create1DConnection(const ICloud1D & c) 
{
  throw(NotYetImplementedException("create1DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create1DConnection(const IProfile1D & p) 
{
  throw(NotYetImplementedException("create1DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create1DConnection(const IDataPointSet & dp, 
				      int xIndex, int valIndex) 
{
  throw(NotYetImplementedException("create1DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const IHistogram2D & h) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const IHistogram2D & h, 
				      int xIndex, int yIndex) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const ICloud2D & c) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const ICloud2D & c, 
				      int xIndex, int yIndex) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const IProfile2D & p) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const IProfile2D & p, 
				      int xIndex, int yIndex) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create2DConnection(const IDataPointSet & dp, 
				      int xIndex, int yIndex, int valIndex) 
{
  throw(NotYetImplementedException("create2DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create3DConnection(const IHistogram3D & h) 
{
  throw(NotYetImplementedException("create3DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create3DConnection(const IHistogram3D & h, 
				      int xIndex, int yIndex, int zIndex) 
{
  throw(NotYetImplementedException("create3DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create3DConnection(const ICloud3D & c) 
{
  throw(NotYetImplementedException("create3DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create3DConnection(const ICloud3D & c, 
				      int xIndex, int yIndex, int zIndex) 
{
  throw(NotYetImplementedException("create3DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::create3DConnection(const IDataPointSet & dp, 
				      int xIndex, int yIndex, int zIndex, 
				      int valIndex) 
{
  throw(NotYetImplementedException("create3DConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::createConnection(const ITuple & t, 
				    std::vector<std::string>  colNames) 
{
  throw(NotYetImplementedException("createConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::createConnection(const ITuple & t, 
				    std::vector<IEvaluator *>  & evals) 
{
  throw(NotYetImplementedException("createConnection()","IFitData"));
  return true;
}

bool IFitDataROOT::createConnection(const IDataPointSet & dp, 
				    std::vector<int>  indeces, int valIndex) 
{
  throw(NotYetImplementedException("createConnection()","IFitData"));
  return true;
}

void IFitDataROOT::reset() 
{
  throw(NotYetImplementedException("reset()","IFitData"));
}

int IFitDataROOT::dimension() const 
{
  throw(NotYetImplementedException("dimension()","IFitData"));
  return 0;
}

std::string IFitDataROOT::dataDescription() const 
{
  throw(NotYetImplementedException("dataDescription()","IFitData"));
  return std::string("");
}

IRangeSet & IFitDataROOT::range(int index) const 
{
  throw(NotYetImplementedException("range()","IFitData"));
  IRangeSet *x = new IRangeSetROOT;
  return *x;
}
