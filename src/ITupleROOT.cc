#include <RAIDA/ITupleROOT.h>
#include <RAIDA/utilROOT.h>
#include <RAIDA/NotYetImplementedException.h>
#include <iostream>
#include <TDirectory.h>
#include <TTree.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace AIDA ;
using namespace std;

ITupleROOT::ITupleROOT() 
{
}

ITupleROOT::ITupleROOT(const std::string & name,
		       const std::string & title,
		       const std::vector<std::string>  & columnNames,
		       const std::vector<std::string>  & columnType,
		       const std::string & options)
  : _readCursor(0)
{
  // create a ROOT TTree to hold the n-tuple data.
  //string treeName = extractName(path);
  _theTree = new TTree(name.c_str(),title.c_str());

  for (unsigned i = 0; i<columnType.size() ; i++)
    {
      // Make local copy for this class and remove spaces to enable type check
      string colName = columnNames[i];
      string colType = columnType[i];
      while (colType.find(" ") <= (colType.length()-1) )
	{
	  colType.erase(colType.find(" "),1);
	}

      // one string with original string and one with all chars upper case for 
      // comparison with different spelling of data types 
      string original = colType;
      string upper    = colType;
      transform (upper.begin(),upper.end(), upper.begin(), (int(*)(int))toupper);

      // find the data type of column  
      if (upper == "FLOAT" ||
	  original == "F" ||
	  upper == "FLOAT_T" )
	{
	  colType = "F";
	}
      else if (upper == "DOUBLE" ||
	       original == "" ||
	       original == "D" ||
	       upper == "DOUBLE_T" )
	{
	  colType = "D";
	}
      else if (upper == "INT" ||
	       original == "I" ||
	       upper == "INT_T" )
	{
	  colType = "I";
	}
      else if (upper == "SHORT" ||
	       upper == "SHORTINT" ||
	       original == "S" ||
	       upper == "SHORT_T" )
	{
	  colType = "S";
	}
      else if (upper == "LONG" ||
	       upper == "LONGINT" ||
	       upper == "LONG_T" ||
	       original == "L" )
	{
	  colType = "L"; // long <=> Int_t
	}
      else if (upper == "CHAR" ||
	       upper == "CHAR_T" ||
	       original == "B" )
	{
	  colType = "B"; 
	}
      else if (upper == "STRING" ||
	       upper == "STRING_T" ||
	       original == "C" )
	{
	  colType = "C"; 
	}
      else if (upper == "BOOL" ||
	       upper == "BOOL_T" ||
	       original == "O" )
	{
	  colType = "O"; 
	}
      else
	{
	  cout << "Kein gueltiger Datentyp exception" << endl;
	}

      // construct objects to be filled into the tree (columns of ntuple)
      LeafPoint point(colType,colName);
      LeafPoint readPoint(colType,colName);
      _pointVec.push_back(point);
      _readPointVec.push_back(readPoint);
    }

  for (unsigned i = 0; i<_pointVec.size() ; i++)
    {
      //      cout << "### Noch am LEBEN!!!" << endl;
      _theTree->Branch(_pointVec[i].getName().c_str(),
      		       _pointVec[i].getValue(),
      		       _pointVec[i].getROOTNameType().c_str());
      //            cout << "spalten: " << 
      //	      _pointVec[i].getROOTNameType() << " " << 
      //	      _pointVec[i].getName() << endl;
    }
}

std::string ITupleROOT::title() const 
{
  string a(_theTree->GetTitle());
  return a;
}

bool ITupleROOT::setTitle(const std::string & title) 
{
  _theTree->SetTitle(title.c_str());
  return true; 
}

bool ITupleROOT::fill(int column, double value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  // This function allows to fill also Float variables if the
  // datatype of the column is float. This is made because a call of
  // fill with a decimal number will call this function since all 
  // decimal numbers are treated as double. 
  if (_pointVec[column].getType() == 'F' && 
      fabs(value) > FLT_MIN && fabs(value) < FLT_MAX)
    { // ###
      float fvalue;
      fvalue = (float)value;
      return _pointVec[column].set(fvalue); 
    }

  if (_pointVec[column].getType() != 'D') return false;

  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, float value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'F') return false;
  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, int value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'I') return false;

  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, short value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'S') return false;
  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, long value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'L') return false;

  //  cout << "=== short wird gesetzt" << endl;
  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, char value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'B') return false;

  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(int column, bool value) 
{
  // in range? 
  if (column < 0 || column >= (int)_pointVec.size()) return false;

  // right type?
  if (_pointVec[column].getType() != 'O') return false;

  return _pointVec[column].set(value); 
}

bool ITupleROOT::fill(const std::vector<double>  & values) 
{
  // check if ntuple and array have the same size 
  if ( values.size() != _pointVec.size() ) return false; 

  // check types of coloumns
  for ( unsigned i = 0 ; i<_pointVec.size() ; i++ )
    {
      if (_pointVec[i].getType() != 'D') return false; 
    }

  // fill the values into the coloumns
  for ( unsigned i = 0 ; i<_pointVec.size() ; i++ )
    {
      if (!_pointVec[i].set(values[i])) return false;
    }
  return true;
}

bool ITupleROOT::fill(const std::vector<float>  & values) 
{
  // check if ntuple and array have the same size 
  if ( values.size() != _pointVec.size() ) return false; 

  // check types of coloumns
  for ( unsigned i = 0 ; i<_pointVec.size() ; i++ )
    {
      if (_pointVec[i].getType() != 'F') return false; 
    }

  // fill the values into the coloumns
  for ( unsigned i = 0 ; i<_pointVec.size() ; i++ )
    {
      if (!_pointVec[i].set(values[i])) return false;
    }
  return true;
}

bool ITupleROOT::addRow() 
{
  bool fillOK = false;
  if ( _theTree->Fill() == -1) 
    { // write error in ROOT file
      fillOK = false;
    }
  else
    {
      fillOK = true;
    }

  // clear all coloumns of new row (not added)
  for ( unsigned i = 0; i<_pointVec.size() ; i++ )
    _pointVec[i].clear();

  _readCursor = (int)_theTree->GetEntriesFast();
  if (fillOK) 
    {
      return true;
    }
  else
    {
      return false;
    }

  // will never be executed, just to get no compiler warning
  return true;
}

void ITupleROOT::resetRow() 
{
  for ( unsigned i = 0; i<_pointVec.size() ; i++ )
    _pointVec[i].clear();
}

void ITupleROOT::reset() 
{
  throw(NotYetImplementedException("ITuple","reset()"));
}

int ITupleROOT::rows() const 
{
  return (int)_theTree->GetEntriesFast();
}

void ITupleROOT::start() 
{
  _readCursor = 0;
}

bool ITupleROOT::skip(int rows) 
{
  int pos = _readCursor + rows;

  if (pos < 0 || pos > (int)_theTree->GetEntriesFast()) return false;
  _readCursor = pos;
  return true;
}

bool ITupleROOT::next() 
{
  int pos = _readCursor + 1;

  if (pos < 0 || pos > (int)_theTree->GetEntriesFast()) return false;
  _readCursor = pos;
  return true;
}

bool ITupleROOT::setRow(int rowIndex) 
{
  return mySetRow(rowIndex);
}

bool ITupleROOT::mySetRow(int rowIndex) const 
{
  if (rowIndex < 0 || rowIndex > (int)_theTree->GetEntriesFast()) return false;
  _readCursor = rowIndex;
  return true;
}

int ITupleROOT::findColumn(const std::string & name) const 
{
  for (unsigned i = 0; i<_pointVec.size(); i++)
    {
      if (_pointVec[i].getName() == name) return i; 
    }
    return -1;
}

double ITupleROOT::getDouble(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (_pointVec[column].getType() != 'D' &&
      _pointVec[column].getType() != 'F' &&
      _pointVec[column].getType() != 'I' &&
      _pointVec[column].getType() != 'S' &&
      _pointVec[column].getType() != 'L' ) return 0.;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'D') 
	{
	  return _readPointVec[column].getDouble();
	}
      else if (_pointVec[column].getType() == 'F')
	{
	  return (double)_readPointVec[column].getFloat();
	}
      else if (_pointVec[column].getType() == 'I')
	{
	  return (double)_readPointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (double)_readPointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (double)_readPointVec[column].getShort();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'D') 
	{
	  return _pointVec[column].getDouble();
	}
      else if (_pointVec[column].getType() == 'F')
	{
	  return (double)_pointVec[column].getFloat();
	}
      else if (_pointVec[column].getType() == 'I')
	{
	  return (double)_pointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (double)_pointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (double)_pointVec[column].getShort();
	}
    }
  return 0.;
}

float ITupleROOT::getFloat(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (_pointVec[column].getType() != 'F' &&
      _pointVec[column].getType() != 'I' &&
      _pointVec[column].getType() != 'S' &&
      _pointVec[column].getType() != 'L' ) return 0.;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'F')
	{
	  return (float)_readPointVec[column].getFloat();
	}
      else if (_pointVec[column].getType() == 'I')
	{
	  return (float)_readPointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (float)_readPointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (float)_readPointVec[column].getShort();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'F')
	{
	  //  cout << "bis hier!" << endl; 
	  return (float)_pointVec[column].getFloat();
	}
      else if (_pointVec[column].getType() == 'I')
	{
	  return (float)_pointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (float)_pointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (float)_pointVec[column].getShort();
	}
    }
  return 0.;
}

int ITupleROOT::getInt(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0;
  if (_pointVec[column].getType() != 'I' &&
      _pointVec[column].getType() != 'S' &&
      _pointVec[column].getType() != 'L' ) return 0;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'I')
	{
	  return (int)_readPointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (int)_readPointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (int)_readPointVec[column].getShort();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'I')
	{
	  return (int)_pointVec[column].getInt();
	}
      else if (_pointVec[column].getType() == 'L')
	{
	  return (int)_pointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (int)_pointVec[column].getShort();
	}
    }
  return 0;
}

short ITupleROOT::getShort(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return (short)0;
  if (_pointVec[column].getType() != 'S' ) return (short)0;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'S')
	{
	  return (short)_readPointVec[column].getShort();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'S')
	{
	  return (short)_pointVec[column].getShort();
	}
    }
  return (short)0;
}

long ITupleROOT::getLong(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return (long)0;
  if (_pointVec[column].getType() != 'S' &&
      _pointVec[column].getType() != 'L' ) return (long)0;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'L')
	{
	  return (long)_readPointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (long)_readPointVec[column].getShort();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'L')
	{
	  return (long)_pointVec[column].getLong();
	}
      else if (_pointVec[column].getType() == 'S')
	{
	  return (long)_pointVec[column].getShort();
	}
    }
  return (long)0;
}

char ITupleROOT::getChar(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return (char)0;
  if (_pointVec[column].getType() != 'B' ) return (char)0;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'B')
	{
	  return (char)_readPointVec[column].getChar();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'B')
	{
	  return (char)_pointVec[column].getChar();
	}
    }
  return (char)0;
}

bool ITupleROOT::getBoolean(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return false;
  if (_pointVec[column].getType() != 'O' ) return false;

  if (_readCursor < (int)_theTree->GetEntriesFast()) 
    {
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _readPointVec[i].getValue());
	}
      _theTree->GetEntry( (Int_t)_readCursor );
      for (unsigned i = 0; i<_pointVec.size() ; i++)
	{
	  _theTree->SetBranchAddress(_pointVec[i].getName().c_str(),
				     _pointVec[i].getValue());
	}
      if (_pointVec[column].getType() == 'O')
	{
	  return (bool)_readPointVec[column].getBool();
	}
    }
  else 
    {
      if (_pointVec[column].getType() == 'O')
	{
	  return (bool)_pointVec[column].getBool();
	}
    }
  return false;
}

int ITupleROOT::columns() const 
{
  return _pointVec.size();
}

std::string ITupleROOT::columnName(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return "";
  return _pointVec[column].getName() ;
}

std::vector<std::string>  ITupleROOT::columnNames() const 
{
  vector<string> names;
  names.resize(_pointVec.size()); 
  for (unsigned i = 0; i<_pointVec.size() ; i++)
    {
      names[i] = _pointVec[i].getName(); 
    }
  return names;
}

std::string ITupleROOT::columnType(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return "";
  return _pointVec[column].getTypeLong();
}

std::vector<std::string>  ITupleROOT::columnTypes() const 
{
  vector<string> types;
  types.resize(_pointVec.size()); 
  for (unsigned i = 0; i<_pointVec.size() ; i++)
    {
      types[i] = _pointVec[i].getTypeLong(); 
    }
  return types;
}

double ITupleROOT::columnMin(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (rows() < 1) return 0.;
  return _theTree->GetMinimum(_pointVec[column].getName().c_str());
}

double ITupleROOT::columnMax(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (rows() < 1) return 0.;
  return _theTree->GetMaximum(_pointVec[column].getName().c_str());
}

double ITupleROOT::columnMean(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (rows() < 1) return 0.;

  double myMean = 0;
  for (int i = 0; i<rows(); i++)
    {
      mySetRow(i);
      myMean += getDouble(column);
    }
  
  return myMean / ((double) rows());
}

double ITupleROOT::columnRms(int column) const 
{
  if (column < 0 || column >= (int)_pointVec.size() ) return 0.;
  if (rows() < 1) return 0.;

  double myRMS = 0;
  double myMean = columnMean(column);
  for (int i = 0; i<rows(); i++)
    {
      mySetRow(i);
      double x = getDouble(column);
      myRMS += (myMean - x)*(myMean - x);
    }
  myRMS = sqrt( myRMS / sqrt( ((double) rows())
			      * ((double) rows()) ) );
  return myRMS;
}

bool ITupleROOT::project(IHistogram1D & histogram, 
			 IEvaluator & evaluatorX) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram1D &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram1D & histogram, 
			 IEvaluator & evaluatorX, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram1D &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram1D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram1D &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram1D & histogram, 
			 IEvaluator & evaluatorX, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram1D &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram2D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram2D &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram2D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram2D & histogram, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram2D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram2D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram2D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram2D & histogram, IEvaluator &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram3D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram3D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram3D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram3D &, IEvaluator &, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram3D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram3D &, IEvaluator &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IHistogram3D & histogram, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IHistogram3D &, IEvaluator &, IEvaluator & , IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud1D & cloud, 
			 IEvaluator & evaluatorX) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud1D &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud1D & cloud, 
			 IEvaluator & evaluatorX, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud1D &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(ICloud1D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud1D &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud1D & cloud, 
			 IEvaluator & evaluatorX, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud1D &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud2D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud2D &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud2D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud2D &, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(ICloud2D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud2D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud2D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud2D &, IEvaluator &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud3D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud3D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud3D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud3D &, IEvaluator &, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(ICloud3D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud3D &, IEvaluator &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(ICloud3D & cloud, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(ICloud3D &, IEvaluator &, IEvaluator &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile1D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile1D &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile1D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile1D &, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(IProfile1D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile1D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile1D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile1D &, IEvaluator &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile2D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile2D &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile2D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile2D &, IEvaluator &, IEvaluator &, IEvaluator &, IFilter &)"));
  return false; 
}

bool ITupleROOT::project(IProfile2D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile2D &, IEvaluator &, IEvaluator &, IEvaluator &, IEvaluator &)"));
  return false; 
}

bool ITupleROOT::project(IProfile2D & profile, 
			 IEvaluator & evaluatorX, 
			 IEvaluator & evaluatorY, 
			 IEvaluator & evaluatorZ, 
			 IFilter & filter, 
			 IEvaluator & weight) 
{
  throw(NotYetImplementedException("ITuple","project(IProfile2D &, IEvaluator &, IEvaluator &, IEvaluator &, IFilter &, IEvaluator &)"));
  return false; 
}
