#include <RAIDA/utilROOT.h>
#include <iostream>
#include <string>

using namespace AIDA ;
using namespace std ;

namespace AIDA {

std::string AIDAInternalTitle(const std::string & title, int type)
{
  string titleAIDA;
  if (type == 1)
    {
      titleAIDA = title + " (AIDA internal: bin entries)";
    }
  else if (type == 10)
    {
      titleAIDA = title + " (AIDA internal: bin contents)";
    }
  else if (type == 2)
    {
      titleAIDA = title + " (AIDA internal: bin mean X)";
    }
  else if (type == 3)
    {
      titleAIDA = title + " (AIDA internal: bin mean Y)";
    }
  else if (type == 4)
    {
      titleAIDA = title + " (AIDA internal: bin mean Z)";
    }
  else
    {
      exit(-1);
    }

  return titleAIDA;
}

string extractName(const string & pathName)
{
  string a = pathName;
  if (a == "") return a;
  cout << "|" << a << "|" << endl;
  while (a.find(" ") <= (a.length()-1) )
    {
      a.erase(a.find(" "),1);
    }
  cout << "|" << a << "|" << endl;
  if (a[(a.length()-1)] == '/') return "";
  if (a.find("/") == string::npos) return a;
  if (a.rfind("/") < string::npos) return a.substr( a.rfind("/")+1 );
  return "MyObj";
}


} // end namespace AIDA

