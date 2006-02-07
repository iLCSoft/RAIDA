// -*- C++ -*-
#include <RAIDA/Naming.h>

#include <iostream>
#include <string>

using namespace AIDA ;
using namespace std ;

string Naming::binEntry(const string & name) 
{
  return mergeNames(name,"_(AIDA_bin_entry)");
}

string Naming::binContents(const string & name) 
{
  return mergeNames(name,"_(AIDA_bin_contents)");
}

string Naming::binMeanX(const string & name) 
{
  return mergeNames(name,"_(AIDA_bin_mean_x)");
}

string Naming::binMeanY(const string & name) 
{
  return mergeNames(name,"_(AIDA_bin_mean_y)");
}

string Naming::binMeanZ(const string & name) 
{
  return mergeNames(name,"_(AIDA_bin_mean_z)");
}

string Naming::titleBinEntry(const string & name) 
{
  return mergeNames(name," (AIDA bin entry)");
}

string Naming::titleBinContents(const string & name) 
{
  return mergeNames(name," (AIDA bin contents)");
}

string Naming::titleBinMeanX(const string & name) 
{
  return mergeNames(name," (AIDA bin mean x)");
}

string Naming::titleBinMeanY(const string & name) 
{
  return mergeNames(name," (AIDA bin mean y)");
}

string Naming::titleBinMeanZ(const string & name) 
{
  return mergeNames(name," (AIDA bin mean z)");
}

string Naming::mergeNames(const string & n1,const string & n2)  
{
  return n1+n2;
}
