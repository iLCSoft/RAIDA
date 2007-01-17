#include <RAIDA/ITupleFactoryROOT.h>
#include <RAIDA/ITupleROOT.h>
#include <RAIDA/ITreeROOT.h>
#include <RAIDA/PathName.h>

#include <iostream>

using namespace AIDA ;
using namespace std;

ITupleFactoryROOT::ITupleFactoryROOT(ITree & tree)
{
  _usedTree = &tree;
}

ITuple * ITupleFactoryROOT::create(const std::string & path,
				   const std::string & title,
				   const std::vector<std::string>  & columnNames,
				   const std::vector<std::string>  & columnType,
				   const std::string & options) 
{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "ITupleFactoryROOT::create(const std::string & path,const std::string & title,const std::vector<std::string>  & columnNames,const std::vector<std::string>  & columnType,const std::string & options):" << endl;
  cout << "          " 
       << "Creates a ITuple from two vectors with column names and types" << endl << endl;
  cout << "          " << "parameters:" << endl 
       << "          " << "----------" << endl;
  cout << "          " << "path: " << path << endl; 
  cout << "          " << "title: " << title << endl; 
#endif

  if (columnNames.size() != columnType.size()) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          " << "Can not create a tuple: "
	   << "Number of columnNames (" << columnNames.size() << ") "
	   << "does not equal number of columnType (" << columnType.size() << ")." << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "no. of columns: " << columnNames.size() << endl; 
  cout << "          "
       << "column names (type): ";
  for (int i = 0; i<= columnNames.size()-1;i++)
    cout << columnNames[i] << " (" << columnType[i] << ") ";
  cout << endl;
  cout << "          " << "options: " << options << endl; 
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
           << "No file specified: can not create a tuple!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          "
       << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
          cout << "          "
               << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
           << "directory where the tuple is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "
           << "directory where the tuple is created: " << _usedTree->pwd() << endl;
    }
#endif

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
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "ITupleFactoryROOT::create(const string & path,const string & title,const string & columns,const string & options):" << endl;
  cout << "          " 
       << "Creates a ITuple from a string containing column names and types" << endl << endl;
  cout << "          " << "parameters:" << endl 
       << "          " << "----------" << endl;
  cout << "          " << "path: " << path << endl; 
  cout << "          " << "title: " << title << endl; 
  cout << "          " << "columns: " << columns << endl; 
#endif

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
    //    cout<<"// "<<type<<" "<<name<<";"<<endl;
    columnType.push_back(type);
    columnNames.push_back(name);
  }

  if (columnNames.size() != columnType.size()) 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          " << "Can not create a tuple: "
	   << "Number of columnNames (" << columnNames.size() << ") "
	   << "does not equal number of columnType (" << columnType.size() << ")." << endl;
#endif
      return NULL;
    }

#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          " 
       << "no. of columns: " << columnNames.size() << endl; 
  cout << "          "
       << "column names (type): ";
  for (int i = 0; i<= columnNames.size()-1;i++)
    cout << columnNames[i] << " (" << columnType[i] << ") ";
  cout << endl;
  cout << "          " << "options: " << options << endl; 
#endif

  PathName thePath(path);
  if (thePath.getName() == "") 
    {
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
           << "No file specified: can not create a tuple!" << endl;
#endif
      return NULL;
    }

  string thePWD = _usedTree->pwd();
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  cout << "          "
       << "original working directory: " << _usedTree->pwd() << endl;
#endif

  if ( !thePath.onlyName() )
    {
      if (!_usedTree->cd(thePath.getPath()) ) 
	{
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
          cout << "          "
               << "directory does not exist: " << thePath.getPath() << endl;
#endif
	  return NULL;
	}
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
      cout << "          "
           << "directory where the tuple is created: " << _usedTree->pwd() << endl;
#endif
    }
#ifdef USE_RAIDA_DEBUG_VERBOSE_FACTORY
  else
    {
      cout << "          "
           << "directory where the tuple is created: " << _usedTree->pwd() << endl;
    }
#endif

  ITupleROOT* tuple = new ITupleROOT(thePath.getName(), title, 
				     columnNames, columnType, options) ;
  _usedTree->cd( thePWD ) ;
  return tuple;
}
