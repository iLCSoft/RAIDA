#include <RAIDA/ITupleFactoryROOT.h>
#include <RAIDA/ITupleROOT.h>
#include <RAIDA/ITreeROOT.h>
#include <RAIDA/PathName.h>

#include <iostream>

using namespace AIDA ;
using namespace std;

ITupleFactoryROOT::ITupleFactoryROOT(ITree & tree)
{
  //cout << "tuple gibts noch nicht" << endl;
  _usedTree = &tree;
}

ITuple * ITupleFactoryROOT::create(const std::string & path,
				   const std::string & title,
				   const std::vector<std::string>  & columnNames,
				   const std::vector<std::string>  & columnType,
				   const std::string & options) 
{
  PathName thePath(path);
  if (thePath.getName() == "") return NULL;

  string thePWD = _usedTree->pwd();

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) return NULL;
    }

  ITupleROOT* tuple = new ITupleROOT(thePath.getName(), title, 
				     columnNames, columnType, options) ;

  _usedTree->cd( thePWD ) ;
  return tuple;
}

ITuple * ITupleFactoryROOT::create(const string & path, 
				   const string & title, 
				   const string & columns, 
				   const string & options) 
{
  PathName thePath(path);
  if (thePath.getName() == "") return NULL;

  string thePWD = _usedTree->pwd();

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) return NULL;
    }


  vector<string> columnNames;
  vector<string> columnType;

  string type;
  int nl = columns.length();
  int ix=0;
  while (ix<nl) {
    string name;
    string::size_type pos = columns.find (",",ix);
    if (pos==string::npos) pos=nl;
    name=columns.substr(ix,pos-ix);
    for (;;) {
      string::size_type isp = name.find(" ",0);
      if (isp==0) name=name.substr(1);
      else if (isp==string::npos) break;
      else {
	type=name.substr(0,isp);
	name=name.substr(isp+1);
	break;
      }
    }
    ix=pos+1;
    cout<<"// "<<type<<" "<<name<<";"<<endl;
    columnType.push_back(type);
    columnNames.push_back(name);
  }
  
  ITupleROOT* tuple = new ITupleROOT(thePath.getName(), title, 
				     columnNames, columnType, options) ;
  _usedTree->cd( thePWD ) ;
  return tuple;
}
