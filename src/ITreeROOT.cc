#include <RAIDA/ITreeROOT.h>

#include <iostream>
#include <TFile.h>
#include <RVersion.h>
#include <string>

#if ROOT_VERSION_CODE < ROOT_VERSION(5,8,00)
  #define OLD_ROOT_VERSION
#else
  #undef  OLD_ROOT_VERSION
#endif

using namespace AIDA ;
using namespace std;

ITreeROOT::ITreeROOT() : _ROOTFile(0) {}

ITreeROOT::ITreeROOT(const std::string & storeName,
		     const std::string & storeType,
		     bool readOnly,
		     bool createNew,
		     const std::string &options)
 : _ROOTFile(0)
{
  string RWMode;
  if (createNew && readOnly)
    {
      RWMode = "READ";
    }
  else if (!createNew && readOnly)
    {
      RWMode = "READ";
    }
  else if (createNew && !readOnly)
    {
      RWMode = "RECREATE";
    }
  else if (!createNew && !readOnly)
    {
      RWMode = "UPDATE";
    }

  // save storeName because ROOT can not return it
  _storeName = storeName;

  _ROOTFile = new TFile(storeName.c_str(),RWMode.c_str(),"ROOT_AIDA",1);
}

ITreeROOT::~ITreeROOT()
{
  delete _ROOTFile;
}

bool ITreeROOT::commit()
{
  if (_ROOTFile) 
    {
      //      _ROOTFile->mkdir("mydir","mydir");
      _ROOTFile->Write();
      //_ROOTFile->ls("-d");
      // print the ROOT Directory to std-out:
      //  gDirectory->ls("-d");
      return true;
    }
  else 
    {
      return false; 
    }
}

bool ITreeROOT::close()
{
  if (_ROOTFile) 
    {
      // print out the current ROOT working directory.
      //      gDirectory->pwd();
      _ROOTFile->Close();
      //      gDirectory->pwd();
      return true;
    }
  else 
    {
      return false; 
    }
}

std::string ITreeROOT::storeName() const
{
  return _storeName;
}

bool ITreeROOT::cd(const std::string & path) 
{
  string localPath("");
  if (path != "" && path[0] == '/')
    {
      localPath = storeName();
      localPath += ":";
      localPath += path;
    }
  else if (path == ".") 
    {
      return true;
    }
  else if (path != "" && path[0] != '/')
    {
      localPath = path;
    }

#ifdef OLD_ROOT_VERSION
  return (bool)gDirectory->cd(localPath.c_str());
  //  return (bool)_ROOTFile->cd(localPath.c_str());
#else
  TDirectory* target = gDirectory->GetDirectory(localPath.c_str());
  if ( target == NULL )
    return false;

  target->cd();
  return true;
#endif
}

std::string ITreeROOT::pwd() const
{
  int length = _storeName.length() + 1; // because of the ":"
  string thePath(gDirectory->GetPath());
  thePath.replace(0,length,"",0);
  return thePath;
}

bool ITreeROOT::mkdir(const std::string & path)
{
  string leftPath;
  string localPath = path;
  string subDirectory;

  // terminate if path is empty 
  if (localPath == "") return false; 

  // strip trailing "/" and leading "./" 
  while (localPath.rfind("/") == localPath.length()-1) 
    {
      localPath.erase(localPath.rfind("/"));
    }
  if (localPath.find("./") == 0) localPath.erase(0,2);

  if (localPath.rfind(("/")) == string::npos) 
    { // simple sub-directory
      subDirectory = localPath;
    }
  else  
    { // path consists of two parts: Sub-directory + leading path
      subDirectory = localPath.substr(localPath.rfind(("/"))+1);
      leftPath = localPath; 
      leftPath.erase(leftPath.rfind("/"));
      if (leftPath == "") leftPath = "/";
    }

  // check if all leading sub-directories exist 
  string currentDir = pwd();
  if (leftPath != "")
    {
      if (!cd(leftPath)) return false;
    }

#ifdef OLD_ROOT_VERSION
  // sub-directory to be created already exists ?
  if (cd(subDirectory))
    {
      cd(currentDir);
      return false;
    }

  // Subdirectory exists but is an other object
  string temp = subDirectory; temp += ";*";
  if (_ROOTFile->Get(temp.c_str()))
    {
      cd(currentDir);
      return false;
    }
#else
  TDirectory* target = gDirectory->GetDirectory(subDirectory.c_str());
  if ( target != NULL )
    return false;
#endif

  // create the sub-directory:
  gDirectory->mkdir(subDirectory.c_str(),subDirectory.c_str());

  cd(currentDir);
  return true;
}

bool ITreeROOT::ls(const std::string & path,
		   bool recursive,
		   std::ostream & os) const
{
  ITreeROOT *tempobj = const_cast<ITreeROOT*>(this);
  string thePWD = pwd();
  bool pathexists = tempobj->cd(path);
  //  cout << "pfad: " << path << " " << pathexists << endl;
  if (!pathexists) return false;
  gDirectory->ls("-d");
  tempobj->cd( thePWD ) ;
  return true;
}
