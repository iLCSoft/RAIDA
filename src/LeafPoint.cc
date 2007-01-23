#include <RAIDA/LeafPoint.h>
#include <string>
#include <iostream>
#include <limits.h>
#include <float.h>
#include <TROOT.h>

using namespace AIDA ;
using namespace std;

LeafPoint::LeafPoint()
{
  _leafType = 'D';
}

LeafPoint::LeafPoint(string type) 
{
  _leafType = type[0];
}

LeafPoint::LeafPoint(string type,string name) 
{
  _leafType = type[0];
  _leafName = name;
}

LeafPoint::LeafPoint(const LeafPoint & rhs)
{
  _leafType = rhs._leafType;
  _leafName = rhs._leafName;
  _f = rhs._f;
  _d = rhs._d;
  _i = rhs._i;
  _s = rhs._s; 
  _l = rhs._l; 
  _c = rhs._c;
  _b = rhs._b;
  _st = rhs._st;
}

void* LeafPoint::getValue() const 
{
  if (_leafType == 'D') 
    {
      return (void*)&_d;
    } 
  else if (_leafType == 'F')
    {
      return (void*)&_f;
    }
  else if (_leafType == 'I')
    {
      return (void*)&_i;
    }
  else if (_leafType == 'S')
    {
      return (void*)&_s;
    }
  else if (_leafType == 'L')
    {
      return (void*)&_l;
    }
  else if (_leafType == 'O')
    {
      return (void*)&_b;
    }
  else if (_leafType == 'B')
    {
      return (void*)&_c;
    }
  else if (_leafType == 'C')
    {
      return (void*)_st.c_str();
    }
  return (void*)&_d;
}

bool LeafPoint::set(const float v) 
{
  double temp = v;
  return set(temp);
}

bool LeafPoint::set(const double v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      if (fabs(v) > FLT_MIN && fabs(v) < FLT_MAX)
	{
	  _f = v;
	  return true;
	}
      else 
	{
	  _f = 0;
	  return false;
	}
    }
  else if (_leafType == 'I')
    {
      if (v > INT_MIN && v < INT_MAX)
	{
	  _i = (Int_t)v;
	  return true;
	}
      else 
	{
	  _i = 0;
	  return false;
	}
    }
  else if (_leafType == 'S')
    {
      if (v > SHRT_MIN && v < SHRT_MAX)
	{
	  _s = (Short_t)v;
	  return true;
	}
      else 
	{
	  _s = 0;
	  return false;
	}
    }
  else if (_leafType == 'L')
    {
      if (v > INT_MIN && v < INT_MAX)
	{
	  _l = (Int_t)v;
	  return true;
	}
      else 
	{
	  _l = 0;
	  return false;
	}
    }
  else if (_leafType == 'B')
    {
      if (v > SCHAR_MIN && v < SCHAR_MAX)
	{
	  _c = (Char_t)v;
	  return true;
	}
      else 
	{
	  _c = 0;
	  return false;
	}
    }
  return false;
}

bool LeafPoint::set(const int v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      _f = v;
      return true;
    }
  else if (_leafType == 'I')
    {
      _i = v;
      return true;
    }
  else if (_leafType == 'S')
    {
      if (v > SHRT_MIN && v < SHRT_MAX)
	{
	  _s = v;
	  return true;
	}
      else 
	{
	  _s = 0;
	  return false;
	}
    }
  else if (_leafType == 'L')
    {
      _l = v;
      return true;
    }
  else if (_leafType == 'O')
    {
      if (v) 
	_b = true;
      else
	_b = false;
      return true;
    }
  else if (_leafType == 'B')
    {
      if (v > SCHAR_MIN && v < SCHAR_MAX)
	{
	  _c = v;
	  return true;
	}
      else 
	{
	  _c = 0;
	  return false;
	}
    }
  return false;
}

bool LeafPoint::set(const short v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      _f = v;
      return true;
    }
  else if (_leafType == 'I')
    {
      _i = v;
      return true;
    }
  else if (_leafType == 'S')
    {
      _s = v;
      return true;
    }
  else if (_leafType == 'L')
    {
      _l = v;
      return true;
    }
  else if (_leafType == 'O')
    {
      if (v) 
	_b = true;
      else
	_b = false;
      return true;
    }
  else if (_leafType == 'B')
    {
      if (v > SCHAR_MIN && v < SCHAR_MAX)
	{
	  _c = v;
	  return true;
	}
      else 
	{
	  _c = 0;
	  return false;
	}
    }
  return false;
}

bool LeafPoint::set(const long v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      _f = v;
      return true;
    }
  else if (_leafType == 'I')
    {
      if (v > INT_MIN && v < INT_MAX)
	{
	  _i = v;
	  return true;
	}
      else 
	{
	  _i = 0;
	  return false;
	}
    }
  else if (_leafType == 'S')
    {
      if (v > SHRT_MIN && v < SHRT_MAX)
	{
	  _s = v;
	  return true;
	}
      else 
	{
	  _s = 0;
	  return false;
	}
    }
  else if (_leafType == 'L')
    {
      _l = v;
      return true;
    }
  else if (_leafType == 'O')
    {
      if (v) 
	_b = true;
      else
	_b = false;
      return true;
    }
  else if (_leafType == 'B')
    {
      if (v > SCHAR_MIN && v < SCHAR_MAX)
	{
	  _c = v;
	  return true;
	}
      else 
	{
	  _c = 0;
	  return false;
	}
    }
  return false;
}

bool LeafPoint::set(const char v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      _f = v;
      return true;
    }
  else if (_leafType == 'I')
    {
      _i = v;
      return true;
    }
  else if (_leafType == 'S')
    {
      _s = v;
      return true;
    }
  else if (_leafType == 'L')
    {
      _l = v;
      return true;
    }
  else if (_leafType == 'O')
    {
      if (v) 
	_b = true;
      else
	_b = false;
      return true;
    }
  else if (_leafType == 'B')
    {
      _c = v;
      return true;
    }
  return false;
}

bool LeafPoint::set(const bool v) 
{
  if (_leafType == 'D') 
    {
      _d = v;
      return true;
    } 
  else if (_leafType == 'F')
    {
      _f = v;
      return true;
    }
  else if (_leafType == 'I')
    {
      _i = v;
      return true;
    }
  else if (_leafType == 'S')
    {
      _s = v;
      return true;
    }
  else if (_leafType == 'L')
    {
      _l = v;
      return true;
    }
  else if (_leafType == 'O')
    {
      _b = v;
      return true;
    }
  else if (_leafType == 'B')
    {
      _c = v;
      return true;
    }
  return false;
}

bool LeafPoint::set(const string v) 
{
  _st = v;
  return true;
}

char LeafPoint::getType() const
{
  return _leafType;
}

string LeafPoint::getTypeLong() const 
{
  string typelong;

  if (_leafType == 'D') typelong = "double"; 
  else if (_leafType == 'F') typelong = "float"; 
  else if (_leafType == 'I') typelong = "int";
  else if (_leafType == 'S') typelong = "short"; 
  else if (_leafType == 'L') typelong = "long"; 
  else if (_leafType == 'B') typelong = "char"; 
  else if (_leafType == 'O') typelong = "bool";
  else if (_leafType == 'C') typelong = "string"; 
  else typelong = "";

  return typelong;
}
string LeafPoint::getName() const 
{
  return _leafName;
}

void LeafPoint::clear()
{
  _f = 0;
  _d = 0;
  _i = 0;
  _s = 0; 
  _l = 0; 
  _c = 0;
  _b = 0;
  _st = "";
}

string LeafPoint::getROOTNameType() const 
{
  string nametype;

  if (_leafType == 'L') 
    {
      nametype = _leafName + "/I" ;
    }
  else
    {
      nametype = _leafName + "/" + _leafType;
    }
  return nametype;
}

double LeafPoint::getDouble() const 
{
  return (double)_d;
}

float LeafPoint::getFloat() const 
{
  return (float)_f;
}

int LeafPoint::getInt() const 
{
  return (int)_i;
}

short LeafPoint::getShort() const
{
  return (short)_s;
}

long LeafPoint::getLong() const 
{
  return (long)_l;
}

char LeafPoint::getChar() const 
{
  return (char)_c;
}

bool LeafPoint::getBool() const 
{
  return (bool)_b;
}

string LeafPoint::getString() const 
{
  return _st;
}



