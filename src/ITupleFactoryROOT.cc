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

