#include <RAIDA/ITreeFactoryROOT.h>
#include <RAIDA/ITreeROOT.h>


using namespace AIDA ;
using namespace std;

ITree * ITreeFactoryROOT::create()
{
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "ITreeFactoryROOT::create():" << endl;
  cout << "          " 
       << "Creates an AIDA tree in memory" << endl;
  cout << "          " 
       << "will call: ITreeROOT::ITreeROOT()" << endl;
#endif
  return new ITreeROOT;
}

ITree * ITreeFactoryROOT::create(const std::string & storeName, 
				 const std::string & storeType, 
				 bool readOnly, 
				 bool createNew, 
				 const std::string &options)
{
#ifdef USE_RAIDA_DEBUG_VERBOSE
  cout << "ITreeFactoryROOT::create(const std::string & storeName,const std::string & storeType,bool readOnly,bool createNew,const std::string &options):" << endl;
  cout << "          " 
       << "Creates an AIDA tree connected to a ROOT file" << endl << endl;
  cout << "          " 
       << "parameter:" << endl;
  cout << "          " 
       << "---------" << endl;
  cout << "          " 
       << "storeName: " << storeName << endl;
  cout << "          " 
       << "storeType: " << storeType << endl;
  cout << "          " 
       << "readOnly: " << readOnly 
       << " createNew: " << createNew << endl;
  cout << "          " 
       << "options: " << options << endl;
  cout << "          " 
       << "will call: ITreeROOT::ITreeROOT(const std::string & storeName,const std::string & storeType,bool readOnly,bool createNew,const std::string &options)" << endl;
#endif
  return new ITreeROOT(storeName,storeType,readOnly,createNew,options);
}
