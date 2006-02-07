#include <RAIDA/ITupleFactoryROOT.h>
#include <RAIDA/ITupleROOT.h>
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
  return new ITupleROOT(path, title, columnNames, columnType, options) ;
}
