#include <RAIDA/NotYetImplementedException.h>

#include <exception>
#include <iostream>
#include <string>

using namespace AIDA;
using namespace std;

NotYetImplementedException::NotYetImplementedException(const string& what_arg)
{
  _what = "<<< SORY !!! The class ";
  _what += what_arg;
  _what += " has not yet been implemented! >>>";
  cout << _what << endl;
}

NotYetImplementedException::NotYetImplementedException(const string& what_function,
						       const string& what_class)
{
  _what = "<<< SORY !!! The function ";
  _what += what_function;
  _what += " in class ";
  _what += what_class;
  _what += " has not yet been implemented! >>>";
  cout << _what << endl;
}

