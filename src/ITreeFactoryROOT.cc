#include <RAIDA/ITreeFactoryROOT.h>
#include <RAIDA/ITreeROOT.h>


using namespace AIDA ;
using namespace std;

ITree * ITreeFactoryROOT::create()
{
  return new ITreeROOT;
}

ITree * ITreeFactoryROOT::create(const std::string & storeName, 
				 const std::string & storeType, 
				 bool readOnly, 
				 bool createNew, 
				 const std::string &options)
{
  return new ITreeROOT(storeName,storeType,readOnly,createNew,options);
}
