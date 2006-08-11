#include <RAIDA/PathName.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace AIDA;

PathName::PathName() 
{
  setPathName("");
}

PathName::PathName(string rawName)
{
  setPathName(rawName);
  //  cout << "%" << rawName << "%" << endl;
  //  cout << "%" << _rawPathName << "%" << endl;
  //  for (unsigned i = 0; i<_names.size(); i++)
  //    cout << _names[i] << endl;

}

void PathName::setPathName(string rawName)
{
  _names.clear();
  _rawPathName = rawName;
  clean();

  if (_rawPathName == "")
    {
      _isEmpty = true;
      _names.push_back("");
      return;
    }

  _isEmpty = false;
  _isRelative = true;
  if (_rawPathName[0] == '/') _isRelative = false;

  // now: extract all names from path
  string rawPathName = _rawPathName;
  while (rawPathName.length() > 0)
    {
      if (rawPathName[0] == '/') rawPathName.erase(0,1); 
      if (rawPathName.find("/") < rawPathName.length())
	{
	  string newName = rawPathName.substr(0,rawPathName.find("/"));
	  rawPathName.erase(0,newName.length());
	  _names.push_back(newName);
	}
      else
	{
	  string newName = rawPathName;
	  _names.push_back(newName);
	  rawPathName = "" ;
	}
    }
}

string PathName::getName() const
{
  if (_names.size() < 1) return "";
  return _names[ (_names.size()-1) ];
}  

string PathName::getName(int number) const
{
  if (number < 0 || number >= (int)_names.size()) return "";
  return _names[number];
}  

string PathName::getPath() const
{
  return getPathTo( (_names.size()-2) ); 
}

string PathName::getPathTo(int number) const
{
  if (number < -1) return "";
  if (number >= ((int)_names.size()-1) ) number = _names.size() - 2;
  string thePath;
  if (!_isRelative) thePath = "/";
  for ( int i=0 ; i<=number ; i++ )
    {
      thePath += _names[i];
      thePath += "/";
    }
  return thePath;
}

string PathName::getPathName() const
{
  return _rawPathName;
}

string PathName::getPathNameTemp() const
{
  return _rawPathName + "_TEMP";
}

string PathName::getNameTemp() const
{
  if (_names.size() < 1) return "";
  return _names[ (_names.size()-1) ] + "_TEMP";
}

int PathName::getNumberOfNames() const
{
  return _names.size();
}

bool PathName::isEmpty()const
{ 
  return _isEmpty; 
}

void PathName::clean()
{
  while (_rawPathName.find(" ") < (_rawPathName.length()) )
    {
      _rawPathName.erase(_rawPathName.find(" "),1);
    }
  while (_rawPathName.find("//") < (_rawPathName.length()) )
    {
      _rawPathName.erase(_rawPathName.find("//"),1);
    }
}

bool PathName::onlyName() const
{
  if ( _isRelative && getName() != "" && getNumberOfNames() == 1 ) return true;
  return false;
}

void PathName::changePath(string rawPath)
{
  string name = getName();
  if (rawPath == "")
    {
      setPathName(name);
      return;
    }

  if (rawPath[rawPath.length()-1]!='/') rawPath += "/";
  rawPath += name;
  setPathName(rawPath);
}
